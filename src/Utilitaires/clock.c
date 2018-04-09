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
 * \file clock.c
 */
#include "clock.h"


/**
 * Fonction récupérant la date
 */
unsigned long get_clock_time ()
{
    // On teste si une horloge insensible est disponible
#ifdef _SC_MONOTONIC_CLOCK
    struct timespec ts;

    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0)
    {
        return (ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
    }
    else
    {
        return 0;
    }

#else
    // Si elle est pas disponible, on passe par la date, en esperant que le système a pas midifié l'heure
    struct timeval tv;

    if (gettimeofday (&tv, NULL) == 0)
    {
        return (tv.tv_sec * 1000000 + tv.tv_usec);
    }
    else
    {
        return 0;
    }

#endif
}
