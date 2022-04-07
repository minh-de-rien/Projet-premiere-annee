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

#include "minuterie_2.h"

// Mode normal et prescaler de 1024
void partirTimer2(uint16_t periodeTi) {
    TCNT2 = 0;
    OCR2A = periodeTi;

    // OC2A et OC2B on compare match
    // TCCR2A = (1<<COM2A0) | (1<<COM2B0); 

    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
    TIMSK2 |= (1 << OCIE2A); // ( 1 << OCIE2B)

}

void partirClock(uint16_t periodeCl) {
    gCompteur = 0;
    TIMSK2   |= ( 1 << OCIE2B);
    OCR2B     = periodeCl;
}

void eteindreClock() {
    TIMSK2 = (0 << OCIE2B) | (1 << OCIE2A);
}

float calculerDistance(float vitesse) {
    float  distanceDepartRobot    = vitesse * (gCompteur / 30);
    float  distanceDepartObstacle = distanceDepartRobot + distance + 5;
    return distanceDepartObstacle;
}

uint16_t calculerDelaiFin(float vitesse, float obstacle1) {
    float    distanceFin = DISTANCE_TOTALE - DEMI_ROBOT - obstacle1;
    uint16_t delai       = distanceFin / vitesse;     
    return   delai; // en secondes
}
