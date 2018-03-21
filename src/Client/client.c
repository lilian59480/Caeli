/**
 * \file client.c
 */
#include "client.h"

/**
 * fonction traitant les signaux reçus
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


void message_erreur (char* mesg_erreur)
{
    fprintf (stderr, mesg_erreur);
}

/**
 * fonction de gestion d'un thread de ping
 * \param socket socket de liaison vers le serveur
 */
void dialogue_serveur (T_Socket socket)
{
    (void) socket;
}

/**
 * fonction gérant l'initialisation du serveur
 */
void init_connexion_serveur()
{
    const char* hote = "127.0.0.1";
    int port = 5000;
    // Les informations sur le serveur
    struct sockaddr_in* addr_serveur;
    // La socket utilisé par le client
    T_Socket client;
    client = soinit();
    addr_serveur = sockaddrinit (hote, port);

    // Si on arrive a utiliser les parametres
    if (addr_serveur != NULL)
    {
        // On essaye de se connecter avec une requete
        T_Requete requete_connexion;
        requete_connexion = creareq_ping ();
        writereq (client, requete_connexion, addr_serveur);
        // On va voir si on a reçu une erreur ou pas
        T_Reponse reponse;
        struct sockaddr_in addr_recu;
        reponse = readrep (client, &addr_recu);

        if (reponse.identifiant == REP_CODE_PONG)
        {
            // Tout est bon, on va pouvoir avancer
            printf("OK,%s",inet_ntoa(addr_recu.sin_addr));
        }
        else
        {
            // Erreur, mauvaise réponse
            T_Buffer mes;
            sprintf (mes, "Mauvaise reponse du serveur: Code %d", reponse.identifiant);
            message_erreur (mes);
        }
    }
    else
    {
        T_Buffer mes;
        sprintf (mes, "Impossible de se connecter:%s", strerror (errno) );
        message_erreur (mes);
    }

// On ferme le tout
close (client);
sockaddrfree (addr_serveur);
}


/**
 * Main Client
 * \param argc Le nombre d'arguments
 * \param argv Les arguments
 * \retval int La valeur de sortie du programme
 */
int main ()
{
    handle_signal (SIGINT, deroute, 0);
    init_connexion_serveur();
    return EXIT_SUCCESS;
}
