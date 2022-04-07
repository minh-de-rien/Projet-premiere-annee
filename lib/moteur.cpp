/* -------------------------------------------------|
| Fichier:     moteur.cpp                           |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme permet d'initialiser    |
|              les moteurs du robot et de contrôler |
|              sa direction et sa vitesse.          |
| Matériel:    Le fil relié à la direction de la    |
|              roue droite est branché sur le pin #6|
|              du port B, celui du enable est sur le|
|              pin #4 du port B. En ce qui concerne |
|              la roue gauche, la direction est     |
|              branchée sur le pin #7 du port B et  |
|              le enable, sur le pin #5.            |
|---------------------------------------------------|
*/

#include "moteur.h"

void Roue::ajusterDirection(uint8_t direction) { 
    if (direction == 0)
        *portDirection_ &=  ~( 0x01 << pinDirection_); // set a 0  

    if (direction >= 1)
        *portDirection_ |= (0x01 << pinDirection_); // set a 1
}

void Roue::changerDirection() {
    *portDirection_ ^= (0x01 << pinDirection_); // set a 0 si 1 et 1 si 0
}

void Moteur::initialiser() {
    DDRB = 0xff; // Port B en mode sortie
    TCNT0 = 0;
    
    // Mode PWM phase correct; 
    // CLEAR OC0A et OC0B sur comparaison montante;
    // SET sur comparaison descendante
    TCCR0A |=  (1 << COM0B1) | (0 << COM0B0) | (1 << COM0A1) 
               | (0 << COM0A0) | (1 << WGM00);

    // Prescaler de 1024
    TCCR0B |=   (1 << CS02) | (1 << CS00);
    // TIMSK0 |= ( 1 << OCIE0B) | (1 << OCIE0A);  
}

void Moteur::ajusterVitesseRoueD(uint8_t vitesse) { // 1-100
    OCR0A = vitesse * TOP_TIMER * POURCENTAGE;
}

void Moteur::ajusterVitesseRoueG(uint8_t vitesse) { // 1-100
    OCR0B = vitesse * TOP_TIMER * POURCENTAGE;
}

void Moteur::synchroniserRoues(uint8_t vitesse, uint8_t direction) {
    roueD_.ajusterDirection(direction);
    roueG_.ajusterDirection(direction);
    OCR0B = OCR0A = vitesse * TOP_TIMER * POURCENTAGE;
}

void Moteur::synchroniserRouesDroit(uint8_t vitesseDroite, uint8_t vitesseGauche,
 uint8_t direction) {
    roueD_.ajusterDirection(direction);
    roueG_.ajusterDirection(direction);
    ajusterVitesseRoueD(vitesseDroite);
    ajusterVitesseRoueG(vitesseGauche);
}

void Moteur::tourner_90(uint8_t direction) {
    this->synchroniserRoues(0, 0);
    _delay_ms(1000);
    if (direction == 0) {
        roueD_.ajusterDirection(1);
        roueG_.ajusterDirection(0);
    }
    if (direction == 1) {
        roueD_.ajusterDirection(0);
        roueG_.ajusterDirection(1);
    }
    OCR0B = OCR0A = VITESSE_VIRAGE * TOP_TIMER * POURCENTAGE;
    _delay_ms(DUREE_VIRAGE);
    this->synchroniserRoues(0, 0);
}

void Moteur::tourner(uint8_t direction) {
    this->synchroniserRoues(0, 0);
    _delay_ms(500);
    if (direction == 0){
        roueD_.ajusterDirection(1);
        roueG_.ajusterDirection(0);
    }
    if (direction == 1){
        roueD_.ajusterDirection(0);
        roueG_.ajusterDirection(1);
    }
    OCR0B = (VITESSE_VIRAGE + 5) * TOP_TIMER * POURCENTAGE;
    OCR0A = VITESSE_VIRAGE * TOP_TIMER * POURCENTAGE;
}