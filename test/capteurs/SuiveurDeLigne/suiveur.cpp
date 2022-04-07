#define F_CPU 8000000UL

#include <moteur.h>
#include <util/delay.h>

#include <avr/io.h> 
#include <stdio.h>

// void Moteur::suivreLigne(){
//     if (PINA & 1<<PA1 || PINA & 1<<PA0){
//         this->moteur.ajusterVitesseRoueD(40);
//         _delay_ms(5);
//         this->moteur.ajusterVitesseRoueD(65);
//     }
//     if (PINA & 1<<PA3 || PINA & 1<<PA4){
//         this->moteur.ajusterVitesseRoueD(80);
//         _delay_ms(5);
//         this->moteur.ajusterVitesseRoueD(65);
//     }
// }

// void Moteur::suivreParcour() {
//     if (PINA & 1<<PA1 || PINA & 1<<PA0){      /// remplacer par un appel de la fonction suivreLigne ?
//         this->moteur.ajusterVitesseRoueD(40);
//         _delay_ms(5);
//         this->moteur.ajusterVitesseRoueD(65);
//     }
//     if (PINA & 1<<PA3 || PINA & 1<<PA4){
//         this->moteur.ajusterVitesseRoueD(80);
//         _delay_ms(5);
//         this->moteur.ajusterVitesseRoueD(65);
//     }                                         ///

//     if ((PINA & 1<<PA0) && (PINA & 1<<PA1)){ //verifie les 2 pins les plus a droite
//         moteurTest.tourner(0);               // tourne droite
//         while(!(PINA & 1<<PA2)){};
//         moteurTest.synchroniserRoues(65, 0);
//     }
//     if ((PINA & 1<<PA4) && (PINA & 1<<PA3)){ // verifie les 2 pins les plus a gauche
//         moteurTest.tourner(1);               // tourne gauche
//         while(!(PINA & 1<<PA2)){};
//         moteurTest.synchroniserRoues(65, 0);
//     }
// }
// void debuterVirage(){
//     if ((PINA & 1<<PA0) && (PINA & 1<<PA1)){ //verifie les 2 pins les plus a droite
//         moteurTest.tourner(0);               // tourne droite
//     }
//     if ((PINA & 1<<PA4) && (PINA & 1<<PA3)){ // verifie les 2 pins les plus a gauche
//         moteurTest.tourner(1);               // tourne gauche
//     }
//     _delay_ms(5);
// }

int main() {
    DDRA |= 0x00;
    DDRB |= 0b11;
    Moteur moteurTest(PORTB, 5, PORTB, 6);
    moteurTest.initialiser();

    // a Tester : inclure la synchro dans le while 
    
    while(true){
        moteurTest.synchroniserRoues(65, 0);
        if (PINA & 1<<PA1 || PINA & 1<<PA0){
            moteurTest.ajusterVitesseRoueD(40);
            _delay_ms(5);
        }
        if (PINA & 1<<PA3 || PINA & 1<<PA4){
             moteurTest.ajusterVitesseRoueD(80);
             _delay_ms(5);
        }
        if ((PINA & 1<<PA0) && (PINA & 1<<PA1)){ //verifie les 2 pins les plus a droite
            moteurTest.tourner(0);               // tourne droite
            while(!(PINA & 1<<PA2)){};
        }
        if ((PINA & 1<<PA4) && (PINA & 1<<PA3)){ // verifie les 2 pins les plus a gauche
            moteurTest.tourner(1);               // tourne gauche
            while(!(PINA & 1<<PA2)){};
        }
    }
    return 0;
}
