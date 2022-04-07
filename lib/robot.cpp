/* -------------------------------------------------|
| Fichier:     robot.cpp                            |
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

#include "moteur.h"
#include "robot.h"


Robot:: ~Robot() {
    //eteindreSon();
    gInterruptStop = 1;
    TCCR1B &= ~(1 << CS12); //arrete le son
    moteur_.synchroniserRoues(0, 0);
    del_.eteindreDel();
    LCM lcm(&DDRC, &PORTC);
    lcd_.eteindreLcd(lcm);
}

void Robot::attendre(Etape etat, float distance) { 
    
    // Eteindre moteurs   
    moteur_.synchroniserRoues(0, 0);

    // Del en rouge
    del_.allumerDel(COULEUR_ROUGE);  

    // arrete le son
    gInterruptStop = 1;
    TCCR1B &= ~(1 << CS12); 
       
    if (etat == ATTENTE1 || etat == ATTENTE2) {
        LCM lcm(&DDRC, &PORTC);
        do {       
                 
            lcd_.afficherLcd(lcm, distance, unite); 
        } while (gInterrupteur != 1);                 

        // eteindreLcd();                
        lcd_.eteindreLcd(lcm); 
    }

    else {        
        while (gInterrupteur != 1) {}            
    }

    gInterrupteur = 0;

    del_.allumerDel(COULEUR_VERT);
    _delay_ms(FAIRE_RIEN);
    
    // reactive le son
    TCCR1B |= (1 << CS12); 
    gInterruptStop = 0;
}

void Robot:: suivreLigne() {
    if (PINA & 1 << PA1 || PINA & 1 << PA0) { 
        moteur_.ajusterVitesseRoueD(PUISSANCE_B);
        _delay_ms(3);
        moteur_.ajusterVitesseRoueD(PUISSANCE_M);
    }
    if (PINA & 1 << PA3 || PINA & 1 << PA4) { 
        moteur_.ajusterVitesseRoueD(PUISSANCE_E);
        _delay_ms(3);
        moteur_.ajusterVitesseRoueD(PUISSANCE_M);
    }
}

void Robot:: suivreParcour(uint8_t& nVirages) {
    if (PINA & 1 << PA1 || PINA & 1 << PA0) {
        moteur_.ajusterVitesseRoueD(PUISSANCE_B);
        _delay_ms(3);
        moteur_.ajusterVitesseRoueD(PUISSANCE_M);
    }
    if (PINA & 1 << PA3 || PINA & 1 << PA4) {
        moteur_.ajusterVitesseRoueD(PUISSANCE_E);
        _delay_ms(3);
        moteur_.ajusterVitesseRoueD(PUISSANCE_M);
    }
    if ((PINA & 1 << PA0) && (PINA & 1 << PA1)) { // verifie les 2 pins les plus a droite
        nVirages++;
        _delay_ms(500);
        moteur_.tourner(0);               // tourne droite
        while(!(PINA & 1 << PA2)) {};
        moteur_.synchroniserRouesDroit(40, 50, 0);
    }
    if ((PINA & 1 << PA4) && (PINA & 1 << PA3)) { // verifie les 2 pins les plus a gauche
        _delay_ms(500);
        moteur_.tourner(1);               // tourne gauche
        while(!(PINA & 1 << PA2)) {};
        moteur_.synchroniserRouesDroit(40, 50, 0);
    }
}

void Robot:: arreter05() {    
    for (uint8_t i = 0; i < 3; i++) {          
        moteur_.synchroniserRouesDroit(58, 66, 0); 
        _delay_ms(200); 
        moteur_.synchroniserRoues(0, 0);
        _delay_ms(1500); 
    }
}
void Robot:: evitement() {
    moteur_.tourner(1);
    _delay_ms(1300); //1750, 1300 ok peut-etre 1350
    moteur_.synchroniserRouesDroit(40, 60, 0);
    while(!(PINA & 1 << PA2)) {};
    moteur_.synchroniserRoues(0, 0);
}

void Robot:: boucle() {                                           //nécessaire pour que isr se fassent

    moteur_.tourner(0);                   //180 degres, début sans verifier condition pour qu'il ne reste pas bloqué sur la ligne      
    _delay_ms(1000);
    while(!(PINA & 1 << PA2)) {};

    moteur_.synchroniserRoues(0,0);       //pause
    _delay_ms(1000);
    moteur_.synchroniserRouesDroit(40, 50, 0);

    while(!((PINA & 1 << PA3) && (PINA & 1 << PA4))) {     //ignore le suiveur de ligne quand croise première intersection
        suivreLigne();
    }
    _delay_ms(300);
    while(!((PINA & 1 << PA3) && (PINA & 1 << PA4))) {     //deuxième intersection = rotation
        suivreLigne();
    }

    _delay_ms(400);                                     //continue d'avancer un peu
    moteur_.tourner(1);                   //tourne à gauche
    _delay_ms(1000);                                    //début sans verifier condition pour qu'il ne reste pas bloqué sur la ligne
    while(!(PINA & 1 << PA2)) {};

    moteur_.synchroniserRoues(0, 0);       //pause
    _delay_ms(1000); 
    moteur_.synchroniserRouesDroit(40, 50, 0);

    partirClock(260);                                   //hardcode petit segment en avançant un temps determiné par clock
    while(gCompteur != 115) {  // 105                    //83 = compteur de base pour avoir le devant sur ligne jaune
        suivreLigne();
    }

    moteur_.synchroniserRoues(0, 0);       //pause
    _delay_ms(1000);

    moteur_.tourner(1);                   //virage hardcodé sur ligne jaune
    _delay_ms(3000); // 3700
    
    moteur_.synchroniserRoues(0, 0);       //pause
    _delay_ms(1000);
    moteur_.synchroniserRouesDroit(40, 50, 0);

    _delay_ms(2000);
    if (!((PINA & 1 << PA0) || (PINA & 1 << PA1) || (PINA & 1 << PA2) || (PINA & 1 << PA3) || (PINA & 1 << PA4))) {
        moteur_.tourner(1);
        while(!(PINA & 1 << PA2)) {};
        moteur_.synchroniserRoues(0, 0);
        _delay_ms(500);
        moteur_.synchroniserRouesDroit(40, 50, 0);
}

    while(!((PINA & 1 << PA2) && (PINA & 1 << PA3) && (PINA & 1 << PA4))) {      //avance puis suis ligne jusqu'au point B, condition = trois pins de gauche
        suivreLigne();
    }

    _delay_ms(300);                                                         //avance un peu puis complète boucle avec suivre ligne et rotations
    moteur_.tourner(1);
    while(!(PINA & 1 << PA2)) {};
    moteur_.synchroniserRouesDroit(40, 50, 0);
    while(!((PINA & 1 << PA3) && (PINA & 1 << PA4))) {
        suivreLigne();
    }
    _delay_ms(300);
    moteur_.tourner(1);
    _delay_ms(1000);                                                        //début sans verifier condition pour qu'il ne reste pas bloqué sur la ligne
    while(!(PINA & 1 << PA2)) {};
    moteur_.synchroniserRouesDroit(40, 50, 0);
    while(!((PINA & 1 << PA3) && (PINA & 1 << PA4))) {
        suivreLigne();
    }

    _delay_ms(300);
    moteur_.tourner(1);
    while(!(PINA & 1 << PA2)) {};
    moteur_.synchroniserRoues(0, 0);
    _delay_ms(1000);