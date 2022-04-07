/* -------------------------------------------------|
| Fichier:     son.h                                |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme permet d'initialiser    |
|              les moteurs du robot et de contrôler |
|              sa direction et sa vitesse.          |
| Matériel:    Le fil noir du piézo est branché sur |
|              le pin #5 du port D et le rouge, sur |
|              le pin #6 du port D (là où se situe  |
|              OCRIA).                              |
|---------------------------------------------------|
*/

#define F_CPU 8000000UL
#include <avr/io.h> 
#include "minuterie_1.h"
#include <util/delay.h>

const uint16_t MULTIPLICATEUR 		    = 1000;
const uint16_t PRESCALER_SON			= 256;
const uint16_t NUMERATEUR_CALC_OCR1A  	= 8000;     // F_CPU div par 1000
const uint16_t AJUSTEMENT              	= 1000;     // Pour ne pas overflow
const float    TAUX_VARIATION           = -59.06;   // (200-2000)/(60.96 - 30.48)
const uint16_t ORDONNEE_ORIGINE         = 3800;
const uint8_t  FREQ_24PO                = 200;
const uint16_t FREQ_12PO                = 2000;

void jouerSon (uint8_t note);
void jouerSonDistance (float distance);
void eteindreSon();

const double NOTES[] = 
{
    110,            // 45
    116.5409404,
    123.4708253,
    130.8127827,
    138.5913155,
    146.832384,     // 50
    155.5634919,
    164.8137785,
    174.6141157,
    184.9972114,
    195.997718,     // 55
    207.6523488,
    220,
    233.0818808,
    246.9416506,
    261.6255653,    // 60
    277.182631,
    293.6647679,
    311.1269837,
    329.6275569,
    349.2282314,    // 65
    369.9944227,
    391.995436,
    415.3046976,
    440,
    466.1637615,    // 70
    493.8833013,
    523.2511306,
    554.365262,
    587.3295358,
    622.2539674,    // 75
    659.2551138,
    698.4564629,
    739.9888454,
    783.990872,
    830.6093952,    // 80
    880
};
