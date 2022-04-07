/*
Jolan Le Clainche
Nils Coulier
*/
#include <son.h>

int main() {
    DDRD = 0xff;
    DDRB = 0xff;
    float dist = 30.48;
    float dist2 = 60.96;
    float dist3 = 70.96;
    float dist4 = 40.96;
    jouerSonDistance(dist);
    _delay_ms(1000);
    jouerSonDistance(dist2);
    _delay_ms(1000);
    jouerSonDistance(dist3);
    _delay_ms(1000);
    jouerSonDistance(dist4);
    _delay_ms(1000);
    TCCR1B = (0 << CS12);
    return 0;
}