/* -------------------------------------------------|
| Fichier:     controlDel.h                         |
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

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>

// Les deux broches pour le branchement de la DEL doivent
// etre sur le même port.

void initialisationDel(volatile uint8_t& ddrx);

// ddrx: DDRA, DDRB, DDRC, DDRD
// doit être en majuscules

void allumerAmbre(volatile uint8_t& portx, uint8_t brocheNegative, 
    uint8_t brochePositive, uint16_t delai);

// Le delai est optionnel et est par defaut à 0.
// Si un delai est specifie, la DEL s'eteint apres le delai specifie.

void allumerDel(volatile uint8_t& portx, uint8_t brocheNegative, 
    uint8_t brochePositive, uint8_t couleur, uint16_t delai);

// Restriction: la couleur ambre necessite de specifier un delai.

// portx: PORTA, PORTB, PORTC, PORTD
// doit être en majuscules

// broches: 0 à 7

// couleur: 0 à 3 
// 0 -> eteint,
// 1 -> rouge, 
// 2 -> vert, 
// 3 -> ambre

// delai:
// delai doit être en ms
// delai minimum : 10 ms 
// delai maximum : 655 s 





 
