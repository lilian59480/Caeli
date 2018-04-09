#
#    Copyright (c) 2012 Lilian Petitpas & Hugo Dooms
#
#    Permission is hereby granted, free of charge, to any person obtaining
#    a copy of this software and associated documentation files (the "Software"),
#    to deal in the Software without restriction, including without limitation
#    the rights to use, copy, modify, merge, publish, distribute, sublicense,
#    and/or sell copies of the Software, and to permit persons to whom the Software
#    is furnished to do so, subject to the following conditions:
#
#    The above copyright notice and this permission notice shall be included in
#    all copies or substantial portions of the Software.
#
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
#    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
#    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
#    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
#    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

# Version de CMake
cmake_minimum_required(VERSION 2.8)
# Nom du projet
project("Caeli")

set(SQLite3_DIR ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Threads REQUIRED)
find_package(SQLite3 REQUIRED)

# On active les erreurs de compilations
set(warnings "-Wall -Wextra -Werror -pedantic -g2 -O0 -ggdb")
# On affiche ce que fait le makefile
set(CMAKE_VERBOSE_MAKEFILE OFF)
# On met nos flags
set(CMAKE_C_FLAGS "${warnings}")

# On demande d'inclure le dossier
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

include_directories(${SQLITE3_INCLUDE_DIRS})

add_subdirectory(src/Protocole)
add_subdirectory(src/Reseau)
add_subdirectory(src/Utilitaires)
add_subdirectory(src/Materiel)
add_subdirectory(src/Serveur)
add_subdirectory(src/Client)

add_executable(Caeli_Serveur "src/Serveur/serveur.c")
target_link_libraries(Caeli_Serveur Reseau Protocole Utilitaires Materiel ${CMAKE_THREAD_LIBS_INIT})

add_executable(Caeli_Client "src/Client/client.c")
target_link_libraries(Caeli_Client Reseau Protocole Utilitaires Client ${SQLITE3_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Installation
install(TARGETS Caeli_Serveur Caeli_Client
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)
