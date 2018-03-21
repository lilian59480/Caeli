# Version de CMake
cmake_minimum_required(VERSION 2.8)
# Nom du projet
project("MCS Caeli")

find_package(Threads REQUIRED)

# On active les erreurs de compilations
set(warnings "-Wall -Wextra -Werror -pedantic -g2 -O0 -ggdb")
# On affiche ce que fait le makefile
set(CMAKE_VERBOSE_MAKEFILE OFF)
# On met nos flags
set(CMAKE_C_FLAGS "${warnings}")

# On demande d'inclure le dossier
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(src/Protocole)
add_subdirectory(src/Reseau)
add_subdirectory(src/Utilitaires)
add_subdirectory(src/Serveur)
add_subdirectory(src/Client)

add_executable(Caeli_Serveur "src/Serveur/serveur.c")
target_link_libraries(Caeli_Serveur Reseau Protocole Utilitaires ${CMAKE_THREAD_LIBS_INIT})

add_executable(Caeli_Client "src/Client/client.c")
target_link_libraries(Caeli_Client Reseau Protocole Utilitaires ${CMAKE_THREAD_LIBS_INIT})
