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
 * \file reseau.h
 */
#ifndef H_RESEAU_RESEAU
#define H_RESEAU_RESEAU

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>


// Includes locaux
#include "../Protocole/protocole.h"
#include "../Protocole/Reponses/reponses.h"
#include "../Protocole/Requetes/requetes.h"
#include "../Utilitaires/utils.h"

/** La taille de buffer */
#define BUFF_MAX 1024

/** Alias pour les sockets */
typedef int T_Socket;

/** Défini un buffer */
typedef char T_Buffer[BUFF_MAX] ;

T_Socket soinit();

struct sockaddr_in* sockaddrinit (const char* adresse, const int port);

struct sockaddr_in* sockaddrinit_serv (const int port);

void sockaddrfree (struct sockaddr_in* socketaddr);

long int writereq (const T_Socket socket, const T_Requete requete, const struct sockaddr_in* address);

long int writerep (const T_Socket socket, const T_Reponse reponse, const struct sockaddr_in* address);

T_Requete readreq (const T_Socket socket, struct sockaddr_in* address);

T_Reponse readrep (const T_Socket socket, struct sockaddr_in* address);

#endif

