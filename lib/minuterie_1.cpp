/* -------------------------------------------------|
| Fichier:     minuterie_1.cpp                      |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme permet de partir la     |
|              minuterie 1 selon un mode et un      |
|              prescaler donné.                     |
|---------------------------------------------------|
*/

#include "minuterie_1.h"

void Minuterie::fixerModeMinuterie() {
	
    switch (modeMinuterie_) {
        case Mode::MODE_CTC :
            TCCR1A |= (0 << WGM11) | (0 << WGM10) | (1 << COM1A0); 
            TCCR1B |= (0 << WGM13) | (1 << WGM12);
            break;
		case Mode::MODE_PHASE_CORRECTE :
			TCCR1A |= (0 << WGM11) | (1 << WGM10); 
            TCCR1B |= (0 << WGM13) | (0 << WGM12);
			break;
		case Mode::MODE_PWM_RAPIDE : 
			TCCR1A |= (0 << WGM11) | (1 << WGM10); 
            TCCR1B |= (0 << WGM13) | (1 << WGM12);
			break;
		case Mode::MODE_NORMAL :
        default:
		    TCCR1A |= (0 << WGM11) | (0 << WGM10); 
            TCCR1B |= (0 << WGM13) | (0 << WGM12);
            break;
    }
}

void Minuterie::fixerPrescaler() {
    
    switch (modePrescaler_) {
        case Prescaler::PRESCALER_8 :
            TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
            break;
        case Prescaler::PRESCALER_64 :
            TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
            break;
        case Prescaler::PRESCALER_256 :
            TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
            break;
        case Prescaler::PRESCALER_1024 :
            TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
            break;
        case Prescaler::PRESCALER_1 :
        default:
            TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
            break;
    }

    TCCR1C = 0;
}

void Minuterie::partirMinuterie() {
    
    // Valeur initiale du registre timer1 :
    // la minuterie commence a 0
    TCNT1 = 0; 

    // Valeur qui est continuellement comparée à la valeur du compteur 
    // elle permet l'interruption après la durée spécifiée
    OCR1A = dureeA_; 
    OCR1B = dureeB_;

    // Le timer peut avoir des modes (formes d'onde) différents
    // le TCCR (Timer/Counter Control) permet de fixer ce mode
	fixerModeMinuterie();
    
	// Le TCCR permet également de fixer le prescaler de la minuterie
	// ce dernier permet à la minuterie de compter plus lentement
    fixerPrescaler();

    // Autre fonction pour enable l'interruption
    // TIMSK1 |= 1 << OCIE1A; 
    // if (dureeB_ != 0)
    //     TIMSK1 |= 1 << OCIE1B;
}
