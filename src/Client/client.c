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
 * \file client.c
 */
#include "client.h"

sqlite3* bdd;

/**
 * Fonction traitant les signaux reçus
 * \param signal signal reçu
 */
void deroute (int signal)
{
    switch (signal)
    {
        case SIGINT:
            exit (1);
            break;
    }
}

/**
 * Fonction Récupération de la température
 * \param[out] float la température
 * \param[in] la socket de connexion
 */
float recuperer_temperature (const T_Socket socket, struct sockaddr_in* addr_serveur)
{
    T_Requete requete;
    requete = creareq_recup_temp ();
    writereq (socket, requete, addr_serveur);
    // On va voir si on a reçu une reponse
    T_Reponse reponse;
    struct sockaddr_in addr_recu;
    reponse = readrep (socket, &addr_recu);

    if (reponse.identifiant != REP_CODE_OK)
    {
        // Erreur, mauvaise réponse
        T_Buffer erreur = {'\0'};
        get_rep_param (reponse, "Type", erreur);
        syslog (LOG_ERR, "Mauvaise reponse du serveur: Code %d - %s", reponse.identifiant, erreur );
        return -1;
    }

    T_Buffer temp_string;
    get_rep_param (reponse, "Type", temp_string);
    float temperature = strtof (temp_string, NULL);
    // On enregistre la valeur dans la bdd
    ajouter_temperature (bdd, temperature);
    return temperature;
}

/**
 * Fonction Récupération de l'humidité
 * \param[out] float la valeur de l'humidité
 * \param[in] la socket de connexion
 */
float recuperer_humidite (const T_Socket socket, struct sockaddr_in* addr_serveur)
{
    T_Requete requete;
    requete = creareq_recup_hum ();
    writereq (socket, requete, addr_serveur);
    // On va voir si on a reçu une reponse
    T_Reponse reponse;
    struct sockaddr_in addr_recu;
    reponse = readrep (socket, &addr_recu);

    if (reponse.identifiant != REP_CODE_OK)
    {
        // Erreur, mauvaise réponse
        T_Buffer erreur = {'\0'};
        get_rep_param (reponse, "Type", erreur);
        syslog (LOG_ERR, "Mauvaise reponse du serveur: Code %d - %s", reponse.identifiant, erreur );
        return -1;
    }

    T_Buffer hum_string;
    get_rep_param (reponse, "Type", hum_string);
    float humidite = strtof (hum_string, NULL);
    // On enregistre la valeur dans la bdd
    ajouter_humidite (bdd, humidite);
    return humidite;
}

/**
 * Fonction Récupération de la température
 * \param[out] void
 * \param[in] la socket de connexion
 * \param[in] rouge
 * \param[in] bleu
 * \param[in] vert
 * \param[in] texte à afficher sur l'écran
 */
void ecrire_lcd (const T_Socket socket, struct sockaddr_in* addr_serveur, char* texte, char rouge, char vert, char bleu)
{
    T_Requete requete;
    requete = creareq_ecrire_lcd (rouge, vert, bleu, texte);
    writereq (socket, requete, addr_serveur);
    // On va voir si on a reçu une reponse
    T_Reponse reponse;
    struct sockaddr_in addr_recu;
    reponse = readrep (socket, &addr_recu);

    if (reponse.identifiant != REP_CODE_OK)
    {
        // Erreur, mauvaise réponse
        T_Buffer erreur = {'\0'};
        get_rep_param (reponse, "Type", erreur);
        syslog (LOG_ERR, "Mauvaise reponse du serveur: Code %d - %s", reponse.identifiant, erreur );
        return;
    }

    return;
}

/**
 * Fonction ecriture Led
 * \param[out] void
 * \param[in] la socket de connexion
 * \param[in] type
 * \param[in] l'etat de la led (High/low)
 */
void ecrire_led (const T_Socket socket, struct sockaddr_in* addr_serveur, int type, int etat)
{
    T_Requete requete;
    requete = creareq_ecrire_led (type, etat);
    writereq (socket, requete, addr_serveur);
    // On va voir si on a reçu une reponse
    T_Reponse reponse;
    struct sockaddr_in addr_recu;
    reponse = readrep (socket, &addr_recu);

    if (reponse.identifiant != REP_CODE_OK)
    {
        // Erreur, mauvaise réponse
        T_Buffer erreur = {'\0'};
        get_rep_param (reponse, "Type", erreur);
        syslog (LOG_ERR, "Mauvaise reponse du serveur: Code %d - %s", reponse.identifiant, erreur );
        return;
    }

    return;
}


/**
 * Fonction charge de la logique du dialogue avec le serveur
 * \param socket La socket vers le serveur
 */
void dialogue (const T_Socket socket, struct sockaddr_in* addr_serveur)
{
    ecrire_led (socket, addr_serveur, LED_ACTIVITE, LED_ON);
    //T_Buffer loading;
    //sprintf (loading, "%s\n%s", LCD_TEXT_NO_DATA_H, LCD_TEXT_NO_DATA_B);
    //ecrire_lcd (socket, addr_serveur, loading, 0, 0, 255);
    // Recuperation de la valeur de temperature
    float temperature = recuperer_temperature (socket, addr_serveur);
    // Recuperation de la valeur d'humidite
    float humidite = recuperer_humidite (socket, addr_serveur);

    // Ecriture sur le LCD et mise a jour des leds
    if (!isnan (temperature) && !isnan (humidite) )
    {
        T_Buffer lcd, lcd_h, lcd_b;
        char r, v, b;
        int state;
        sprintf (lcd_h, LCD_TEXT_DATA_H, temperature);
        sprintf (lcd_b, LCD_TEXT_DATA_B, humidite);
        sprintf (lcd, "%s\n%s", lcd_h, lcd_b);

        // Todo : Creer une methode
        if ( humidite < 5 || humidite > 85 )
        {
            r = 230;
            v = 160;
            b = 0;
            state = LED_ON;
        }
        else
        {
            r = 0;
            v = 255;
            b = 0;
            state = LED_OFF;
        }

        ecrire_led (socket, addr_serveur, LED_ALERTE, state);
        ecrire_lcd (socket, addr_serveur, lcd, r, v, b);
    }

    ecrire_led (socket, addr_serveur, LED_ACTIVITE, LED_OFF);
}

/**
 * Fonction chargant de verifier que l'on peut se connecter au serveur
 * Si la connection est effective, alors on effectue notre dialogue
 * \param hote Hote a contacter
 * \param port Port a contacter
 */
void init_connexion_serveur (const char* hote, const int port)
{
    // Les informations sur le serveur
    struct sockaddr_in* addr_serveur;
    addr_serveur = sockaddrinit (hote, port);
    // La socket utilise par le client
    T_Socket socket;
    socket = soinit();

    // Si on arrive a utiliser les parametres
    if (addr_serveur != NULL)
    {
        // On essaye de se connecter avec une requete
        T_Requete requete_connexion;
        requete_connexion = creareq_ping ();
        writereq (socket, requete_connexion, addr_serveur);
        // On va voir si on a reçu une erreur ou pas
        T_Reponse reponse;
        struct sockaddr_in addr_recu;
        reponse = readrep (socket, &addr_recu);

        if (reponse.identifiant == REP_CODE_PONG)
        {
            // Tout est bon, on va pouvoir avancer
            dialogue (socket, addr_serveur);
        }
        else
        {
            // Erreur, mauvaise réponse
            syslog (LOG_ERR, "Mauvaise reponse du serveur: Code %d", reponse.identifiant );
        }
    }
    else
    {
        syslog (LOG_ERR, "Impossible de se connecter:%s", strerror (errno) );
    }

    // On ferme le tout
    close (socket);
    sockaddrfree (addr_serveur);
}


/**
 * Main Client
 * \param argc Le nombre d'arguments
 * \param argv Les arguments
 * \retval int La valeur de sortie du programme
 */
int main (int argc, char** argv)
{
    int i;
    // Arguments autorises
    const char* short_opt = "hva:p:";
    struct option long_opt[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"address", required_argument, NULL, 'a'},
        {"port", required_argument, NULL, 'p'},
        {NULL, 0, NULL, 0}
    };
    // Parametres par defaut
    T_Buffer hote = "127.0.0.1";
    int port = 5000;

    // Lectures des arguments
    while ( (i = getopt_long (argc, argv, short_opt, long_opt, NULL) ) != -1)
    {
        switch (i)
        {
            case -1:       /* Plus d'arguments */
            case 0:        /* Argument long */
                break;

            case 'a':
                strncpy (hote, optarg, BUFF_MAX);
                hote[BUFF_MAX] = '\0';
                break;

            case 'p':
                CHECK (port = strtol (optarg, NULL, 10), "Port incorrect");
                break;

            case 'v':
                printf ("Version dev\n");
                return EXIT_SUCCESS;

            case 'h':
            default:
                printf ("Usage: %s [OPTIONS]\n", argv[0]);
                printf ("\t-a, --address\t\tAdresse IP du serveur a contacter [defaut : localhost]\n");
                printf ("\t-p, --port\t\tPort du serveur a contacter [defaut : 5000]\n");
                printf ("\t-h, --help\t\tAffiche cette aide et quitte\n");
                printf ("\t-v, --version\t\tAffiche la version du programme et quitte\n");
                printf ("\n");
                return EXIT_FAILURE;
        }
    }

    // Ouverture de syslog
    openlog ("Caeli Client interne", LOG_PID | LOG_PERROR, LOG_USER);
    // Gestion des signaux
    handle_signal (SIGINT, deroute, 0);

    // Initialisation de la base de donnees
    if (init_bdd (&bdd) != 0)
    {
        return EXIT_FAILURE;
    }

    // Mise en place de la connexion
    init_connexion_serveur (hote, port);
    // Nettoyage de la base de donnees
    nett_bdd (bdd);
    // Fermeture de syslog
    closelog();
    return EXIT_SUCCESS;
}
