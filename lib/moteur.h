/* -------------------------------------------------|
| Fichier:     moteur.h                             |
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

#ifndef MOTEUR_H
#define MOTEUR_H

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

const uint8_t  TOP_TIMER      = 255;
const float    POURCENTAGE    = 0.01;
const uint8_t  VITESSE_VIRAGE = 30;
const uint16_t DUREE_VIRAGE   = 1250;

class Roue {
    public:
        Roue() { portDirection_ = &PORTB; } 
        Roue(volatile uint8_t& port, uint8_t pin){
            portDirection_ = &port;
            pinDirection_  = pin;
        };
        void ajusterDirection(uint8_t direction_); // 0 = avancer 1+ = reculer 
        void changerDirection();
        volatile uint8_t* getPortDirection() const { return portDirection_; }
        uint8_t getPinDirection() const { return pinDirection_; }
        uint8_t getDirection() const { return direction_; }

    private:
        volatile uint8_t* portDirection_;
        uint8_t pinDirection_ = 0;
        uint8_t direction_    = 0;
};

class Moteur {
    public:
        Moteur(volatile uint8_t& portA, uint8_t pinA, volatile uint8_t& portB,
         uint8_t pinB){
            roueD_ = Roue(portA, pinA);
            roueG_ = Roue(portB, pinB);
        }
        void initialiser();
        void ajusterVitesseRoueD(uint8_t vitesse); // [0-100] 0 = arret 100 = puissance max
        void ajusterVitesseRoueG(uint8_t vitesse);
        void synchroniserRoues(uint8_t vitesse, uint8_t direction_);
        void synchroniserRouesDroit(uint8_t vitesseDroite, uint8_t vitesseGauche,
         uint8_t direction);
        void tourner_90(uint8_t direction_);
        void tourner(uint8_t direction_);
        Roue getRoueD() const { return roueD_; }
        Roue getRoueG() const { return roueG_; }

    private:
        Roue roueD_;
        Roue roueG_;  
}; 

#endif