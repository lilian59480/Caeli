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

long int writereq (const T_Socket socket, const T_Requete requete);

long int writerep (const T_Socket socket, const T_Reponse reponse);

T_Requete readreq (const T_Socket socket);

T_Reponse readrep (const T_Socket socket);

#endif

