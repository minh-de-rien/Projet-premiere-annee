#define F_CPU 8000000UL
#include <avr/io.h> 
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

extern volatile float gCompteur; 
extern volatile float distance; 

// CONSTANTES
const float DISTANCE_TOTALE  = 182.88;
const float TAILLE_ROBOT     = 18.5; 
const float DEMI_ROBOT       = 17; // avant 7.62 qui depasse lors du virage
const uint16_t CONVERSION_MS = 1000;

void partirTimer2 ( uint16_t periodeTi); // normal PWM, interrupt, prescaler = 1024
void partirClock (uint16_t periodeCl);
void eteindreClock ();
float calculerDistance(float vitesse);
uint16_t calculerDelaiFin(float vitesse, float obstacle1);