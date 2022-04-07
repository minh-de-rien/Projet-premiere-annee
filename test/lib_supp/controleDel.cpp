/* -------------------------------------------------|
| Fichier:     controlDel.cpp                       |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme initialise la DEL       |
|              libre, permet de l'allumer et de     |
|              changer les couleurs selon un état   |
|              entré en paramètre.                  |
| Matériel:    Le fil relié à la prise de données   |
|              est branché sur le pin #4 du port D. |
|---------------------------------------------------|
*/

#include "initialisationBouton.h"
#include "minuterie_1.h"
#include "controleDel.h"

// CONSTANTES
const uint8_t DELAI_VERT    = 5;  // en millisecondes
const uint8_t DELAI_ROUGE   = 5;  // en millisecondes
const uint8_t DELAI_AMBRE   = 10; // delai_vert + delai_rouge
const uint8_t AJUSTEMENT    = 10; // pour ajuster le nombre d'iterations 
                                  // de la boucle avec le delai en parametre
const uint8_t DELAI_ALLUMER = 10; // pour deminuer le delai de la boucle for


// ddrx: DDRA, DDRB, DDRC, DDRD
// doit être en majuscules

void initialisationDel(volatile uint8_t& ddrx) {
    ddrx = 0xff;                   
}

void allumerAmbre(volatile uint8_t& portx, uint8_t brocheNegative, 
    uint8_t brochePositive, uint16_t delai) {
    
    for (uint16_t i = 0; i < (delai/DELAI_AMBRE); i++) 
    {
        portx |= 1 << brocheNegative; 
        _delay_ms(DELAI_ROUGE); 
        portx &= ~(1 << brocheNegative); 
        portx |= 1 << brochePositive;
        _delay_ms(DELAI_VERT); 
        portx &= ~(1 << brochePositive); 
    }    
}

// Parametres:

// Restriction: la couleur ambre necessite de specifier un delai

// portx: PORTA, PORTB, PORTC, PORTD
// doit être en majuscules

// broche: 0 à 7

// couleur: 0 à 3 
// 0 -> eteint,
// 1 -> rouge, 
// 2 -> vert, 
// 3 -> ambre

// delai:
// delai doit être en ms
// delai minimum : 10 ms 
// delai maximum : 655 s 

void allumerDel(volatile uint8_t& portx, uint8_t brocheNegative, 
    uint8_t brochePositive, uint8_t couleur = 0, uint16_t delai = 0) {  

    enum Couleur {      
        COULEUR_ETEINT = 0,        
        COULEUR_ROUGE,
        COULEUR_VERT,
        COULEUR_AMBRE
    };   

    switch (couleur) {
        case COULEUR_ETEINT :
            portx &= ~(1 << brochePositive); 
            portx &= ~(1 << brocheNegative);           
            break;
        case COULEUR_ROUGE :
            portx |= 1 << brocheNegative;  
            portx &= ~(1 << brochePositive); // autre pin eteinte       
            break;
        case COULEUR_VERT:
            portx |= 1 << brochePositive; 
            portx &= ~(1 << brocheNegative); // autre pin eteinte            
            break;
        case COULEUR_AMBRE :
            allumerAmbre(portx, brocheNegative, brochePositive, delai);
            break;
        default : // ne devrait pas se rendre ici            
            break;
    }
    
    // delai pour COULEUR_ROUGE et COULEUR_VERT
    if (delai != 0 && couleur != 3){     
        for (uint16_t i = 0; i < (delai/AJUSTEMENT); i++){                 
            _delay_ms(DELAI_ALLUMER);                        
        }     
        // eteindre la DEL
            portx &= ~(1 << brochePositive);     
            portx &= ~(1 << brocheNegative);     
    }          
}   


