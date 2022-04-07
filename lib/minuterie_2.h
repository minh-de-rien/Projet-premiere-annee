/* -------------------------------------------------|
| Fichier:     minuterie_2.cpp                      |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme permet de partir la     |
|              minuterie 2, de calculer la distance |
|              entre le point de départ et          |
|              l'obstacle et d'utiliser cette       |
|              distance pour calculer la distance   |
|              que le robot doit parcourir avant de |
|              s'arrêter.                           |
|---------------------------------------------------|
*/

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

extern volatile float gCompteur; 
extern volatile float distance; 

// CONSTANTES
const float DISTANCE_TOTALE  = 182.88;
const float TAILLE_ROBOT     = 18.5; 
const float DEMI_ROBOT       = 17; // qui depasse lors du virage 90
const uint16_t CONVERSION_MS = 1000;

// Mode normal et prescaler de 1024
void     partirTimer2    (uint16_t periodeTi); 
void     partirClock     (uint16_t periodeCl);
void     eteindreClock   ();
float    calculerDistance(float vitesse);
uint16_t calculerDelaiFin(float vitesse, float obstacle1);
