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
