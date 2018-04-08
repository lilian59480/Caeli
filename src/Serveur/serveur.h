/**
 * \file serveur_central.h
 */
#ifndef H_SERVEUR_CENTRAL_SERVEUR_CENTRAL
#define H_SERVEUR_CENTRAL_SERVEUR_CENTRAL

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
#include <wait.h>
#include <semaphore.h>
#include <fcntl.h>

// Includes locaux
#include "../Protocole/protocole.h"
#include "../Protocole/Reponses/reponses.h"
#include "../Protocole/Requetes/requetes.h"
#include "../Reseau/reseau.h"
#include "../Utilitaires/utils.h"
#include "../Utilitaires/signaux.h"
#include "../Materiel/grovepi.h"
#include "../Materiel/grove_rgb_lcd.h"
#include "../Materiel/grove_dht.h"
#include "../Materiel/materiel.h"


#endif


