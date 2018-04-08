/**
 * \file requetes.c
 */
#include "requetes.h"

/**
 * Transforme une requete en chaine de caractères
 * \param[out] str La chaine de caractères obtenu
 * \param[in] requete La requete à transformer
 */
void reqtostr (char* str, const T_Requete requete)
{
    int i;
    // On met l'indentifiant de requete
    sprintf (str, "REQUETE %d\n", requete.identifiant);

    // On ajoute les parametres
    for (i = 0; i < requete.nbr_parametres; i += 1)
    {
        char parametre[TAILLE_PARAM_MAX * 2];
        char valeur[TAILLE_PARAM_MAX];
        strncpy (valeur, requete.parametres[i].valeur, TAILLE_PARAM_MAX - 1);
        strnltocr (valeur);
        sprintf (parametre, "%s:%s\n", requete.parametres[i].nom, valeur);
        strcat (str, parametre);
    }

    strcat (str, "\n");
}

/**
 * Parse une chaine de caractéres en requete
 * \param[in] str La chaine de caractéres a parser
 * \param[out] requete La requete obtenu
 */
void strtoreq (T_Requete* requete, const char* str)
{
    char* copie_str;
    char* parametre;
    char identifiant[TAILLE_PARAM_MAX];
    char valeur[TAILLE_PARAM_MAX];
    T_Requete_parametre param;
    int i = 0;
    // On reset la structure
    memset (requete, 0, sizeof (T_Requete) );
    // On récupére le numéro de requete
    sscanf (str, "REQUETE %d\n", & (requete->identifiant) );
    // On fait une copie de la chiane de caractéres d'origine
    copie_str = (char*) malloc ( (strlen (str) + 1) * sizeof (char) );
    strcpy (copie_str, str);
    // Maintenant, on récupére toutes les lignes
    parametre = strtok (copie_str, "\n");

    while (parametre != NULL && i < NBR_PARAM_MAX)
    {
        // On récupére chaque morceaux
        sscanf (parametre, "%[^:]:%[^\n]", identifiant, valeur);

        if (strcmp (identifiant, parametre) != 0)
        {
            // On transforme nos \r en \n afin de retrouver des chaines normales
            strcrtonl (valeur);
            // On reset la structure
            memset (&param, 0, sizeof (T_Requete_parametre) );
            // On assigne les valeurs
            strcpy (param.nom, identifiant);
            strcpy (param.valeur, valeur);
            // Et on le met a notre structure
            requete->parametres[i] = param;
            // On incrémente
            i++;
        }

        // On continue notre découpe de parametres
        parametre = strtok (NULL, "\n");
    }

    requete->nbr_parametres = i;
}

/**
 * Crée une requete Ping
 * \param requete requête à traiter
 * \param param paramètres à trouver
 * \param resultat paramètres trouvés après traitement
 */
void get_req_param (const T_Requete requete, const char* param, char* resultat)
{
    int i;
    strcpy (resultat, "");

    for (i = 0; i < requete.nbr_parametres; i++)
    {
        if (strcmp (param, requete.parametres[i].nom) == 0)
        {
            strcpy (resultat, requete.parametres[i].valeur);
            return;
        }
    }
}

/**
 * Crée une requete Ping
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_ping()
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_PING;
    requete.nbr_parametres = 0;
    return requete;
}

/**
 * Crée une requete de récupération de Température
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_recup_temp()
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_RECUP_TEMP;
    requete.nbr_parametres = 0;
    return requete;
}

/**
 * Crée une requete de récupération d'Humidité
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_recup_hum()
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_RECUP_HUM;
    requete.nbr_parametres = 0;
    return requete;
}

/**
 * Crée une requete Demande partie
 * \param[in] equipe Si le joueur est avec (1) ou contre nous (-1)
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_ecrire_buzzer (int etat)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_ECRIRE_BUZZER;
    requete.nbr_parametres = 1;
    T_Requete_parametre param_etat;
    strcpy (param_etat.nom, "Etat");
    sprintf (param_etat.valeur, "%d", etat);
    requete.parametres[0] = param_etat;
    return requete;
}

/**
 * Crée une requete ecrire led
 * \param[in] int représentant la LED
 * \param[in] Etat LED (high=1/low=0)
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_ecrire_led (int type, int etat)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_ECRIRE_LED;
    requete.nbr_parametres = 2;
    T_Requete_parametre param_couleur;
    strcpy (param_couleur.nom, "Type");
    sprintf (param_couleur.valeur, "%d", type);
    requete.parametres[0] = param_couleur;
    T_Requete_parametre param_etat;
    strcpy (param_etat.nom, "Etat");
    sprintf (param_etat.valeur, "%d", etat);
    requete.parametres[1] = param_etat;
    return requete;
}

/**
 * Crée une requete ecrire led
 * \param[in] int représentant la LED
 * \param[in] Etat LED (high=1/low=0)
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_ecrire_lcd (int rouge, int vert, int bleu, char* texte)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_ECRIRE_LCD;
    requete.nbr_parametres = 4;
    T_Requete_parametre param_couleur_r;
    strcpy (param_couleur_r.nom, "Rouge");
    sprintf (param_couleur_r.valeur, "%d", rouge);
    requete.parametres[0] = param_couleur_r;
    T_Requete_parametre param_couleur_v;
    strcpy (param_couleur_v.nom, "Vert");
    sprintf (param_couleur_v.valeur, "%d", vert);
    requete.parametres[1] = param_couleur_v;
    T_Requete_parametre param_couleur_b;
    strcpy (param_couleur_b.nom, "Bleu");
    sprintf (param_couleur_b.valeur, "%d", bleu);
    requete.parametres[2] = param_couleur_b;
    T_Requete_parametre param_texte;
    strcpy (param_texte.nom, "Texte");
    strncpy (param_texte.valeur, texte, TAILLE_PARAM_MAX - 1);
    requete.parametres[3] = param_texte;
    return requete;
}
