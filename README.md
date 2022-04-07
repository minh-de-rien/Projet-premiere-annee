---

# Projet INF1900 - Polytechnique Montréal
Projet initial de système embarqué

# Auteur.es
Nils Coulier  
[Minh Ngoc Do](https://github.com/minh-de-rien)  
[Jolan Le Clainche](https://github.com/JolanLec)  
[Rosie Morissette](https://github.com/mori-rosi)  

---

# Description

Le but du projet est de programmer un robot équipé d'un Atmega 324PA pour qu'il suive un parcours constitué d'une ligne noire et jaune et de deux obstacles.


## Aspects matériels

### Capteurs et actionneurs

* Le robot utilise un suiveur de ligne (Cytron LSS05) pour compléter le parcours et un capteur de distance (Sharp GP2Y0A21YK0F) pour répondre à des évenements prenant place durant le parcours. 
* Un afficheur (LCD Lumex LCM-S01602DTR/M) et une diode électroluminescente (DEL) sont aussi installés sur le robot. 
* Enfin, un haut-parleur permet d'émettre du son en fonction de la distance le séparant d'un obstacle.


### Branchements

| Composants              | Pins                      |
| ----------------------- |:-------------------------:|
| Pins vide               | A8, B3, B8, D1, D2, D7, D8|
| DEL                     | B1-B2                     |
| Haut-parleur            | D5-D6 (OC1A sur pin D6)   | 
| LCD                     | PORTC en entier           |
| Capteur de distance     | A7                        |
| Suiveur de ligne        | A1 à A6                   |
| Bouton-poussoir externe | D4                        |
| Moteurs <br>Enable OC0A (roue droite) <br>Enable OC0B (roue gauche) <br>Direction droite <br>Direction gauche|
B4 à B7 <br>B4 <br>B4 <br>B6 <br>B7|     

*L'interrupteur sur le robot est lié à la pin D3 grâce au cavalier sur IntEn.*


### Ressources internes

* Minuterie 0 : PWM pour le moteur (OCR0A, roue droite et OCR0B, roue gauche)
* Minuterie 1 : PWM pour le son (OCR1A)
* Minuterie 2 : Génère des interruptions 30 fois par seconde pour mesurer la distance à un obstacle (OCR2A) ou la distance parcourue (OCR2B).


## Librairie

Des classes et fonctions se trouvent dans la librairie sous le répertoire « lib ».

### Classes

`Robot`
  La classe Robot permet un contrôle centralisé. Elle comprend un Moteur, une Del, et un Lcd. En plus des méthodes fournies par ces classes, Robot contient les méthodes suivantes : 
  * attendre(), 
  * suivreLigne(), 
  * suivreParcours(), 
  * Arret05() (permet un arret a 0.5 po d'un obstacle),
  * evitement() et 
  * boucle() (permet de suivre une partie du parcours avec 
    des valeurs prédéfinies).

`Moteur`
    La classe Moteur comprend deux Roue et permet une gestion du moteur en fournissant des méthodes pour ajuster la vitesse de chaque roue, pour synchroniser les vitesses des deux roues, et pour tourner. La classe Moteur utilise le timer0 du atmega324PA pour controler le moteur. Il faut donc faire appel à la méthode initialiser() avant toute chose pour pouvoir controler le moteur (intitialiser le timer). On utilise les registres OCR0A et OCR0B pour controler les roues; par conséquent les signaux "Enable" des roues sont branchés sur les pins 4 et 5 du PORTB pour répondre aux signaux OC0A et OC0B.

`Roue`
    La classe Roue permet de représenter les roues du robot. Elle détient comme attributs une référence au PORT sur lequel la roue est branchée, un uint8_t pour indiquer le pin controlant la direction, ainsi qu'un uint8_t indiquant la direction de la roue. Les méthodes de la classe permettent un contrôle de la direction. Dans notre cas, ce sont les pins 6 et 7 du PORTB qui sont liés à la direction des roues.

`Del`
    La classe Del permet de contrôler la DEL présente sur le robot. Elle détient comme attributs une réference au port sur lequel la DEL est branchée, une référence au registre de donnée de direction (DDR), ainsi que des uint8_t indiquant la broche négative et la broche positive sur lesquelles elle est branchée. Ses méthodes permettent d'allumer la del du robot d'une certaine couleur, avec un délai ou non, et de l'éteindre. Dans notre assemblage, la DEL est branchée sur les pin 1 (négatif) et 2 (positif) du PORTB.

### Structure

`Lcd`
    La structure Lcd permet l'affichage de la distance calculée entre le point B et le premier obstacle (le mur ainsi qu'entre le point F et le deuxième obstacle (le poteau). Elle comprend deux méthodes dont afficherLcd et eteindreLcd qui prend en paramètre l'objet de la classe LCM qui elle permet l'initialisation du lcd selon le port sur lequel il est branché. La méthode afficherLcd prend également en paramètre la distance l'unité à afficher.

        
## Autres fichiers

* D'autres fonctions permettent d'utiliser le capteur de distance et les boutons-poussoir, de gérer le son ou de contrôler les ressources internes du processeur, comme les interruptions et les minuteries. Celles-ci sont placées dans des fichiers distincts qui sont dans la librairie.

* Des programmes déjà fournis, comme la classe LCM ou la conversion analogique-numérique (can.h/can.cpp) se retrouvent également dans cette librairie.


## Main

Le code principal est réparti en 4 sections principales.

* Une machine à états implémentée à l'aide d'un type énuméré (défini dans la classe robot) et d'une structure switch/case. Elle appelle des fonctions déjà définies dans la librairie. Cela permet de répartir l'épreuve en sections et de réutiliser du code. Une section d'initialisation précède le switch/case et permet de déclarer les variables locales et les objets, et d'initialiser les interruptions et les minuteries. 

* Les variables et constantes. Elle contient des constantes, comme la vitesse ou des constantes pour un calcul de distance, et des variables globales qui sont modifiées dans les routines d'interruptions. 
 
* Les 4 routines d'interruptions. L'interrupteur, le bouton-poussoir externe, et deux comparaisons pour la minuterie 2. 

* Des fonctions globales simples (comme les anti-rebonds pour les boutons).

---
Équipe : 18-35  
8 décembre 2021

