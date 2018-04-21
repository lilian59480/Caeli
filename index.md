---
layout: default
---

# Caeli : Prototype de station d'analyse de l'air

Projet Objets Connectés LE3 pour Centrale Lille Formation IG2I

**Bon on pourra discuter des critères de qualité**

Caeli est un projet réalisé dans le cadre des études en troisième année de la formation IG2I de Centrale Lille

Notre objectif était de réaliser un prototype réalisable s'inspirant d'une idée imaginée pour le concours IOT Student Challenge 2018

## Commencer

### Prérequis

Le projet nécessite du materiel listé ici :
- Un Raspberry-Pi 3
- Un kit GrovePi+ dans lequel on utilise :
    - Un LCD 16x2 avec rétroéclairage RGB
    - Un capteur de température et d'humidité DHT (Version Bleu)

Les exemples ici sont pour les systèmes basés sur GNU/Raspbian

- Build-Essential `# apt-get install build-essential`
- GCC `# apt-get install gcc`
- CMake `# apt-get install cmake`
- Git `# apt-get install git`
- Firmware et librairies GrovePi `# git clone https://github.com/DexterInd/GrovePi.git && cd GrovePi/Script && sh install.sh`

### Compiler et Installer

Nous avons utilisé CMake afin de simplifier la compilation

- Installez les prérequis
- Téléchargez le zip ou clonez ce repo
- Déplacez vous dans le répertoire build
- Executez `$ cmake ..` puis `$ make`

## Lancer

Le projet compilé est disponible dans le dossier build.

Lancer le avec `$ ./Caeli`

