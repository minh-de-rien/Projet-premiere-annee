#define F_CPU 8000000UL 
#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"
//#include <cstdio>

enum Unite {
    UNITE_CM,
    UNITE_POUCE
};

void static inline w(void);
void afficherLcd(float distance, Unite uniteDeMesure);
void afficherDistanceCentimetre(float distance);
void afficherDistancePouce(float distance);
