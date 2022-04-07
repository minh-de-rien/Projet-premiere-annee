#include "lcd.h"

// DECLARATION DE FONCTIONS
void static inline w(void);
void afficherLcd(float distance, Unite uniteDeMesure);
void afficherDistanceCentimetre(float distance);
void afficherDistancePouce(float distance);

// CONSTANTES
const uint8_t N_CHAR = 8;
const float   POUCE  = 2.54;

void static inline w(void) {
	cp_wait_ms(2000);
}

void afficherLcd(float distance, Unite uniteDeMesure) {	
	// Cr�ation de l'objet (l'afficheur est connect� sur le port DEMO_PORT)
	LCM lcd(&DDRC, &PORTC);

	char distanceAffichee[N_CHAR];

	if (uniteDeMesure == Unite::UNITE_POUCE) 
		sprintf(distanceAffichee, "%.2fpo", (double) distance);
	else
		sprintf(distanceAffichee, "%.2fcm", (double) distance);

    lcd.write(distanceAffichee, 0, true);
    w();
}

void afficherDistanceCentimetre(float distance) {
	afficherLcd(distance, Unite::UNITE_CM);
}

void afficherDistancePouce(float distance) {
	distance = distance / POUCE;
	afficherLcd(distance, Unite::UNITE_POUCE);
}
