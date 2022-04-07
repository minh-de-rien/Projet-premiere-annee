#include "lcd.h"
#include "util/delay.h"
#include "can.h"

void afficherDistance(float distance, Unite unite);

// CONSTANTES
const uint8_t A6                = 6;
const uint8_t DECALAGE          = 2;
