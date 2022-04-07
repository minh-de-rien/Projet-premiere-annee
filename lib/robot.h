/* -------------------------------------------------|
| Fichier:     robot.h                              |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme regroupe les diverses   |
|              classes, qui chacune contrôle une    |
|              partie du robot, en une seule classe.|
|---------------------------------------------------|
*/

#ifndef ROBOT_H
#define ROBOT_H

#include "moteur.h"
#include "controleDelClass.h"
#include "son.h"
#include "lcd.h"
#include "minuterie_2.h"

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

// CONSTANTES
const uint16_t          FAIRE_RIEN = 2000; // delai fin attente
extern volatile uint8_t gInterrupteur;
extern volatile Unite   unite;
extern volatile uint8_t gInterruptStop;

const uint8_t PUISSANCE_M = 40; 
const uint8_t PUISSANCE_B = 30; // 30
const uint8_t PUISSANCE_E = 50; // 70 

enum Etape {
    DEBUT,
    OBSTACLE1,
    ATTENTE1,    
    BOUCLE,    
    OBSTACLE2,
    ATTENTE2,    
    OBSTACLE3,
    ATTENTE3,
    FIN
};

extern enum Etape etat; 

class Robot {
    public:
        Robot():
            moteur_(Moteur(PORTB, 5, PORTB, 6)),
            del_(Del(&DDRB, &PORTB, 1, 0)),
            lcd_()
        {}
        ~Robot();

        void attendre(Etape etat, float distance);

        Moteur getMoteur() const { return moteur_; }
        Del getDel() const { return del_; }
        
        void suivreLigne();
        void suivreParcour(uint8_t& nVirages);
        void arreter05();
        void evitement();
        void boucle();

    private:
        Moteur moteur_;
        Del del_;
        Lcd lcd_;
};

#endif