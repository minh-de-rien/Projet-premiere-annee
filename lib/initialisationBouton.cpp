/* -------------------------------------------------|
| Fichier:     initialisationBouton.cpp             |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce progrogramme initialise le bouton |
|              d'interruption installé sur la carte.|
|---------------------------------------------------|
*/

#include "initialisationBouton.h"

void initialisationBouton(ModeIB mode) {
    
    // cli est une routine qui bloque toutes les interruptions.
    cli ();

    DDRD &= ~(1 << PD2); // Port D mode entree

    // permettre les interruptions externes
    EIMSK |= (1 << INT0) ;

    // mettre EICRA à 0
    switch (mode) {
        case ModeIB::MODE_BAS_NIVEAU :
            break;
        case ModeIB::MODE_FRONT_QUELCONQUE :
            EICRA |= (1 << ISC00);
            break;
        case ModeIB::MODE_FRONT_DESCENDANT :
            EICRA |= (1 << ISC01);
            break;
        case ModeIB::MODE_FRONT_MONTANT :
            EICRA |= (1 << ISC01) | (1 << ISC00);
            break;
    }
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}
