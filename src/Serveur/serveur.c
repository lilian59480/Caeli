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
 * \file serveur_central.c
 */
#include "serveur.h"

volatile sig_atomic_t stop_serveur;

/**
 * Traitement des signaux par déroutage
 * \param signal Le signal qu'on va traiter
 */
void deroute_serveur (int signal)
{
    int status;
    pid_t pidchld;

    switch (signal)
    {
        case SIGCHLD:
            // On va récupérer le status renvoyé par wait, ainsi que le PID du fils
            pidchld = wait (&status);
            fprintf (stderr, "Le processus de service [PID:%d] vient de se terminer sur le signal SIGCHLD(%d) avec le status : %d\n", pidchld, signal, status);
            break;

        case SIGINT:
            fprintf (stderr, "SIGINT : Fermeture du serveur\n");
            CHECK (kill (0, SIGUSR1), "ERREUR KILL");
            sleep (5);
            stop_serveur = !stop_serveur;
            break;
    }
}

/**
 * Traitement des signaux par déroutage
 * \param signal Le signal qu'on va traiter
 */
void deroute_clients (int signal)
{
    switch (signal)
    {
        case SIGUSR1:
            exit (1);
            break;
    }
}

/**
 * Fonction d'envoi d'une réponse de humidite
 * \param socket socket d'envoi de la réponse
 */
void traiter_requete_humidite (T_Socket socket, const struct sockaddr_in* addr)
{
    float humidite;
    float unused;
    GroveDHT dht;
    dht.module = BLUE_MODULE;
    dht.pin = DHT_PIN;
    DHT_getSafeData (&dht, &unused, &humidite);
    T_Buffer type;
    snprintf (type, BUFF_MAX - 1, "%f", humidite);
    T_Reponse reponse;
    reponse = crearep_ok (type);
    writerep (socket, reponse, addr);
    return;
}

/**
 * Fonction d'envoi d'une réponse de temperature
 * \param socket socket d'envoi de la réponse
 */
void traiter_requete_temperature (T_Socket socket, const struct sockaddr_in* addr)
{
    float temperature;
    float unused;
    GroveDHT dht;
    dht.module = BLUE_MODULE;
    dht.pin = DHT_PIN;
    DHT_getSafeData (&dht, &temperature, &unused);
    T_Buffer type;
    snprintf (type, BUFF_MAX - 1, "%f", temperature);
    T_Reponse reponse;
    reponse = crearep_ok (type);
    writerep (socket, reponse, addr);
    return;
}

/**
 * Fonction d'envoi d'une réponse pour les leds
 * \param socket socket d'envoi de la réponse
 */
void traiter_requete_led (T_Socket socket, const struct sockaddr_in* addr, const T_Requete requete)
{
    T_Buffer texte;
    int type;
    int etat;
    get_req_param (requete, "Type", texte);
    type = strtol (texte, NULL, 10);
    get_req_param (requete, "Etat", texte);
    etat = strtol (texte, NULL, 10);
    pinMode (type, G_OUTPUT);
    int dw;
    bool led = G_LOW;

    if (etat == LED_ON)
    {
        led = G_HIGH;
    }

    dw = digitalWrite (type, led);

    if (dw == 0)
    {
        // Lancer une erreur
        T_Reponse reponse;
        reponse = crearep_erreur ("Etat led erreur");
        writerep (socket, reponse, addr);
        return;
    }

    T_Reponse reponse;
    reponse = crearep_ok ("");
    writerep (socket, reponse, addr);
    return;
}

/**
 * Fonction d'envoi d'une réponse pour le LCD
 * \param socket socket d'envoi de la réponse
 */
void traiter_requete_lcd (T_Socket socket, const struct sockaddr_in* addr, const T_Requete requete)
{
    T_Buffer texte;
    char r, v, b;
    get_req_param (requete, "Rouge", texte);
    r = strtol (texte, NULL, 10);
    get_req_param (requete, "Vert", texte);
    v = strtol (texte, NULL, 10);
    get_req_param (requete, "Bleu", texte);
    b = strtol (texte, NULL, 10);
    get_req_param (requete, "Texte", texte);
    GroveLCD lcd = GroveLCD_init();
    GroveLCD_connect (&lcd);

    if (! GroveLCD_isConnected (&lcd) )
    {
        // Lancer une erreur
        T_Reponse reponse;
        reponse = crearep_erreur ("LCD non connecte");
        writerep (socket, reponse, addr);
        return;
    }

    int error;
    error = GroveLCD_setRGB (&lcd, r, v, b);

    if (error)
    {
        // Lancer une erreur
        T_Reponse reponse;
        reponse = crearep_erreur ("Couleur LCD erreur");
        writerep (socket, reponse, addr);
        return;
    }

    error =  GroveLCD_setText (&lcd, texte);

    if (error)
    {
        // Lancer une erreur
        T_Reponse reponse;
        reponse = crearep_erreur ("Texte LCD erreur");
        writerep (socket, reponse, addr);
        return;
    }

    T_Reponse reponse;
    reponse = crearep_ok ("");
    writerep (socket, reponse, addr);
    return;
}

/**
 * Fonction d'envoi d'une réponse "pong"
 * \param socket socket d'envoi de la réponse
 */
void traiter_requete_ping (T_Socket socket, const struct sockaddr_in* addr)
{
    T_Reponse reponse;
    reponse = crearep_pong();
    writerep (socket, reponse, addr);
    return;
}

/**
 * Fonction d'envoi d'une réponse "pong"
 * \param socket socket d'envoi de la réponse
 */
void requete_invalide (T_Socket socket, const struct sockaddr_in* addr)
{
    T_Reponse reponse;
    reponse = crearep_requete_invalide();
    writerep (socket, reponse, addr);
    return;
}

/**
 * Représente la logique du dialogue pour le serveur central
 * \param socket_dialogue La socket de dialogue
 * \param addr_client addresse du client
 */
int dialogue_serveur (T_Socket socket)
{
    // Une requete sous forme de structure
    T_Requete requete;
    T_Buffer buf;
    reqtostr (buf, requete);
    // On va lire la requete envoyé par le client
    struct sockaddr_in addr;
    requete = readreq (socket, &addr);
    printf ("Nouvelle requete de %s\n", inet_ntoa (addr.sin_addr) );

    // On parcours la liste des requetes qu'on connait
    switch (requete.identifiant)
    {
        case REQ_CODE_PING:
            traiter_requete_ping (socket, &addr);
            break;

        case REQ_CODE_RECUP_TEMP:
            traiter_requete_temperature (socket, &addr);
            break;

        case REQ_CODE_RECUP_HUM:
            traiter_requete_humidite (socket, &addr);
            break;

        case REQ_CODE_ECRIRE_LED:
            traiter_requete_led (socket, &addr, requete);
            break;

        case REQ_CODE_ECRIRE_LCD:
            traiter_requete_lcd (socket, &addr, requete);
            break;

        default:
            requete_invalide (socket, &addr);
            break;
    }

    return 0;
}

/**
 * Main Serveur
 * \retval int La valeur de sortie du programme
 */
int main()
{
    // La socket utilisé par le serveur
    T_Socket serveur;
    // La structure de l'adresse de notre serveur
    struct sockaddr_in* addr_serveur;
    // On prépare notre adresse
    addr_serveur = sockaddrinit_serv (5000);
    // On initialise une socket
    serveur = soinit();
    // On va demander a la machine de nous assigner ce qu'on a demandé
    CHECK (bind (serveur, (struct sockaddr*) addr_serveur, sizeof (struct sockaddr) ), "ERREUR BIND");
    // On va dérouter les signaux SIG_CHLD afin d'éviter la création de processus zombies
    handle_signal (SIGCHLD, deroute_serveur, SA_RESTART);
    handle_signal (SIGINT, deroute_serveur, 0);
    handle_signal (SIGUSR1, SIG_IGN, 0);
    stop_serveur = FALSE;

    // Initialiser le materiel
    if (!initGrovePi() )
    {
        return -1;
    }

    // On écoute a présent
    while (!stop_serveur)
    {
        stop_serveur = dialogue_serveur (serveur);
    }

    // Il faut fermer les sockets avec close dès qu'on en a plus besoin
    close (serveur);
    sockaddrfree (addr_serveur);
    return 0;
}

