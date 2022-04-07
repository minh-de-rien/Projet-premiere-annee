/* -------------------------------------------------|
| Fichier:     capteurDistance.cpp                  |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme calcule la distance     |
|              entre le capteur de distance et      |
|              un obstacle donné en transformant le |
|              voltage détecté en valeur numérique. |
| Matériel:    Le fil relié à la prise de données   |
|              est branché sur le pin #7 du port A. |
|---------------------------------------------------|
*/

#include "capteurDistance.h"

// DECLARATION DE FONCTION
uint8_t lireCapteurIR();
void    mesurerDistance();
void    trier(uint8_t voltagesIR[], uint8_t taille);


void mesurerDistance(const float C1, const float C2) {
    // Initialisation du port A en mode entrée
    DDRA &= ~(1 << PA6);

    uint8_t voltagesIR[N_MESURES];

    // Prise de données : 25 fois
    for (int i = 0; i < N_MESURES; i++)
        voltagesIR[i] = lireCapteurIR();

    // Tri les données en ordre croissant afin de prendre la valeur
    // du milieu
    trier(voltagesIR, N_MESURES);

    // Calcul de la distance entre le capteur de distance et l'obstacle
    distance = pow(voltagesIR[N_MESURES / 2] / C1, 1 / C2) * 100 - 10;
}

uint8_t lireCapteurIR() {
    can capteurIR;
    return capteurIR.lecture(A6) >> DECALAGE;
}

void trier(uint8_t voltagesIR[], uint8_t taille) {
    for(int voltage = 0; voltage < taille - 1; voltage++) {
        bool flag = true;
        for (int i = 0; i < (taille - voltage + 1); i++) {
            if (voltagesIR[i] > voltagesIR[i + 1]) {
                int temp = voltagesIR[i];
                voltagesIR[i] = voltagesIR[i + 1];
                voltagesIR[i + 1] = temp;
                flag = false;
            }
        }
        if (flag) break;
    }
}
