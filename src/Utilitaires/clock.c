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
