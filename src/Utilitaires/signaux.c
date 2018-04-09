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
 * \file signaux.c
 */
#include "signaux.h"


/**
 *
 * \param signal
 * \param
 * \param flags
 */
struct sigaction handle_signal (int signal, void (*handler) (int), int flags)
{
    struct sigaction act;
    struct sigaction old;
    act.sa_handler = handler;
    act.sa_flags = flags;
    CHECK (sigemptyset (&act.sa_mask), "ERREUR SIGEMPTYSET");
    CHECK (sigaction (signal, &act, &old), "ERREUR SIGACTION");
    return old;
}

/**
 *
 * \param signal
 * \param flags
 */
struct sigaction ignore_signal (int signal, int flags)
{
    return handle_signal (signal, SIG_IGN, flags);
}
