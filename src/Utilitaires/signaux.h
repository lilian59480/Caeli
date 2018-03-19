/**
 * \file signaux.h
 */
#ifndef H_UTILITAIRES_SIGNAUX
#define H_UTILITAIRES_SIGNAUX

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

// Includes locaux
#include "../Utilitaires/utils.h"

struct sigaction handle_signal (int signal, void (*handler) (int), int flags);

struct sigaction ignore_signal (int signal, int flags);


#endif
