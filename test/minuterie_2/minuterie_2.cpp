#include "minuterie_2.h"

void partirTimer2 ( uint16_t periodeTi) {
    TCNT2 = 0;
    OCR2A = periodeTi;
    //TCCR2A = (1<<COM2A0) | (1<<COM2B0); // pour OC2A et OC2B on compare match 
    TCCR2B = (1 << CS22) | ( 1<< CS21) | ( 1<< CS20) ;
    TIMSK2 |= ( 1 << OCIE2A); // ( 1 << OCIE2B)

}

void partirClock (uint16_t periodeCl){
    gCompteur = 0;
    TIMSK2 |= ( 1 << OCIE2B);
    OCR2B = periodeCl;
}

void eteindreClock () {
    TIMSK2 = ( 0 << OCIE2B) | ( 1 << OCIE2A);
}

// obstacle entre 46" et 55" (116.84 a 139.70)
float calculerDistance(float vitesse){
    // po/s (valeur a determiner empiriquement)
    /*partirClock(periodeFreqCl);
    while ( distance>12 ) {
        if (gCompteur == 300){
            distance = 12;
        }
    }
    eteindreClock();*/
    //fonction attendre -> comment gerer cli et sei?
    float distanceDepartRobot = vitesse * (gCompteur/30);
    float distanceDepartObstacle = distanceDepartRobot + distance;
    return distanceDepartObstacle;
}

// test: vitesse ~4.3 cm/s, obs 50" (127 cm) -­> delai de 11 223 ms
// test: vitesse ~4.3 cm/s, obs 46" (116.84 cm) -­> delai de 13 586 ms max
// test: vitesse ~4.3 cm/s, obs 55" (139.70 cm) -­> delai de 8 270 ms min; 2.57 sec
uint16_t calculerDelaiFin(float vitesse, float obstacle1) {
    float distanceFin = DISTANCE_TOTALE - DEMI_ROBOT - obstacle1;
    uint16_t delai = distanceFin / vitesse;     
    return delai; // en sec 
}
// (182.88 - 17 - 139.70) / 12 = 2.35 (delai min)
// (182.88 - 17 - 116.84) / 12 = 4.09 (delai max)

// (182.88 - 17 - 139.70) / 10 = 2.62 (delai min)
// (182.88 - 17 - 116.84) / 10 = 4.90 (delai max)

