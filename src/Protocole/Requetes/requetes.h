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
