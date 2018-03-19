/**
 * \file utils.h
 */
#ifndef H_UTILS
#define H_UTILS

#if 0

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>


// Include libncurses et libcdk
#include <ncurses.h>
#include <cdk/cdk.h>

#endif

// Macros
/** Permet d'utiliser la valeur FALSE au lieu de 0 */
#define FALSE 0
/** Permet d'utiliser la valeur TRUE au lieu de 1 */
#define TRUE 1

/** Ce test permet d'afficher les erreurs pour les appels systèmes qui aurai échoué
 * \param statement Le statement a tester
 * \param mess Le message d'erreur a afficher
 */
#define CHECK(statement,mess) if ((statement)<0) { perror(mess); exit(errno); }

/** Ce test permet d'afficher les erreurs en cas de valeur nulle
 * \param statement Le statement a tester
 * \param mess Le message d'erreur a afficher
 */
#define CHECK_NULL(statement,mess) if ((statement) == NULL) { fprintf(stderr,mess); exit(2); }

/** Ce test permet d'afficher les erreurs pour les appels systèmes qui aurai échoué, sauf pour EINTR, afin de pouvoir nettoyer correctement les ressources
 * \param statement Le statement a tester
 * \param mess Le message d'erreur a afficher
 */
#define CHECK_NOEINTR(statement,mess) if ((statement)<0 && errno != EINTR) { perror(mess); exit(errno); }

/** Ce test permet d'afficher les erreurs en cas de semaphore nulle
 * \param statement Le statement a tester
 * \param mess Le message d'erreur a afficher
 */
#define CHECK_SEMFAILED(statement,mess) if ((statement) == SEM_FAILED) { fprintf(stderr,mess); exit(2); }

/** \mainpage Description du protocole
 *MCS Quiz

# Principe

Le projet consiste à ce que plusieurs clients s’affrontent en 2vs2 par équipe sur des questions posées par les joueurs eux-mêmes.

Chaque nouveau joueur identifié par un nom de compte va se connecter sur le serveur central, qui se charge de trouver les joueurs qu’il connaît (Ceux en partie comme ceux qui sont en recherche de partie)

Les joueurs en recherche de partie pourront décider d'émettre et/ou d’accepter les invitations d’autres joueurs.

Dès que les 4 joueurs sont d’accord, on connecte tous les utilisateurs entre eux.

Un canal "public" est disponible entre tous les joueurs afin qu’ils s'envoient des messages pendant la partie.

Un canal supplémentaire "privé” entre les membres d’une même équipe servira à l’envoi de message privés.

Le serveur central décide de la personne qui pose la question. La personne écrit la question, qui est envoyée aux autres joueurs (Y compris son partenaire). Les joueurs de l’autre équipe réfléchissent à la question et l’un d’entre eux (Ou les 2, mais seule la première réponse sera prise en compte) répond. L’équipe qui a émise la question décide de la validité de la réponse.

Si elle est invalide, alors l’autre équipe renvoi une réponse et on continue jusqu’à la bonne réponse.

Dès qu’une bonne réponse est émise, le serveur central est prévenu et désigne le joueur suivant.

La partie est fini dès qu’un des joueurs fait une demande polie de déconnexion, ou dès qu’on n’arrive pas à contacter un joueur après un certain temps.

Le serveur central va pinger toutes les personnes qu’il connaît afin d’estimer le temps de latence entre eux.

Les joueurs en partie font de même, afin de s’assurer qu’ils puissent communiquer entre eux, et connaître le temps de latence aussi.

# Scénarii

Un client se connecte au serveur central

Il demande la liste des clients que le serveur connaît

Celui-ci lui retourne le nombre de clients qu’il connaît et enfin, le client demande individuellement chaque infos client.

Un client fait une demande de partie à un autre client.

Celui-ci accepte ou refuse.

S’il refuse, alors le client émetteur est averti

S’il accepte, on avertit le serveur central.

Dès la formation d’une équipe, les clients demandent au serveur central de les autoriser à jouer, afin que le serveur puisse enregistrer les équipes, et retourne les ports de communications qu’il a choisi pour les chats publics et privés à chaque client (Avec seulement ce qu’il a besoin de connaître).

Les clients essayent de mettre en place une connexion sur un port connu entre eux, afin de faire l’envoi/réception des requêtes/réponses touchant au jeu, et avertissent le serveur central en cas de réussite d’une communication.

En cas d'échec de communication, on avertit le serveur central qu’on arrive pas à le contacter.

A partir d’ici, toutes les requêtes importantes font l’objet d’un acquittement de chaque client et enfin, l’émetteur acquitte que tout le monde à reçu.

Dans le cas des chats, l’envoi d’un message est une requête importante

Dans le cas du jeu, le serveur central envoi à tout le monde qui est le joueur qui va poser la question. Ce joueur envoie la requête qui contient la question (Requête importante)

L'équipe adverse envoie une réponse (Requête importante). Si le joueur qui a envoyé la réponse reçoit plusieurs requêtes, seule la première est prise en compte.

Si c’est une bonne réponse, tout le monde est prévenu, et le joueur prévient le serveur qu’il peut choisir le nouveau joueur qui va poser la réponse.

On boucle sur les dernières étapes, jusqu'à ce qu’un joueur fasse une demande au serveur central de se déconnecter.

Dans ce cas, le serveur central averti tous les autres membres qu’il doivent couper la connexion et repasser en recherche de nouveaux adversaires.

L’autre cas est que les pings n’ont rien retourné sur un client, dans ce cas on avertit le serveur central qu’on arrive pas à le contacter, et on effectue le même traitement qu’au-dessus.

# Format protocolaire

## Workflow

Requête simple :


Requête avec réponse :


Requête multi-acknowledge :


## Requêtes

Sauf si précisé, toutes les requêtes demandent une connexion établie avec le serveur central ou avec un client/serveur en partie.

La numérotation des requêtes suit le principe suivant :

<table>
  <tr>
    <td>0XX</td>
    <td>Fonctions bas niveau (Ping/Pong, Déconnexion, ...)</td>
  </tr>
  <tr>
    <td>1XX</td>
    <td>Requêtes entre le serveur central et un client</td>
  </tr>
  <tr>
    <td>2XX</td>
    <td>Requêtes entre 2 clients</td>
  </tr>
</table>


### Requêtes « bas niveau » (0XX)

#### Ping (001)

Cette requête sert à vérifier la connexion avec un client.

Cette requête peut être envoyé si le client est déconnecté.

Elle ne prend aucun paramètre.

#### Déconnexion (002)

Cette requête sert à déconnecter le client.

Permet au serveur de faire des traitements appropriés.

Les clients DEVRAIENT envoyer cette requête pour assurer le bon fonctionnement.

Elle ne prend aucun paramètre.

### Requêtes entre le serveur central et un client

#### Connexion au serveur central (100)

Cette requête sert à demander une connexion avec le serveur central.

Cette requête ne doit être envoyé que si le client est déconnecté.

Elle ne prend un paramètre :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>Nom d’affichage</td>
    <td>Pseudo</td>
    <td>Chaine de caractères</td>
  </tr>
</table>


#### Nombre de clients connecté (101)

Cette requête sert à demander le nombre de clients connecté au serveur central.

Elle ne prend aucun paramètre.

#### Informations client (102)

Cette requête sert à des informations sur un client connecté au serveur central.

Dans le cadre d’une utilisation raisonnée, le client doit savoir auparavant le nombre de clients connectées, sachant que cette valeur peut changer au cours du temps

Elle prend un paramètre :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>Index client</td>
    <td>Index</td>
    <td>Entier long non signé</td>
  </tr>
</table>


#### Passer en mode partie (103)

Cette requête sert à demander au serveur central de faire passer les clients spécifiés en mode partie.

Si le client demandé est déjà en partie, le serveur DOIT rejeter la demande.

Tous les clients concernés DOIVENT envoyer la requête, a des fins de contrôle.

Elle prend 4 paramètres :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
    <td>Remarque</td>
  </tr>
  <tr>
    <td>Premier client</td>
    <td>Client_1</td>
    <td>Chaine de caractères</td>
    <td></td>
  </tr>
  <tr>
    <td>Deuxième client</td>
    <td>Client_2</td>
    <td>Chaine de caractères</td>
    <td></td>
  </tr>
  <tr>
    <td>Troisième client</td>
    <td>Client_3</td>
    <td>Chaine de caractères</td>
    <td></td>
  </tr>
  <tr>
    <td>Partenaire</td>
    <td>Partenaire</td>
    <td>Entier court non signé</td>
    <td>Prends une valeur entre 1 et 3</td>
  </tr>
</table>


#### Port chat (104)

Cette requête sert à demander au serveur central d’envoyer le port de connexion pour connecter le client sur le système de chat.

Le serveur central DOIT vérifier si on demande le port de chat privé, d’être dans la même équipe.

Le serveur central DOIT rejeter la requête si l’un des clients n’est pas en partie.

Elle prend un paramètre :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
    <td>Remarque</td>
  </tr>
  <tr>
    <td>Type de connexion</td>
    <td>Type</td>
    <td>Entier court non signé</td>
    <td>Prend 2 valeurs :
1 pour le chat public
2 pour le chat privé</td>
  </tr>
</table>


#### Choix du joueur (105)

Cette requête sert à demander au serveur central qui est le client en partie qui pose la question

Le serveur central DOIT rejeter la requête si le client n’est pas en partie.

Elle prend aucun paramètre

### Requêtes entre 2 clients

#### Demande de partie (200)

Cette requête sert à demander à un client non connecté à une partie.

Si le client demandé est déjà en partie, le client/serveur DOIT rejeter la demande.

La demande ne DOIT pas être envoyé au serveur central mais directement au client grâce aux ports de demande de connexion fourni par les informations clients (Voir requête 102)

Elle prend un paramètre :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
    <td>Remarque</td>
  </tr>
  <tr>
    <td>Equipe</td>
    <td>Equipe</td>
    <td>Entier court signé</td>
    <td>2 valeurs sont autorisées :
+1 pour être dans la même équipe
-1 pour être en équipe adverse</td>
  </tr>
</table>


#### Question (201)

Cette requête sert à envoyer une question

Le serveur central ne DOIT pas recevoir cette requête.

Elle prend un paramètre :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>Question posée</td>
    <td>Question</td>
    <td>Chaine de caractères</td>
  </tr>
</table>


#### Valider réponse (202)

Cette requête sert à valider la réponse reçue.

Le serveur central ne DOIT pas recevoir cette requête.

Elle prend deux paramètres :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
    <td>Remarque</td>
  </tr>
  <tr>
    <td>Validité</td>
    <td>Valide</td>
    <td>Entier court non signé</td>
    <td>Valeur booléenne</td>
  </tr>
  <tr>
    <td>Message</td>
    <td>Message</td>
    <td>Chaine de caractères</td>
    <td></td>
  </tr>
</table>


#### Message chat (203)

Cette requête sert à envoyer un nouveau message de chat

Le serveur central ne DOIT pas recevoir cette requête.

Cette requête est fortement dépendante du port d’envoi choisi.

Elle prend un paramètre :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>Message</td>
    <td>Message</td>
    <td>Chaine de caractères</td>
  </tr>
</table>


## Réponses

La numérotation des réponses suit le principe suivant :

<table>
  <tr>
    <td>5XX</td>
    <td>Fonctions bas niveau (Ping/Pong, Déconnexion, ...)</td>
  </tr>
  <tr>
    <td>6XX</td>
    <td>Réponses entre le serveur central et un client</td>
  </tr>
  <tr>
    <td>7XX</td>
    <td>Réponses entre 2 clients</td>
  </tr>
</table>


### Réponses « bas niveau »

#### Pong (500)

Cette réponse sert à vérifier la connexion avec un client.

Cette réponse DOIT être envoyé en cas de requête ping (001).

Elle ne retourne aucune valeur.

#### Requête invalide (501)

Cette réponse sert à prévenir qu’une requête précédente n’aurait pas dû être envoyé, ou que des paramètres sont manquants

Elle ne retourne aucune valeur.

#### Acquittement (502)

Cette réponse sert à prévenir qu’une requête précédente à été reçu et que le destinataire peut faire ses traitements.

Elle ne retourne aucune valeur.

#### Ports disponibles (503)

Cette réponse permet d’avertir le destinataire des ports ouvert sur le client en paramètre de la requête précédente

Elle retourne deux valeurs

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>Type</td>
    <td>Type</td>
    <td>Entier court non signé</td>
  </tr>
  <tr>
    <td>Port</td>
    <td>Port</td>
    <td>Entier non signé</td>
  </tr>
</table>


### Réponses entre le serveur central et un client

#### Nombre de clients (600)

Cette réponse transmet le nombre de clients connecté sur le serveur.

Cette réponse ne DOIT être envoyé que par le serveur central.

Elle retourne une valeur

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>Nombre de clients</td>
    <td>Clients</td>
    <td>Entier long non signé</td>
  </tr>
</table>


#### Informations client (601)

Cette réponse transmet les informations sur un client connecté sur le serveur.

Cette réponse ne DOIT être envoyé que par le serveur central.

Elle retourne plusieurs valeurs : (Certaines restent a définir)

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>Pseudo</td>
    <td>Pseudo</td>
    <td>Chaine de caractères</td>
  </tr>
  <tr>
    <td>Port de demande</td>
    <td>Port</td>
    <td>Entier non signé</td>
  </tr>
  <tr>
    <td>… (A déterminer)</td>
    <td></td>
    <td></td>
  </tr>
</table>


#### Joueur qui pose la question (602)

Cette réponse renvoi le joueur qui pose la question

Elle retourne une valeur

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>Choix du joueur</td>
    <td>Joueur</td>
    <td>Chaine de caractères</td>
  </tr>
</table>


### Réponses entre 2 clients

#### Accepter demande de partie (700)

Cette réponse permet d’accepter une demande de partie

Cette réponse ne DOIT être envoyé que par un client n’étant pas en partie.

Elle retourne aucune valeur

#### Refuser demande de partie (701)

Cette réponse permet de refuser une demande de partie

Cette réponse ne DOIT être envoyé que par un client n’étant pas en partie.

Elle retourne aucune valeur

#### Réponse (702)

Cette réponse renvoi la réponse à la question posée

Elle retourne une valeur

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>Réponse</td>
    <td>Reponse</td>
    <td>Chaine de caractères</td>
  </tr>
</table>


## Format messages

### Requêtes

Le format des requêtes est le suivant :

Le séparateur de fin de requête est un double \\n

<table>
  <tr>
    <td>REQUETE ID_Requete
Parametre_1: Valeur_1
Parametre_2: Valeur_2
…
</td>
  </tr>
</table>


### Réponse

Le format des réponses est le suivant :

Le séparateur de fin de réponse est un double \\n

Pour utiliser un retour à la ligne dans les valeurs, on doit utiliser un retour chariot (\\r)

<table>
  <tr>
    <td>REPONSE ID_Reponse
Retour_1: Valeur_1
Retour_2: Valeur_2
…
</td>
  </tr>
</table>

 */

#endif
