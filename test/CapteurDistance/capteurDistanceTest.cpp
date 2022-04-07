/* 
Jolan Le Clainche
Nils Coulier

On utilise ici un processeur artmega324pa.

La borne positive de la led est liee au bit 0 du port B et la borne negative au bit 1. 

Si la lumière est basse (en cachant la photorésistance), la DEL prendra la couleur verte. (Port B = 0b10)
Si la lumière est à un bon niveau (lumière ambiante), la DEL tournera à l'ambré.   (Port B alterne entre 0b10 et 0b01)
Si la lumière est trop forte (photorésistance sous une lampe de poche), la DEL devient rouge. (Port B = 0b01)

Le convertisseur (CAN) permet de convertir le signal analogique (entrant en A0) en signal numerique.
On utilise se signal numerique pour determiner si la lumiere est basse, haute ou normale.
*/

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h> 


#include "can.h"
#include "lcd.h"


// CONSTANTES
const uint8_t ROUGE             = 0b01;
const uint8_t VERT              = 0b10;
const uint8_t ETEINT            = 0b00;
const uint8_t A6                = 6;
const uint8_t DECALAGE          = 2;
const float   DISTANCE_12_POUCES = 30.48;
const float   DISTANCE_24_POUCES = 60.96;
const uint8_t N_MESURES          = 25;


uint8_t lireCapteurIR(){
    can capteurIR;
    return capteurIR.lecture(A6) >> DECALAGE;
}

void sort(uint8_t voltagesIR[], uint8_t taille) {
    for(int voltage = 0; voltage < taille - 1; voltage++) {
        bool flag = true;
        for (int i = 0; i < (taille - voltage+1); i++) {
            if (voltagesIR[i] > voltagesIR[i+1]) {
                int temp = voltagesIR[i];
                voltagesIR[i] = voltagesIR[i+1];
                voltagesIR[i+1] = temp;
                flag = false;
            }
        }
        if (flag) break;
    }
}

// int mostFrequent(int arr[], int n)
// {
//     // Sort the array
//     //sort(arr, );
 
//     // find the max frequency using linear traversal
//     int max_count = 1, res = arr[0], curr_count = 1;
//     for (int i = 1; i < n; i++) {
//         if (arr[i] == arr[i - 1])
//             curr_count++;
//         else {
//             if (curr_count > max_count) {
//                 max_count = curr_count;
//                 res = arr[i - 1];
//             }
//             curr_count = 1;
//         }
//     }
 
//     // If last element is most frequent
//     if (curr_count > max_count)
//     {
//         max_count = curr_count;
//         res = arr[n - 1];
//     }
 
//     return res;
// }

// inspire de https://www.arduino.cc/reference/en/language/functions/math/map/ 
long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main() {
    DDRA &= ~(1 << PA6);
    DDRB |= (1 << PB0) | (1 << PB1);

    uint8_t voltageIR;
    float distance;

    uint8_t voltagesIR[N_MESURES];

    Lcd lcd;
    LCM lcm(&DDRC, &PORTC);
    while (true) {
        //voltageIR = lireCapteurIR();

        for (int i = 0; i < N_MESURES; i++) {
            voltagesIR[i] = lireCapteurIR();
            _delay_ms(40);
        }

        sort(voltagesIR, N_MESURES);

        // int n = sizeof(voltagesIR) / sizeof(voltagesIR[0]);
        // int vol = mostFrequent(voltagesIR, n);

        // float sum = 0;
        // for (int i = 0; i < 100; i++)
        //     sum += lireCapteurIR();

        // float voltage = sum / 100;
        //float voltageFinale = voltage*5.0/1024;
        
        //sort(voltagesIR, 1001);
        //distance = pow(21579 / (50*voltageIR), 1000/617);
        //distance = (2998.8 * pow(voltageIR, -1.149));
        //distance = 2377.9 * pow(voltageIR, -1.045);

        //afficherDistanceCentimetre(distance*100+0.9);

        //distance = 245.49 * pow(voltageIR, -0.56);
        //distance = 8 * pow(10, -5) * pow(voltagesIR[25/2], 4) + 0.0141 * pow(voltagesIR[25/2], 3) + 0.7669 * pow(voltagesIR[25/2], 2) - 16.918 * voltagesIR[25/2] + 175.42;

        //distance = pow(voltage / 16.7647563, 1 / -0.85803107);
        //distance = pow(voltagesIR[25/2] / 16.7647563, 1 / -1.00803107) * 100; // avec 5.7V
        //distance = pow(vol / 16.7647563, 1 / -1.00503107) * 100 - 10;

        distance = 27.728 * pow(map(voltagesIR[25 / 2], 0, 1023, 0, 5000)/1000.0, -1.2045);

        //distance = 27.728 * pow(map(voltagesIR[25 / 2], 0, 4095, 0, 5000)/1000.0, -1.2045);
        //distance = 27.728 * pow(map(voltagesIR[25 / 2], 0, 2998.8, 0, 2377.9), -1.045);
        
        //distance = 27.728 * pow(voltagesIR[25 / 2] / 1000.0, -1.2045);


        lcd.afficherLcd(lcm, distance, UNITE_CM);

        _delay_ms(33);

    }

    return 0;
}

