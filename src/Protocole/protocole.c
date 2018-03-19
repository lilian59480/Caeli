#include "protocole.h"

/**
 * Transforme tous les \\r en \\n
 * \param[in,out] str La chaine à modifier
 */
void strcrtonl (char* str)
{
    unsigned int i;

    for (i = 0; i < strlen (str); i += 1)
    {
        if (str[i] == '\r')
        {
            str[i] = '\n';
        }
    }
}

/**
 * Transforme tous les \\n en \\r
 * \param[in,out] str La chaine à modifier
 */
void strnltocr (char* str)
{
    unsigned int i;

    for (i = 0; i < strlen (str); i += 1)
    {
        if (str[i] == '\n')
        {
            str[i] = '\r';
        }
    }
}

