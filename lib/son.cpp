/* -------------------------------------------------|
| Fichier:     son.cpp                              |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme permet d'initialiser    |
|              les moteurs du robot et de contrôler |
|              sa direction et sa vitesse.          |
| Matériel:    Le fil noir du piézo est branché sur |
|              le pin #5 du port D et le rouge, sur |
|              le pin #6 du port D (là où se situe  |
|              OCRIA).                              |
|---------------------------------------------------|
*/

#include "son.h"

void jouerSon (uint8_t note) {
    uint16_t setOcr1a = (F_CPU * MULTIPLICATEUR / (2 * PRESCALER_SON * NOTES[note - 45]) 
                        / MULTIPLICATEUR) - 1; 

    Minuterie minuterie(Mode::MODE_CTC, Prescaler::PRESCALER_256, setOcr1a, 0);
    minuterie.partirMinuterie();
}

void jouerSonDistance (float distance) { // en cm

    // Initialiser D5 en mode sortie et D4 à 0
    DDRD |= (1 << PD5) | (1 << PD4); 
    PORTD &= ~(1 << PD4);

    if (distance > 60.96)
        eteindreSon();
    else {
        TCCR1B |= (1 << CS12);
        float freq = 0;

        if (distance == 60.96)
            freq = FREQ_24PO;
        if (distance <= 30.48)
            freq = FREQ_12PO;
        if (distance > 30.48 && distance < 60.96)
            freq = distance*(TAUX_VARIATION) + ORDONNEE_ORIGINE;

        float    denominateur = (freq / AJUSTEMENT) * 2 * PRESCALER_SON;
        uint16_t setOcr1a     = (NUMERATEUR_CALC_OCR1A / denominateur) - 1;

        OCR1A = setOcr1a;
        
    }
}

void eteindreSon() {
    TCCR1B &= ~(1 << CS12);
}