#include "robot.h"
#include "boutonBlanc1.h"
#include "initialisationBouton.h"

// CONSTANTES
const uint8_t  D2      = 0x04;
const uint8_t  D3      = 0x08;
const uint8_t  B1      = 0x01;

// VARIABLE VOLATILE
volatile uint8_t compteurUnite = 0;
volatile uint8_t gBoutonBlanc  = 0;
volatile Unite   unite         = UNITE_POUCE;
volatile uint8_t gInterrupteur = 0; // bouton sur la carte 
volatile float   distance      = 40;
Etape etat = DEBUT;

// DECLARATION DE FONCTIONS
bool antiRebondBoutonBlanc()
{
    if ((PIND & D3) ^ D3) {
        _delay_ms(10);
        return ((PIND & D3) ^ D3);
    } 
    return false;
}

bool antiRebondInterrupt() {
    if (PIND & D2) {
        _delay_ms(10);
        return PIND & D2;
    }
    return false;
}

// ROUTINES D'INTERRUPTIONS
ISR(INT0_vect)
{
    if (antiRebondInterrupt())
        gInterrupteur = 1;      
}

ISR(INT1_vect)
{
    if (antiRebondBoutonBlanc()) {
        // Si le robot est en attente et la DEL est rouge
        if ((etat == ATTENTE1 || etat == ATTENTE2) && (PINB & B1)) {
            if (unite == UNITE_POUCE) 
                unite = UNITE_CM;
            else 
                unite = UNITE_POUCE;
        }
    }
    
    // if (compteurUnite == 0) {
    //     unite = UNITE_CM;
    //     //compteurUnite = 1;
    // }

    // if (compteurUnite == 1) {
    //     unite = UNITE_POUCE;
    //     //compteurUnite = 0;  
    // }    
    //gBoutonBlanc = 1;
}

int main() { 

    // TESTER LCD
    // TESTER SON
    // TESTER MOTEUR

    // Initialisation 
    float distanceCalculee = 0;
    initialisationBoutonBlanc(MODE_FRONT_DESCENDANT);
    initialisationBouton(MODE_FRONT_MONTANT);
    float distance2 = 50.5;

    // Test fonction attendre() dans classe robot
    Robot robot;
    robot.getMoteur().initialiser();

     
    // **Situation initiale
    robot.getDel().allumerDel(COULEUR_VERT);
    //afficherDistance(distance, UNITE_POUCE);
    jouerSonDistance(40);
    // robot.getMoteur().initialiser();
    // robot.getMoteur().synchroniserRoues(50, 0);
    _delay_ms(1000);
    etat = ATTENTE1;
    // Appeler attendre()
    robot.attendre(etat, distance);

    // **Test apres attendre() 
    robot.getDel().allumerDel(COULEUR_ROUGE);
    //afficherDistance(distance, UNITE_POUCE); 
    //jouerSonDistance(distance);
    //Moteur moteur(PORTB, 3, PORTB, 6); 
    //moteur.initialiser();
    //robot.getMoteur().synchroniserRoues(50, 0);

    // DDRB = 0XFF; // vert = pouce
    // while (true) {                       
    //     afficherDistance(distance, unite);            
    // }
    
    return 0;
}