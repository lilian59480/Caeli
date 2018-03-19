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
 * Crée une requete Deconnexion
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_deconnexion()
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_DECONNEXION;
    requete.nbr_parametres = 0;
    return requete;
}

/**
 * Crée une requete Connexion serveur central
 * \param[in] pseudo Le pseudo du client
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_connexion_serveur_central (char* pseudo)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_CONNEXION_SERVEUR_CENTRAL;
    requete.nbr_parametres = 1;
    T_Requete_parametre param_pseudo;
    strcpy (param_pseudo.nom, "Pseudo");
    strncpy (param_pseudo.valeur, pseudo, TAILLE_PARAM_MAX - 1);
    param_pseudo.valeur[TAILLE_PARAM_MAX - 1] = '\0';
    requete.parametres[0] = param_pseudo;
    return requete;
}

/**
 * Crée une requete Nombre de clients connectés
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_nombre_clients_connectes()
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_NOMBRE_CLIENTS_CONNECTES;
    requete.nbr_parametres = 0;
    return requete;
}

/**
 * Crée une requete Information client
 * \param[in] index L'index du client
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_information_client (unsigned long index)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_INFORMATION_CLIENT;
    requete.nbr_parametres = 1;
    T_Requete_parametre param_index;
    strcpy (param_index.nom, "Index");
    sprintf (param_index.valeur, "%ld", index);
    requete.parametres[0] = param_index;
    return requete;
}

/**
 * Crée une requete Passer mode partie
 * \param[in] client_1 Le nom du client 1
 * \param[in] client_2 Le nom du client 2
 * \param[in] client_3 Le nom du client 3
 * \param[in] partenaire Le numéro du partenaire (Entre 1 et 3)
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_passer_mode_partie (char* client_1, char* client_2, char* client_3, unsigned char partenaire)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_PASSER_MODE_PARTIE;
    requete.nbr_parametres = 4;
    T_Requete_parametre param_c1;
    strcpy (param_c1.nom, "Client_1");
    strncpy (param_c1.valeur, client_1, TAILLE_PARAM_MAX - 1);
    param_c1.valeur[TAILLE_PARAM_MAX - 1] = '\0';
    requete.parametres[0] = param_c1;
    T_Requete_parametre param_c2;
    strcpy (param_c2.nom, "Client_2");
    strncpy (param_c2.valeur, client_2, TAILLE_PARAM_MAX - 1);
    param_c2.valeur[TAILLE_PARAM_MAX - 1] = '\0';
    requete.parametres[1] = param_c2;
    T_Requete_parametre param_c3;
    strcpy (param_c3.nom, "Client_3");
    strncpy (param_c3.valeur, client_3, TAILLE_PARAM_MAX - 1);
    param_c3.valeur[TAILLE_PARAM_MAX - 1] = '\0';
    requete.parametres[2] = param_c3;
    T_Requete_parametre param_partenaire;
    strcpy (param_partenaire.nom, "Partenaire");
    sprintf (param_partenaire.valeur, "%d", partenaire);
    requete.parametres[3] = param_partenaire;
    return requete;
}

/**
 * Crée une requete Port chat
 * \param[in] type Le type de chat
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_port_chat (unsigned char type)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_PORT_CHAT;
    requete.nbr_parametres = 1;
    T_Requete_parametre param_type;
    strcpy (param_type.nom, "Type");
    sprintf (param_type.valeur, "%d", type);
    requete.parametres[0] = param_type;
    return requete;
}

/**
 * Crée une requete Choix joueur
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_choix_joueur()
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_CHOIX_JOUEUR;
    requete.nbr_parametres = 0;
    return requete;
}

/**
 * Crée une requete Demande partie
 * \param[in] equipe Si le joueur est avec (1) ou contre nous (-1)
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_demande_partie (short equipe)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_DEMANDE_PARTIE;
    requete.nbr_parametres = 1;
    T_Requete_parametre param_equipe;
    strcpy (param_equipe.nom, "Equipe");
    sprintf (param_equipe.valeur, "%d", equipe);
    requete.parametres[0] = param_equipe;
    return requete;
}

/**
 * Crée une requete Question
 * \param[in] question La question à poser
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_question (char* question)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_QUESTION;
    requete.nbr_parametres = 1;
    T_Requete_parametre param_question;
    strcpy (param_question.nom, "Question");
    strncpy (param_question.valeur, question, TAILLE_PARAM_MAX - 1);
    param_question.valeur[TAILLE_PARAM_MAX - 1] = '\0';
    requete.parametres[0] = param_question;
    return requete;
}

/**
 * Crée une requete Valider réponse
 * \param[in] valide La réponse est valide ou non
 * \param[in] message Un message supplémentaire
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_valider_reponse (unsigned short valide, char* message)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_VALIDER_REPONSE;
    requete.nbr_parametres = 2;
    T_Requete_parametre param_valide;
    strcpy (param_valide.nom, "Valide");
    sprintf (param_valide.valeur, "%d", valide);
    requete.parametres[0] = param_valide;
    T_Requete_parametre param_message;
    strcpy (param_message.nom, "Message");
    strncpy (param_message.valeur, message, TAILLE_PARAM_MAX - 1);
    param_message.valeur[TAILLE_PARAM_MAX - 1] = '\0';
    requete.parametres[1] = param_message;
    return requete;
}

/**
 * Crée une requete Message chat
 * \param[in] message Le message
 * \retval T_Requete La requete préparée
 */
T_Requete creareq_message_chat (char* message)
{
    T_Requete requete;
    memset (&requete, 0, sizeof (T_Requete) );
    requete.identifiant = REQ_CODE_MESSAGE_CHAT;
    requete.nbr_parametres = 1;
    T_Requete_parametre param_message;
    strcpy (param_message.nom, "Message");
    strncpy (param_message.valeur, message, TAILLE_PARAM_MAX - 1);
    param_message.valeur[TAILLE_PARAM_MAX - 1] = '\0';
    requete.parametres[0] = param_message;
    return requete;
}
