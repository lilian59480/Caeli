/**
 * \file client.h
 */
#ifndef H_CLIENT_CLIENT
#define H_CLIENT_CLIENT

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
#include <wait.h>
#include <pthread.h>


// Includes locaux
#include "../Protocole/protocole.h"
#include "../Protocole/Reponses/reponses.h"
#include "../Protocole/Requetes/requetes.h"
#include "../Reseau/reseau.h"
#include "../Utilitaires/utils.h"
#include "../Utilitaires/signaux.h"
#include "../Utilitaires/clock.h"

#define MCS_CONNEXION_TAILLE_CHAMPS 30

#define MCS_CONNEXION_HOTE_MIN 2
#define MCS_CONNEXION_PORT_MIN 2
#define MCS_CONNEXION_PSEUDO_MIN 2

#define MCS_CONNEXION_HOTE_MAX 30
#define MCS_CONNEXION_PORT_MAX 5
#define MCS_CONNEXION_PSEUDO_MAX 30


#define NBR_CLIENTS_MAX 60

typedef enum
{
    DISPONIBLE,
    EN_PARTIE,
} T_Etat_Joueur;

typedef struct
{
    char pseudo[TAILLE_PARAM_MAX - 1];
    unsigned int port;
    T_Etat_Joueur etat_joueur;
} T_Info_Joueur;

typedef T_Info_Joueur T_Infos_Joueurs[NBR_CLIENTS_MAX];

#endif

