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

#define REQ_CODE_RECUP_TEMP 100
#define REQ_CODE_RECUP_HUM 101
#define REQ_CODE_ECRIRE_LCD 102
#define REQ_CODE_ECRIRE_LED 103
#define REQ_CODE_ECRIRE_BUZZER 104


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
T_Requete creareq_recup_temp();
T_Requete creareq_recup_hum();
T_Requete creareq_ecrire_led (int type, int etat);
T_Requete creareq_ecrire_lcd (int rouge, int vert, int bleu, char* texte);
T_Requete creareq_ecrire_buzzer (int etat);

#endif
