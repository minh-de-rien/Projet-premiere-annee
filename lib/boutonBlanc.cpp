/* -------------------------------------------------|
| Fichier:     boutonBlanc.cpp                      |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        29 novembre 2021                     |
| Description: Ce progrogramme initialise le bouton |
|              poussoir installé sur la platine     |
|              d'expérimentation.                   |
| Matériel:    Le fil relié à la prise de données   |
|              est branché sur le pin #4 du port D. |
|---------------------------------------------------|
*/

#include "boutonBlanc.h"

void initialisationBoutonBlanc(ModeIB mode) {
    
    // cli est une routine qui bloque toutes les interruptions.
    cli ();

    DDRD &= ~(1 << PD3); // Port D en mode entree

    //Permettre les interruptions externes
    EIMSK |= (1 << INT1) ;

    // mettre EICRA à 0
    switch (mode) {
        case ModeIB::MODE_BAS_NIVEAU :
            break;
        case ModeIB::MODE_FRONT_QUELCONQUE :
            EICRA |= (1 << ISC10);
            break;
        case ModeIB::MODE_FRONT_DESCENDANT :
            EICRA |= (1 << ISC11);
            break;
        case ModeIB::MODE_FRONT_MONTANT :
            EICRA |= (1 << ISC11) | (1 << ISC10);
            break;
    }
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}
