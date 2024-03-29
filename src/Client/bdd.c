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
 * \file bdd.c
 */
#include "bdd.h"

/**
 * Ajoute une valeur d'humidite dans la base de donnees
 * \param bdd La connexion a la base de donnees
 * \param humidite La valeur d'humidite a ajouter
 * \retval char Reussite ou non de l'initialisation
 */
char ajouter_humidite (sqlite3* bdd, float humidite)
{
    sqlite3_stmt* prepared_stmt;
    int result = sqlite3_prepare_v2 (bdd, REQUETE_INSERTION_HUMIDITE, -1, &prepared_stmt, NULL);

    if ( result != SQLITE_OK )
    {
        syslog (LOG_ERR, "Erreur lors de la preparation de la requete:%s", sqlite3_errmsg (bdd) );
        return 1;
    }

    sqlite3_bind_double (prepared_stmt, 1, humidite);

    if ( result != SQLITE_OK )
    {
        syslog (LOG_ERR, "Erreur lors de l'ajout des elements de la requete:%s", sqlite3_errmsg (bdd) );
        return 1;
    }

    // Execution de la requete
    result = sqlite3_step (prepared_stmt);

    if ( result != SQLITE_DONE )
    {
        syslog (LOG_ERR, "Erreur lors de l'execution de la requete:%s", sqlite3_errmsg (bdd) );
        return 1;
    }

    // Nettoyage
    result = sqlite3_finalize (prepared_stmt);

    if ( result != SQLITE_OK )
    {
        syslog (LOG_ERR, "Erreur lors de la finalisation de la requete:%s", sqlite3_errmsg (bdd) );
        return 1;
    }

    return 0;
}

/**
 * Ajoute une temperature dans la base de donnees
 * \param bdd La connexion a la base de donnees
 * \param temperature La temperature a ajouter
 * \retval char Reussite ou non de l'initialisation
 */
char ajouter_temperature (sqlite3* bdd, float temperature)
{
    sqlite3_stmt* prepared_stmt;
    int result = sqlite3_prepare_v2 (bdd, REQUETE_INSERTION_TEMPERATURE, -1, &prepared_stmt, NULL);

    if ( result != SQLITE_OK )
    {
        syslog (LOG_ERR, "Erreur lors de la preparation de la requete:%s", sqlite3_errmsg (bdd) );
        return 1;
    }

    result = sqlite3_bind_double (prepared_stmt, 1, temperature);

    if ( result != SQLITE_OK )
    {
        syslog (LOG_ERR, "Erreur lors de l'ajout des elements de la requete:%s", sqlite3_errmsg (bdd) );
        return 1;
    }

    // Execution de la requete
    result = sqlite3_step (prepared_stmt);

    if ( result != SQLITE_DONE )
    {
        syslog (LOG_ERR, "Erreur lors de l'execution de la requete:%s", sqlite3_errmsg (bdd) );
        return 1;
    }

    // Nettoyage
    result = sqlite3_finalize (prepared_stmt);

    if ( result != SQLITE_OK )
    {
        syslog (LOG_ERR, "Erreur lors de la finalisation de la requete:%s", sqlite3_errmsg (bdd) );
        return 1;
    }

    return 0;
}

/**
 * Creer les tables si la structure n'existe pas
 * \param bdd La connexion a la base de donnees
 * \retval char Reussite ou non de l'initialisation
 */
char creation_bdd (sqlite3* bdd)
{
    sqlite3_stmt* prepared_stmt;
    // Preparation de la requete
    char requetes[2][1024] = {REQUETE_CREATION_TABLE_TEMPERATURE, REQUETE_CREATION_TABLE_HUMIDITE};
    int i;

    for (i = 0; i < 2; i++)
    {
        int result = sqlite3_prepare_v2 (bdd, requetes[i], -1, &prepared_stmt, NULL);

        if ( result != SQLITE_OK )
        {
            syslog (LOG_ERR, "Erreur lors de la preparation de la requete:%s", sqlite3_errmsg (bdd) );
            return 1;
        }

        // Execution de la requete
        result = sqlite3_step (prepared_stmt);

        if ( result != SQLITE_DONE )
        {
            syslog (LOG_ERR, "Erreur lors de l'execution de la requete:%s", sqlite3_errmsg (bdd) );
            return 1;
        }

        // Nettoyage
        result = sqlite3_finalize (prepared_stmt);

        if ( result != SQLITE_OK )
        {
            syslog (LOG_ERR, "Erreur lors de la finalisation de la requete:%s", sqlite3_errmsg (bdd) );
            return 1;
        }
    }

    return 0;
}

/**
 * Initialisation de la base de donnees
 * \param bdd[out] La structure qui va contenir la connexiona a la bdd
 * \retval char Reussite ou non de l'initialisation
 */
char init_bdd (sqlite3** bdd)
{
    int result = sqlite3_open ("/var/lib/Caeli/caeli.db", bdd);

    if ( result != SQLITE_OK )
    {
        syslog (LOG_ERR, "Impossible d'ouvrir la base de donnees:%s", sqlite3_errmsg (*bdd) );
        sqlite3_close (*bdd);
        return 1;
    }

    return creation_bdd (*bdd);
}

void nett_bdd (sqlite3* bdd)
{
    sqlite3_close (bdd);
}
