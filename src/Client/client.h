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
#include <math.h>

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
