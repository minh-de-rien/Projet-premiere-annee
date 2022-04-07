/* -------------------------------------------------|
| Fichier:     lcd.h			                    |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme affiche une distance    |
|              donnée en pouce ou en centimètre sur |
|              l'afficheur LCD.                     |
| Matériel:    Les fils du LCD sont branchés sur le |
|              le port C.                           |
|---------------------------------------------------|
*/

#ifndef LCD_H
#define LCD_H

#define F_CPU 8000000UL 
#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"


// CONSTANTES
const uint8_t N_CHAR = 8;
const float   POUCE  = 2.54;

extern volatile float distance;

enum Unite {
    UNITE_CM,
    UNITE_POUCE
};

struct Lcd {
    Lcd() = default;

    void afficherLcd(LCM& lcm, float distance, Unite uniteDeMesure);
    void eteindreLcd(LCM& lcm);
};

#endif
