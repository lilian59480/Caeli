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
 * Fonction d'envoi d'une réponse "pong"
 * \param socket socket d'envoi de la réponse
 */

void traiter_requete_ping (T_Socket socket, const struct sockaddr_in *addr)
{
    T_Reponse reponse;
    reponse = crearep_pong();
    writerep (socket, reponse,addr);
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
        reqtostr(buf,requete);
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

