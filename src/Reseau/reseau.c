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
 * \file reseau.c
 */

#include "reseau.h"

/**
 * Initialise une socket
 * \retval T_Socket Une socket
 */
T_Socket soinit()
{
    return socket ( AF_INET, SOCK_DGRAM, 0 );
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
 * \param[in] address L'addresse a envoyer la requete
 * \retval long int La taille des données envoyées
 */
long int writereq (const T_Socket socket, const T_Requete requete, const struct sockaddr_in* address)
{
    T_Buffer buffer;
    long int length;
    reqtostr (buffer, requete);
    socklen_t addr_length = sizeof (struct sockaddr_in);
    // On va envoyer une réponse
    CHECK ( length = sendto (socket, buffer, strlen (buffer) + 1, 0, (struct sockaddr*) address, addr_length), "ERREUR WRITE");
    // On teste si le write est bien passé
    return length;
}

/**
 * Envoie une reponse par le réseau
 * \param[in] socket La socket à utiliser
 * \param[in] reponse La requete à envoyer
 * \retval long int La taille des données envoyées
 */
long int writerep (const T_Socket socket, const T_Reponse reponse, const struct sockaddr_in* address)
{
    T_Buffer buffer;
    long int length;
    reptostr (buffer, reponse);
    socklen_t addr_length = sizeof (struct sockaddr_in);
    // On va envoyer une réponse
    CHECK ( length = sendto (socket, buffer, strlen (buffer) + 1, 0, (struct sockaddr*) address, addr_length), "ERREUR WRITE");
    // On teste si le write est bien passé
    return length;
}

/**
 * Lit une requete par le réseau
 * \param[in] socket La socket à utiliser
 * \param[out] address L'addresse a envoyer la requete
 * \retval T_Requete La requete reçu
 */
T_Requete readreq (const T_Socket socket, struct sockaddr_in* address)
{
    T_Buffer buffer;
    T_Requete requete;
    long int length;
    socklen_t addr_length = sizeof (struct sockaddr);
    CHECK (length = recvfrom (socket, buffer, BUFF_MAX, 0, (struct sockaddr*) address, &addr_length), "ERREUR READ");
    // On va transformer notre buffer en une structure de type T_Requete
    strtoreq (&requete, buffer);
    return requete;
}

/**
 * Lit une reponse par le réseau
 * \param[in] socket La socket à utiliser
 * \param[out] address L'addresse a envoyer la requete
 * \retval T_Reponse La reponse reçu
 */
T_Reponse readrep (const T_Socket socket, struct sockaddr_in* address)
{
    T_Buffer buffer;
    T_Reponse reponse;
    long int length;
    socklen_t addr_length = sizeof (struct sockaddr);
    CHECK (length = recvfrom (socket, buffer, BUFF_MAX, 0, (struct sockaddr*) address, &addr_length), "ERREUR READ");
    // On va transformer notre buffer en une structure de type T_Reponse
    strtorep (&reponse, buffer);
    return reponse;
}


