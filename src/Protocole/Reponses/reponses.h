/**
 * \file reponses.h
 */
#ifndef H_PROTOCOLE_REPONSES
#define H_PROTOCOLE_REPONSES

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Includes locaux
#include "../protocole.h"

#define REP_CODE_PONG 500
#define REP_CODE_REQUETE_INVALIDE 501
#define REP_CODE_ACQUITTEMENT 502
#define REP_CODE_PORTS_DISPONIBLES 503
#define REP_CODE_NOMBRE_CLIENTS 600
#define REP_CODE_INFORMATION_CLIENT 601
#define REP_CODE_JOUEUR_POSE_QUESTION 602
#define REP_CODE_ACCEPTER_DEMANDE_PARTIE 700
#define REP_CODE_REFUSER_DEMANDE_PARTIE 701

/** Défini la structure d'un parametre */
typedef struct
{
    char nom[TAILLE_PARAM_MAX]; ///< L'identifiant du parametre
    char valeur[TAILLE_PARAM_MAX]; ///< La valeur possible
} T_Reponse_parametre;

/** Defini une réponse émise par le serveur */
typedef struct
{
    int identifiant; ///< Le numéro de la reponse, qui l'identifie
    int nbr_parametres; ///< Le nombre de parametres dans notre tableau de parametres
    T_Reponse_parametre parametres[NBR_PARAM_MAX]; ///< Représente les parametres afin de completer les reponses
} T_Reponse;

void reptostr (char* str, const T_Reponse reponse);
void strtorep (T_Reponse* reponse, const char* str);
void get_rep_param (const T_Reponse reponse, const char* param, char* resultat);

T_Reponse crearep_pong();
T_Reponse crearep_requete_invalide();
T_Reponse crearep_acquittement();
T_Reponse crearep_ports_disponibles (unsigned short type, unsigned int port);
T_Reponse crearep_nombre_clients (unsigned long clients);
T_Reponse crearep_information_client (char* pseudo, unsigned int port);
T_Reponse crearep_joueur_pose_question (char* joueur);
T_Reponse crearep_accepter_demande_partie();
T_Reponse crearep_refuser_demande_partie();

#endif
