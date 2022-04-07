
#define F_CPU 8000000UL 
#include <stdlib.h>
#include <avr/io.h>
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

void static inline w(void) {
	cp_wait_ms(2000);
}

int main(void) {	
	// Cr�ation de l'objet (l'afficheur est connect� sur le port DEMO_PORT)
	LCM lcd(&DDRC, &PORTC);
    const char* distance = "12,5 po";
	const char* distance2 = "13 po";
    //float distance3 = 12.5;                                                                                  
	//char msg[20];
	//sprintf_s(msg, "%.1f po", distance); 
	
    lcd.write(distance, 0, true);
    w();
	lcd.write(distance2, 15, false);
	w();
}