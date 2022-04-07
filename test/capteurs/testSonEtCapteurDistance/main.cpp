#include "son.h"
#include "capteurDistance.h"
#include "lcd.h"

//volatile float distance = 0;

int main() {
    DDRD = 0xff;
    DDRB = 0xff;

    const float   C1_MUR        = 16.7647563;
    const float   C1_POTEAU     = 16.5647563;
    const float   C2_MUR        = -1.00503107;
    //const float   C2_MUR        = -0.85803107;
    const float   C2_POTEAU     = -1.00503107;
    //LCM lcm(&DDRC, &PORTC);
    Lcd lcd;
    Minuterie minuterie(Mode::MODE_CTC, Prescaler::PRESCALER_256, 0, 0);
    minuterie.partirMinuterie();

    while (true) {
        mesurerDistance(C1_MUR, C2_MUR);

        LCM lcm(&DDRC, &PORTC);
        lcd.afficherLcd(lcm, distance, UNITE_CM);

        jouerSonDistance(distance);
        _delay_ms(500);

        // lcm.clear();
        // _delay_ms(500);
    }
    
    TCCR1B = (0 << CS12);
    return 0;
}