/* -------------------------------------------------|
| Fichier:     boutonBlanc.h                        |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme initialise le bouton    |
|              poussoir installé sur la platine     |
|              d'expérimentation.                   |
| Matériel:    Le fil relié à la prise de données   |
|              est branché sur le pin #4 du port D. |
|---------------------------------------------------|
*/

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "initialisationBouton.h"

void initialisationBoutonBlanc(ModeIB mode); 
