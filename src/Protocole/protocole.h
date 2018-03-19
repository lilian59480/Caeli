/**
 * \file protocole.h
 */
#ifndef H_PROTOCOLE_PROTOCOLE
#define H_PROTOCOLE_PROTOCOLE

// Includes systèmes
#include <string.h>

// Includes locaux

/** Nombre de paramètres autorisés dans une requete ou une réponse */
#define NBR_PARAM_MAX 20

/** Taille maximum des paramètres */
#define TAILLE_PARAM_MAX 250

void strcrtonl (char* str);
void strnltocr (char* str);

#endif
