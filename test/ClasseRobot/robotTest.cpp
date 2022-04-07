#include <moteur.h>
#include <robot.h>
volatile uint8_t gInterrupteur;
volatile Unite   unite;
volatile uint8_t gInterruptStop;
enum Etape etat;

volatile float gCompteur;
int main(){

    Robot robotTest;

    // Test impulsions 0.5
    robotTest.getMoteur().initialiser();
    //robotTest.arreter05();

    robotTest.getMoteur().tourner(1);
    _delay_ms(1750);
    robotTest.getMoteur().synchroniserRouesDroit(38,60,0);
    while(!(PINA & 1 <<PA2)){};

    // robotTest.getMoteur().initialiser();
    // robotTest.getMoteur().synchroniserRoues(65,0);
    // while (true){
    // robotTest.suivreParcour();

    //robotTest.getMoteur().evitement();
    // if ((PINA & 1<<PA0) && (PINA & 1<<PA1)){ //verifie les 2 pins les plus a droite
    //     robotTest.getMoteur().tourner(0);               // tourne droite
    //     while(!(PINA & 1<<PA2)){};
    //     robotTest.getMoteur().synchroniserRoues(65,0);
    // }
    // if ((PINA & 1<<PA4) && (PINA & 1<<PA3)){ // verifie les 2 pins les plus a gauche
    //     robotTest.getMoteur().tourner(1);               // tourne gauche
    //     while(!(PINA & 1<<PA2)){};
    //     robotTest.getMoteur().synchroniserRoues(65,0);
    // }
    //}
    return 0;
}
