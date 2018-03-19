/**
 * \file requetes.h
 */
#ifndef H_PROTOCOLE_REQUETES
#define H_PROTOCOLE_REQUETES

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Includes locaux
#include "../protocole.h"

#define REQ_CODE_PING 1
#define REQ_CODE_DECONNEXION 2
#define REQ_CODE_CONNEXION_SERVEUR_CENTRAL 100
#define REQ_CODE_NOMBRE_CLIENTS_CONNECTES 101
#define REQ_CODE_INFORMATION_CLIENT 102
#define REQ_CODE_PASSER_MODE_PARTIE 103
#define REQ_CODE_PORT_CHAT 104
#define REQ_CODE_CHOIX_JOUEUR 105
#define REQ_CODE_DEMANDE_PARTIE 200
#define REQ_CODE_QUESTION 201
#define REQ_CODE_VALIDER_REPONSE 202
#define REQ_CODE_MESSAGE_CHAT 203

/** Défini la structure d'un parametre */
typedef struct
{
    char nom[TAILLE_PARAM_MAX]; ///< L'identifiant du parametre
    char valeur[TAILLE_PARAM_MAX]; ///< La valeur possible
} T_Requete_parametre;

/** Defini une réponse émise par le serveur */
typedef struct
{
    int identifiant; ///< Le numéro de la reponse, qui l'identifie
    int nbr_parametres; ///< Le nombre de parametres dans notre tableau de parametres
    T_Requete_parametre parametres[NBR_PARAM_MAX]; ///< Représente les parametres afin de completer les reponses
} T_Requete;

void reqtostr (char* str, const T_Requete requete);
void strtoreq (T_Requete* requete, const char* str);
void get_req_param (const T_Requete requete, const char* param, char* resultat);

T_Requete creareq_ping();
T_Requete creareq_deconnexion();
T_Requete creareq_connexion_serveur_central (char* pseudo);
T_Requete creareq_nombre_clients_connectes();
T_Requete creareq_information_client (unsigned long index);
T_Requete creareq_passer_mode_partie (char* client_1, char* client_2, char* client_3, unsigned char partenaire);
T_Requete creareq_port_chat (unsigned char type);
T_Requete creareq_choix_joueur();
T_Requete creareq_demande_partie (short equipe);
T_Requete creareq_question (char* question);
T_Requete creareq_valider_reponse (unsigned short valide, char* message);
T_Requete creareq_message_chat (char* message);

#endif
