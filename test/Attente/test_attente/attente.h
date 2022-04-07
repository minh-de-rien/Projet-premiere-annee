#include <stdlib.h>

#include "lcdMachineEtats.h"
#include "controleDelClass.h"
#include "initialisationBouton.h" 
#include "son.h"
#include "moteur.h"
#include "boutonBlanc.h"

// CONSTANTES

const uint16_t FAIRE_RIEN = 2000; // delai fin attente

enum Etape {
    DEBUT,
    OBSTACLE1,
    ATTENTE1,
    VIRAGE_180_1,
    AVANCER_BOUCLE,
    BOUCLE,
    AVANCER_GAUCHE1,
    OBSTACLE2,
    ATTENTE2,
    EVITEMENT,
    AVANCER_GAUCHE2,
    AVANCER_GAUCHE3,
    OBSTACLE3,
    ATTENTE3,
    VIRAGE_180_2,
    AVANCER_DROIT1,
    AVANCER_DROIT2,
    AVANCER_FIN
};


void attendre(Etape etat, Del del, Unite unite);