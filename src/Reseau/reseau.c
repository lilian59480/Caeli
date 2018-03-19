/**
 * \file reseau.c
 */

#include "reseau.h"

/**
 * Initialise une socket
 * \retval T_Socket Une socket
 */
T_Socket soinit()
{
    return socket ( AF_INET, SOCK_STREAM, 0 );
}

/**
 * Initialise l'adresse et les informations sockaddr_in
 * \param[in] adresse L'adresse
 * \param[in] port Le port
 * \retval struct sockaddr_in* La sockaddr_in initialisé
 */
struct sockaddr_in* sockaddrinit (const char* adresse, const int port)
{
    struct sockaddr_in* as;
    struct hostent* hote;
    as = (struct sockaddr_in*) malloc (sizeof (struct sockaddr_in) );

    if (as == NULL)
    {
        return NULL;
    }

    hote = gethostbyname (adresse);

    if (hote == NULL)
    {
        herror ("ERREUR GETHOSTBYNAME");
        sockaddrfree (as);
        return NULL;
    }

    memset (as, 0, sizeof (struct sockaddr_in) );
    as->sin_family = AF_INET;
    as->sin_port = htons (port);
    as->sin_addr = * ( (struct in_addr*) hote->h_addr);
    memset ( as->sin_zero, 0, 8 );
    return as;
}

/**
 * Initialise l'adresse et les informations sockaddr_in pour une utilisation serveur
 * \param[in] port Le port
 * \retval struct sockaddr_in* La sockaddr_in initialisé
 */
struct sockaddr_in* sockaddrinit_serv (const int port)
{
    struct sockaddr_in* as;
    as = (struct sockaddr_in*) malloc (sizeof (struct sockaddr_in) );

    if (as == NULL)
    {
        return NULL;
    }

    memset (as, 0, sizeof (struct sockaddr_in) );
    as->sin_family = AF_INET;
    as->sin_port = htons (port);
    as->sin_addr.s_addr = htonl (INADDR_ANY);
    memset ( as->sin_zero, 0, 8 );
    return as;
}


/**
 * Nettoye une sockaddr_in
 * \param[in] socketaddr Une sockaddr_in initialisé auparavant
 */
void sockaddrfree (struct sockaddr_in* socketaddr)
{
    free (socketaddr);
}

/**
 * Envoie une requete par le réseau
 * \param[in] socket La socket à utiliser
 * \param[in] requete La requete à envoyer
 * \retval long int La taille des données envoyées
 */
long int writereq (const T_Socket socket, const T_Requete requete)
{
    T_Buffer buffer;
    long int length;
    reqtostr (buffer, requete);
    // On va envoyer une réponse
    CHECK ( length = write (socket, buffer, strlen (buffer) + 1), "ERREUR WRITE");
    // On teste si le write est bien passé
    return length;
}

/**
 * Envoie une réponse par le réseau
 * \param[in] socket La socket à utiliser
 * \param[in] reponse La reponse à envoyer
 * \retval long int La taille des données envoyées
 */
long int writerep (const T_Socket socket, const T_Reponse reponse)
{
    T_Buffer buffer;
    long int length;
    reptostr (buffer, reponse);
    // On va envoyer une réponse
    CHECK ( length = write (socket, buffer, strlen (buffer) + 1), "ERREUR WRITE");
    // On teste si le write est bien passé
    return length;
}

/**
 * Lit une requete par le réseau
 * \param[in] socket La socket à utiliser
 * \retval T_Requete La requete reçu
 */
T_Requete readreq (const T_Socket socket)
{
    T_Buffer buffer;
    T_Requete requete;
    long int length;
    CHECK (length = read (socket, buffer, BUFF_MAX), "ERREUR READ");

    // Si length est "gal à 0, on essaye de se deconnecter
    if (length == 0)
    {
        return creareq_deconnexion();
    }

    // On va transformer notre buffer en une structure de type T_Requete
    strtoreq (&requete, buffer);
    return requete;
}

/**
 * Lit une reponse par le réseau
 * \param[in] socket La socket à utiliser
 * \retval T_Reponse La reponse reçu
 */
T_Reponse readrep (const T_Socket socket)
{
    T_Buffer buffer;
    T_Reponse reponse;
    long int length;
    CHECK (length = read (socket, buffer, BUFF_MAX), "ERREUR READ");
    // On va transformer notre buffer en une structure de type T_Requete
    strtorep (&reponse, buffer);
    return reponse;
}


