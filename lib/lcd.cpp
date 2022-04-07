/* -------------------------------------------------|
| Fichier:     lcd.cpp			                    |
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

#include "lcd.h"
#include "minuterie_2.h"


void Lcd::afficherLcd(LCM& lcm, float distance, Unite uniteDeMesure) {
	// Initialisation d'un tableau de char pour l'affichage
	// d'une chaîne de caractère sur le LCD
	char distanceAffichee[N_CHAR];

	if (uniteDeMesure == Unite::UNITE_POUCE) {
		distance = distance / POUCE;
		sprintf(distanceAffichee, "%.1fpo", (double) distance);
	}
	else
		sprintf(distanceAffichee, "%dcm", (int) distance);

    lcm.write(distanceAffichee, 0, true);
}

void Lcd::eteindreLcd(LCM& lcm) {
	lcm.clear();
}
