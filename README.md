# Caeli : Prototype de station d'analyse de l'air

[Site](https://lilian59480.github.io/Caeli/)

Projet Objets Connectés LE3 pour Centrale Lille Formation IG2I

**Bon on pourra discuter des critères de qualité**

Caeli est un projet réalisé dans le cadre des études en troisième année de la formation IG2I de Centrale Lille

Notre objectif était de réaliser un prototype réalisable s'inspirant d'une idée imaginée pour le concours IOT Student Challenge 2018

## Présentation du prototype

Caeli est un station d’air connecté pouvant relever la température et l’humidité dans une pièce. Ces données sont enregistrées sur un serveur puis traitées et analysées. Ces données servent ensuite à activer les avertisseurs visuels en cas de dépassement des seuils programmés. 
De plus on dispose d’une interface web simple présentant les données sous formes de différents graphes pour une lecture plus clairs et concises.

## Commencer

### Prérequis

Le projet nécessite du materiel listé ici :
- Un Raspberry-Pi 3
- Un kit GrovePi+ dans lequel on utilise :
    - Un LCD 16x2 avec rétroéclairage RGB
    - Un capteur de température et d'humidité DHT (Version Bleu)
    - 2 Leds, une d'activité et une d'alerte de depassement de seuil

Les exemples ici sont pour les systèmes basés sur GNU/Raspbian

- Build-Essential `# apt-get install build-essential`
- GCC `# apt-get install gcc`
- CMake `# apt-get install cmake`
- Git `# apt-get install git`
- Firmware et librairies GrovePi `# git clone https://github.com/DexterInd/GrovePi.git && cd GrovePi/Script && sh install.sh`

### Branchement et cablages :

Connecter le shield Grove PI+ sur les ports GPIO de votre Raspberry Pi.
Ensuite connecter les différents équipements au ports qui leur ont été attribué dans le code.

L’ordre des connections est le suivant :

- LED rouge sur D3 (Digital 3)
- LED bleu sur D4 (Digital 4)
- Capteur sur D7 (Digital 7)
- LCD sur I2C-1


### Compiler et Installer

Nous avons utilisé CMake afin de simplifier la compilation

- Installez les prérequis
- Téléchargez le zip ou clonez ce repo
- Déplacez vous dans le répertoire build
- Executez `$ cmake ..` puis `$ make`

## Lancer

Le projet compilé est disponible dans le dossier build.

Au moins un client doit fonctionner, de préférence une version interne, et vous
pouvez éxécuter une instance sur n'importe quel autre périphérique

Avec les fichiers `.service` et `.timer` pour Systemd, la station fonctionnera au demarrage de la machine, 
et effectuera des requetes réguliérement afin d'interroger la station
