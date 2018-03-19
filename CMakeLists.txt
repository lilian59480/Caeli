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

