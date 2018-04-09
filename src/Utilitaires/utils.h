/*
    Copyright (c) 2018 Lilian Petitpas & Hugo Dooms

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software
    is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * \file utils.h
 */
#ifndef H_UTILS
#define H_UTILS


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
 *Station de régulation d'air

# Principe

Le projet consiste en une raspberry pi3 associé un shield GrovePi.

On connecte sur le shield un capteur de température et d'humidité.
Dans le cas ou les conditions de l'air sont trop dégradé ou inadapté on alerte l'utilisateur que ce soit visuelement (sgnal lumineux) ou bien par une alerte si celui-ci est connecté à la station

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
</table>


### Requêtes « bas niveau » (0XX)

#### Ping (001)

Cette requête sert à vérifier la connexion avec un client.

Cette requête peut être envoyé si le client est déconnecté.

Elle ne prend aucun paramètre.

### Requêtes entre le serveur central et un client

#### Récupération de la température (100)

Cette requête sert à récupérer la température lue par le capteur

Elle ne prend aucun paramètre.

#### Récupération de l'humidité (101)

Cette requête sert à récupérer l'humidité lue par le capteur

Elle ne prend aucun paramètre.

#### Requête d'écriture sur le LCD (102)

Cette requête sert dmander l'écriture des informations sur l'écran LCD.

Elle prend 4 paramètres :

<table>
  <tr>
    <td>Nom</td>
    <td>Type</td>
    <td>Description</td>
    <td>Remarque</td>
  </tr>
  <tr>
    <td>Rouge</td>
    <td>int</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>bleu</td>
    <td>int</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>vert</td>
    <td>int</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>texte</td>
    <td>char*</td>
    <td></td>
    <td>texte a afficher sur le lcd</td>
  </tr>
</table>

#### Requete ecrire LED (103)

Cette requête sert Renseigner et controler l'état d'une LED.

Elle prend 2 paramètre :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td></td>
    <td>type</td>
    <td>int</td>
  </tr>
  <tr>
    <td>Etat de la led</td>
    <td>etat</td>
    <td>int</td>
  </tr>
</table>


#### Requete d'éclencher avertisseur sonore (104)

Cette requête sert à demander lenclenchement de l'avertisseur sonore.

Elle prend 1 paramètre :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
    <td>Remarque</td>
  </tr>
  <tr>
    <td>Etat a affecter au buzzer</td>
    <td>etat</td>
    <td>int</td>
    <td></td>
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
    <td>Réponses code Erreur ou valide</td>
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

### Réponses entre le serveur central et un client

#### Rep Ok (600)

Cette réponse transmet le bon fonctionnement d'une requête.
Elle retourne une valeur

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td></td>
    <td>type</td>
    <td>char*</td>
  </tr>
</table>


#### Reponse avec code Erreur (601)

Cette réponse transmet le code Erreur dans le cas d'un problème d'éxécution.
Elle retourne 1 valeur :

<table>
  <tr>
    <td>Description</td>
    <td>Nom</td>
    <td>Type</td>
  </tr>
  <tr>
    <td>code d'erreur</td>
    <td>type</td>
    <td>char*</td>
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
