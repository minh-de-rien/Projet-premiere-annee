#include "attente.h"

// Bouton blanc connecté à PD3 (INT1_vect)

// CONSTANTES
volatile uint8_t gInterrupteur = 0; // bouton sur la carte 
volatile Unite unite = UNITE_POUCE;
volatile uint8_t compteurUnite = 0;
// État?

// ROUTINES D'INTERRUPTIONS
ISR(INT0_vect)
{
    gInterrupteur = 1;      
}

// mettre
ISR(INT1_vect)
{
    if (compteurUnite == 0) {
        unite = UNITE_CM;
        compteurUnite = 1;
    }

    if (compteurUnite == 1) {
        unite = UNITE_POUCE;
        compteurUnite = 0;  
    }    
}

void attendre(Etape etat, Del& del, Unite unite, float distance, Moteur& moteur, LCM* lcd) { // classe robot: pas besoin del et moteur

    // initialiser LCD (protection contre copie empeche passage en param) CLASSE ROBOT: PAS BESOIN
    //LCM lcd(&DDRC, &PORTC);

    // Eteindre son, moteurs
    eteindreSon();
    moteur.synchroniserRoues(0, 0);

    // Del en rouge
    del.allumerDel(COULEUR_ROUGE);
    
    // initialiser bouton carte
    initialisationBouton(MODE_FRONT_MONTANT);
       
    if (etat == OBSTACLE1 || etat == OBSTACLE2) {

        while (gInterrupteur != 1) {                       
            afficherDistance(distance, unite);            
        }          
        //{                       
            
            // if ((PIND | PD3) != 0xff) {
            //     del_.allumerDel(COULEUR_VERT);
            //     _delay_ms(500);
            //     changerUnite();                
            // }//PIND |= (1 << PD3)
            //(PIND | PD3) != 0xff
            //(PIND & ~(1 << PD3)) == 0
            // PIND & PD3
        //}  
        
        // eteindreLcd();         
        lcd->clear(); 
    }

    else {        
        while (gInterrupteur != 1) {}            
    }

    gInterrupteur = 0;

    del.allumerDel(COULEUR_VERT);
    _delay_ms(FAIRE_RIEN); 
}

int main() {

    //*** Initialisation 
    float distance = 50.5; 
    // del test robot
    Del del(&DDRB, &PORTB, 1, 0);
    // del test simulIDE 
    //Del del(&DDRA, &PORTA, 0, 1); 
    Moteur moteur(PORTB, 3, PORTB, 6);   
    LCM lcd(&DDRC, &PORTC);

    //*** Situation initiale : Del verte, LCD pouce, moteur, son
    del.allumerDel(COULEUR_VERT);    
    jouerSonDistance(distance);
    moteur.initialiser();
    moteur.synchroniserRoues(50, 0);
    afficherDistance(distance, UNITE_POUCE);
    //_delay_ms(1000);
        
    //*** Appeler attendre()
    attendre(OBSTACLE1, del, unite, distance, moteur, &lcd);    
 
    //*** Appuyer sur l'interrupteur: apres 2 sec la del devrait etre verte        

    //*** Test LCD
    afficherDistance(distance, UNITE_CM);

    //*** Test son
    //jouerSonDistance(distance);

    //*** Test moteur 
    //Moteur moteur(PORTB, 3, PORTB, 6); 
    //moteur.initialiser();
    moteur.synchroniserRoues(50, 0);

    return 0;
}