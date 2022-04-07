/* -------------------------------------------------|
| Fichier:     main.cpp			                    |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme permet au robot de      |
|              suivre un parcours prédéterminé      |
|              composé d’un tracé de ruban adhésif  |
|              noir (et jaune) ainsi que de deux    |
|              différents obstacles. Le robot est   |
|              muni de capteur de distance, de      |
|              suiveur de ligne et d'afficheur LCD  |
|              qui l'aident à la complétion du      |
|              parcours.                            |
|---------------------------------------------------|
*/

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <stdio.h>
#include "robot.h"
#include "initialisationBouton.h" 
#include "boutonBlanc.h"
#include "capteurDistance.h"
#include "uart.h"

// CONSTANTES
const uint16_t PERIODE            = 260;
const float    VITESSE            = 10; // cm/s
const uint8_t  ANTI_REBOND        = 10; // millisecondes
const uint8_t  D2                 = 0x04;
const uint8_t  D3                 = 0x08;
const uint8_t  B1                 = 0x01;
const float   C1_MUR        = 16.7647563;
const float   C1_POTEAU     = 10.5647563;
const float   C2_MUR        = -1.00503107;
const float   C2_POTEAU     = -1.0000503107;

// VARIABLE VOLATILE
volatile uint8_t gInterrupteur  = 0; // bouton sur la carte 
volatile uint8_t gInterruptStop = 0;
volatile float   distance       = 40; 
volatile float   gCompteur      = 0;
volatile Unite   unite          = UNITE_POUCE;

Etape etat = DEBUT;

// DECLARATION DE FONCTIONS
void obstacle1(Robot& robot, float& distance);
void obstacle2(Robot& robot, float& distance);

bool antiRebondBoutonBlanc() {
    if ((PIND & D3) ^ D3) {
        _delay_ms(ANTI_REBOND);
        return ((PIND & D3) ^ D3);
    } 
    return false;
}

bool antiRebondInterrupt() {
    if (PIND & D2) {
        _delay_ms(ANTI_REBOND);
        return PIND & D2;
    }
    return false;
}

// ROUTINES D'INTERRUPTIONS
ISR (INT0_vect) {
    if (antiRebondInterrupt())
        gInterrupteur = 1;      
}

ISR (INT1_vect) {
    if (antiRebondBoutonBlanc()) {
        // Si le robot est en attente et la DEL est rouge
        if ((etat == ATTENTE1 || etat == ATTENTE2) && (PINB & B1)) {
            if (unite == UNITE_POUCE) 
                unite = UNITE_CM;
            else 
                unite = UNITE_POUCE;
        }
    }
}

ISR (TIMER2_COMPA_vect) { 
    if (gInterruptStop == 0) {
        if (etat == OBSTACLE2)
            mesurerDistance(C1_MUR, C2_MUR);
        else
            mesurerDistance(C1_MUR, C2_MUR);
        jouerSonDistance(distance);
    }
}

ISR (TIMER2_COMPB_vect) {
    gCompteur += 1;
}

int main() {

    // Initialisation 
    float distanceCalculee = 0;
    float delaiFin = 2.35;
    uint8_t compteurVirages = 0;
    initialisationBoutonBlanc(MODE_FRONT_DESCENDANT);
    initialisationBouton(MODE_FRONT_MONTANT);

    Robot robot;
    robot.getMoteur().initialiser();

    Minuterie minuterie(Mode::MODE_CTC, Prescaler::PRESCALER_256, 0, 0);
    minuterie.partirMinuterie();

    // test pour obstacle3 pour mesurer la distance
    partirTimer2(PERIODE); 
            
    //**MACHINE A ETATS  
    // Pour tester:
    //robot.getDel().allumerDel(COULEUR_VERT);
    //_delay_ms(1000);
        //         while (true) {
    //             lcd.afficherLcd(lcm, distance, UNITE_CM);
    //         }

    switch (etat) {
        case DEBUT :
            robot.attendre(etat, distance);            
            partirTimer2(PERIODE); // pour les interruptions 30 fois/sec
            etat = OBSTACLE1;           
                    
        case OBSTACLE1 : 
            obstacle1(robot, distanceCalculee);  
            delaiFin = calculerDelaiFin(VITESSE, distanceCalculee);
            etat = ATTENTE1;       
        
        case ATTENTE1 :
            robot.attendre(etat, distanceCalculee); 
            etat = BOUCLE;
        
        case BOUCLE :
           robot.boucle();
           distance = 40;
           etat = OBSTACLE2;

        case OBSTACLE2 :            
            obstacle2(robot, distanceCalculee);    
            //partirTimer2(PERIODE);                         
            etat = ATTENTE2;
            
        case ATTENTE2 :
            robot.attendre(etat, distanceCalculee); 
            etat = OBSTACLE3;
        
        case OBSTACLE3 : 
            robot.evitement();  
            //partirTimer2(PERIODE); //a activer si test      
            robot.getMoteur().synchroniserRouesDroit(40, 50 ,0);
            while (distance >= 8) { 
                robot.suivreParcour(compteurVirages); 
            }            
            robot.getMoteur().synchroniserRoues(0, 0); // arreter a 4"
            _delay_ms(1500);
            robot.arreter05();         
            etat = ATTENTE3;
           
        case ATTENTE3 :
            robot.attendre(etat, distanceCalculee); 
            etat = FIN;
           
        case FIN :                   
            // tourne 180 a droite
            robot.getMoteur().tourner(0);
            _delay_ms(1000);
            while(!(PINA & 1 << PA2)) {};          

            robot.getMoteur().synchroniserRoues(0, 0);
            _delay_ms(1000);
            robot.getMoteur().synchroniserRouesDroit(40, 50, 0);
            compteurVirages = 0;

            // avance pour 2 virages
            while (compteurVirages < 2) { 
                robot.suivreParcour(compteurVirages);
            }             

            // avance finale
            //robot.getDel().allumerDel(COULEUR_ROUGE);
            robot.getMoteur().synchroniserRouesDroit(40, 50, 0);
            partirClock(PERIODE);
            //delaiFin = 2.62; //test
            while (gCompteur < (delaiFin * 30 + 15)) {
                robot.suivreLigne();
            }
            robot.getMoteur().synchroniserRoues(0, 0);
            
            // Tout arreter (moteur, son, DEL, LCD)
            robot.~Robot();              
    }   
    return 0;
}


void obstacle1(Robot& robot, float& distanceObstacle1) {
    robot.getMoteur().synchroniserRouesDroit(40, 50, 0);
    while(!((PINA & 1 << PA0) && (PINA & 1 << PA1))) {     
        robot.suivreLigne();
    }
    char distanceAffichee[8];
    partirClock(PERIODE);
    while (distance >= 35) { 
        robot.suivreLigne(); 
        
        sprintf(distanceAffichee, "%.2fpo", (double) distance);

        uart::print(distanceAffichee);
    }    
    robot.getMoteur().synchroniserRoues(0, 0); //test      
    eteindreClock();
    distanceObstacle1 = calculerDistance(VITESSE);
}

void obstacle2(Robot& robot, float& distanceObstacle2) {
    robot.getMoteur().synchroniserRouesDroit(40, 50, 0);
    partirClock(PERIODE);
    while (distance >= 35) { 
        robot.suivreLigne(); 
    }          
    eteindreClock();
    distanceObstacle2 = calculerDistance(VITESSE);
}
