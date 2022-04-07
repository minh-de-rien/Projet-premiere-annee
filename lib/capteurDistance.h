/* -------------------------------------------------|
| Fichier:     capteurDistance.h                    |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme calcule la distance     |
|              entre le capteur de distance et un   |
|              un obstacle donné en transformant le |
|              voltage détecté en valeur numérique. |
| Matériel:    Le fil relié à la prise de données   |
|              est branché sur le pin #7 du port A. |
|---------------------------------------------------|
*/

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <math.h> 
#include "can.h"

// CONSTANTES
const uint8_t A6        = 6;
const uint8_t DECALAGE  = 2;
const uint8_t N_MESURES = 25;

// VARIABLE GLOBALE
extern volatile float distance;

// DECLARATION DE FONCTION
uint8_t lireCapteurIR();
void    mesurerDistance(const float C1, const float C2);
void    trier(uint8_t voltagesIR[], uint8_t taille);
