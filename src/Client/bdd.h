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
 * \file dbb.h
 */
#ifndef H_CLIENT_BDD
#define H_CLIENT_BDD

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <sqlite3.h>

// Includes locaux
#include "../Utilitaires/utils.h"

#define REQUETE_CREATION_TABLE_TEMPERATURE "CREATE TABLE IF NOT EXISTS temperature\
    ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
    valeur FLOAT NOT NULL , \
    datetime DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP);"

#define REQUETE_CREATION_TABLE_HUMIDITE "CREATE TABLE IF NOT EXISTS humidite\
    ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
    valeur FLOAT NOT NULL , \
    datetime DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP);"

#define REQUETE_INSERTION_TEMPERATURE "INSERT INTO temperature\
    (valeur) VALUES (?)"

#define REQUETE_INSERTION_HUMIDITE "INSERT INTO humidite\
    (valeur) VALUES (?)"

char init_bdd (sqlite3** bdd);
void nett_bdd (sqlite3* bdd);

char ajouter_temperature (sqlite3* bdd, float temperature);
char ajouter_humidite (sqlite3* bdd, float humidite);

#endif
