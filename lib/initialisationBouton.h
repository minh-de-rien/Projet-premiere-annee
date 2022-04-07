/* -------------------------------------------------|
| Fichier:     initialisationBouton.h               |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme initialise le bouton    |
|              d'interruption installé sur la carte.|
|---------------------------------------------------|
*/

#ifndef INIT_BOUTON_H
#define INIT_BOUTON_H

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>

enum ModeIB {
    MODE_BAS_NIVEAU,
    MODE_FRONT_QUELCONQUE,
    MODE_FRONT_DESCENDANT,
    MODE_FRONT_MONTANT,
};

void initialisationBouton(ModeIB mode); 

#endif