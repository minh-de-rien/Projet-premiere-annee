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
volatile float distance;
Etape etat;

// DECLARATION DE FONCTIONS
bool antiRebondBoutonBlanc()
{
    if ((PIND & D3) ^ D3) {
        _delay_ms(30);
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

// // Ancien debounce boutonBlanc
// bool debouncer2()
// {
//     if (PIND & PD3)
//     {
//         _delay_ms(10);
//         return PIND & PD3;
//     }
//     return false;
// }

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
    // // Initialisation 
    // initialisationBoutonBlanc(MODE_FRONT_DESCENDANT);
    // initialisationBouton(MODE_FRONT_MONTANT);
    // Robot robot;
    // float distance2 = 50.5;

    // // **Situation initiale
    // robot.getDel().allumerDel(COULEUR_VERT);
    // _delay_ms(1000);
    // etat = ATTENTE1;

    // // Appeler attendre()
    // robot.attendre(etat, distance2);

    // Bouton blanc par scrutation
    etat = ATTENTE1;
    float distance2 = 50.5;
    initialisationBouton(MODE_FRONT_MONTANT);
    LCM lcm(&DDRC, &PORTC); 
    Lcd lcd = Lcd();

    lcd.afficherLcd(lcm, distance2, unite);   
    if (etat == ATTENTE1 || etat == ATTENTE2) {
        do {   
            
                   
            if (unite == UNITE_POUCE) 
                unite = UNITE_CM;
            else 
                unite = UNITE_POUCE;
                // while (antiRebondBoutonBlanc())
                //     lcd.afficherLcd(lcm, distance2, unite);
                // break;
            while (!antiRebondBoutonBlanc()) {
                lcd.afficherLcd(lcm, distance2, unite);   
                //_delay_ms(30);
            }                  
        } while (gInterrupteur != 1); 

        // eteindreLcd();                
        lcd.eteindreLcd(lcm); 
    }
    

    /*
    // // Test bouton blanc par scrutation
    // DDRD = 0x00;
    // while (true) {
    //     robot.getDel().allumerDel(COULEUR_VERT);        
    //     if (debouncer()) {
    //         robot.getDel().allumerDel(COULEUR_ROUGE);
    //         _delay_ms(500);            
    //     }
    // }

    // // Test bouton blanc par scrutation 2
    // DDRD = 0x00;
    // while (true) {
    //     robot.getDel().allumerDel(COULEUR_VERT);        
    //     if (debouncer2()) {
    //         robot.getDel().allumerDel(COULEUR_ROUGE);
    //         _delay_ms(500);            
    //     }
    // }

    // // Test bouton blanc par interruption (fonctionne)
    //   while (true) {
    //     robot.getDel().allumerDel(COULEUR_VERT);
    //     //_delay_ms(500);
    //     if (gBoutonBlanc) {
    //         robot.getDel().allumerDel(COULEUR_ROUGE);
    //         _delay_ms(500);
    //         gBoutonBlanc = 0;
    //     }
    // }

    */

    return 0;
}