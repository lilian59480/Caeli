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

