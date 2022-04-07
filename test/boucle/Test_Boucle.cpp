#include <robot.h>
#include <minuterie_2.h>
volatile uint8_t gInterrupteur;
volatile Unite unite;
volatile uint8_t gInterruptStop;
volatile float gCompteur;


ISR ( TIMER2_COMPA_vect ) {}

ISR ( TIMER2_COMPB_vect ) {

    gCompteur += 1;
}

int main() {

    partirTimer2(260);                                  //partir timer 2 pour utilisation de la clock plus tard
    
    Robot robotTest;
    robotTest.getMoteur().initialiser();

    sei();                                              //nécessaire pour que isr se fassent

    robotTest.getMoteur().tourner(0);                   //180 degres, début sans verifier condition pour qu'il ne reste pas bloqué sur la ligne      
    _delay_ms(1000);
    while(!(PINA & 1 << PA2)){};

    robotTest.getMoteur().synchroniserRoues(0,0);       //pause
    _delay_ms(1000);

    robotTest.getMoteur().synchroniserRoues(PUISSANCE_M,0);

    while(!((PINA & 1<< PA3) && (PINA & 1<< PA4))){     //ignore le suiveur de ligne quand croise première intersection
        robotTest.suivreLigne();
    }
    _delay_ms(300);

//    partirClock(260);
//    while(gCompteur != 20){
//        robotTest.suivreLigne();
//    }
   // robotTest.getMoteur().synchroniserRoues(PUISSANCE_M,0);
    while(!((PINA & 1<< PA3) && (PINA & 1<< PA4))){     //deuxième intersection = rotation
        robotTest.suivreLigne();
    }
    _delay_ms(400);                                     //continue d'avancer un peu
    robotTest.getMoteur().tourner(1);                   //tourne à gauche
    _delay_ms(1000);                                    //début sans verifier condition pour qu'il ne reste pas bloqué sur la ligne
    while(!(PINA & 1 << PA2)){};

    robotTest.getMoteur().synchroniserRoues(0,0);       //pause
    _delay_ms(1000); 

    robotTest.getMoteur().synchroniserRoues(PUISSANCE_M,0);

    partirClock(260);                                   //hardcode petit segment en avançant un temps determiné par clock
    while(gCompteur != 105){                            //83 = compteur de base pour avoir le devant sur ligne jaune
        robotTest.suivreLigne();
    }

    robotTest.getMoteur().synchroniserRoues(0,0);       //pause
    _delay_ms(1000);

    robotTest.getMoteur().tourner(1);                   //virage hardcodé sur ligne jaune
    _delay_ms(3700);
    
    robotTest.getMoteur().synchroniserRoues(0,0);       //pause
    _delay_ms(1000);

    //robotTest.getMoteur().synchroniserRoues(PUISSANCE_M,0);
    robotTest.getMoteur().ajusterVitesseRoueD(42);                          //ajustement roues pour essayer de rouler droit
    robotTest.getMoteur().ajusterVitesseRoueG(PUISSANCE_M);

    while(!((PINA & 1<<PA2) && (PINA & 1<< PA3) && (PINA & 1<< PA4))){      //avance puis suis ligne jusqu'au point B, condition = trois pins de gauche
        robotTest.suivreLigne();
    }

    _delay_ms(300);                                                         //avance un peu puis complète boucle avec suivre ligne et rotations
    robotTest.getMoteur().tourner(1);
    while(!(PINA & 1 << PA2)){};
    robotTest.getMoteur().synchroniserRoues(PUISSANCE_M,0);
    while(!((PINA & 1<< PA3) && (PINA & 1<< PA4))){
        robotTest.suivreLigne();
    }

    _delay_ms(400);
    robotTest.getMoteur().tourner(1);
    _delay_ms(1000);                                                        //début sans verifier condition pour qu'il ne reste pas bloqué sur la ligne
    while(!(PINA & 1 << PA2)){};
    robotTest.getMoteur().synchroniserRoues(PUISSANCE_M,0);
    while(!((PINA & 1<< PA3) && (PINA & 1<< PA4))){
        robotTest.suivreLigne();
    }

    _delay_ms(400);
    robotTest.getMoteur().tourner(1);
    while(!(PINA & 1 << PA2)){};

    
        


   // for ( int i =0; i < 1000; i++){
    //    robotTest.suivreLigne();
    //    _delay_ms(5);
    //}       

//    robotTest.getMoteur().tourner(1);
//    _delay_ms(5);
//    while (!(PINA & 1<<PA2)){};
//    robotTest.getMoteur().synchroniserRoues(65,0); // faire suivre ligne avec for + delais
//    _delay_ms(2000);
//    robotTest.getMoteur().tourner(0);
//    _delay_ms(1500);
//    robotTest.getMoteur().synchroniserRoues(65,0);
//    while (!(PINA & 1<<PA4) && !(PINA & 1<<PA3)){
//        robotTest.suivreLigne();
//    };
//    robotTest.getMoteur().tourner(1);
//
//    while (!(PINA & 1<<PA2)){};
//    while (!(PINA & 1<<PA4) && !(PINA & 1<<PA3)){
//        robotTest.suivreLigne();
//    }
//    robotTest.getMoteur().tourner(0);
//    while (!(PINA & 1<<PA2)){};

    return 0;
}
