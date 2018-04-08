/**
 * \file client.h
 */
#ifndef H_CLIENT_CLIENT
#define H_CLIENT_CLIENT

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
#include <pthread.h>
#include <syslog.h>
#include <getopt.h>

// Includes locaux
#include "../Protocole/protocole.h"
#include "../Protocole/Reponses/reponses.h"
#include "../Protocole/Requetes/requetes.h"
#include "../Reseau/reseau.h"
#include "../Utilitaires/utils.h"
#include "../Utilitaires/signaux.h"
#include "../Utilitaires/clock.h"
#include "../Materiel/materiel.h"
#include "bdd.h"

#define LCD_TEXT_NO_DATA_H "Recuperation des"
#define LCD_TEXT_NO_DATA_B "donnees en cours"

#define LCD_TEXT_DATA_H "Temp: % 2.1f"
#define LCD_TEXT_DATA_B "Humidite: %2.1f %%"


#endif
