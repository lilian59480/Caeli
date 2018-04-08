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
