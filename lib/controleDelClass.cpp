/* -------------------------------------------------|
| Fichier:     controlDelClass.cpp                  |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme initialise la DEL       |
|              libre, permet de l'allumer et de     |
|              changer les couleurs selon un état   |
|              entré en paramètre.                  |
|---------------------------------------------------|
*/

#include "controleDelClass.h"

// CONSTANTES
const uint8_t DELAI_VERT    = 9;   // en ms
const uint8_t DELAI_ROUGE   = 1;   // en ms
const uint8_t DELAI_AMBRE   = 10;  // delai_vert + delai_rouge, en ms
const uint8_t AJUSTEMENT    = 10;  // pour ajuster le nombre d'iterations 
								  // de la boucle avec le delai en parametre
const uint8_t DELAI_ALLUMER = 10; // pour deminuer le delai de la boucle for

void Del::allumerAmbre(uint16_t delai) {

	for (uint16_t i = 0; i < (delai / DELAI_AMBRE); i++) {
		*portx_ |= 1 << brocheNegative_;
		_delay_ms(DELAI_VERT);
		*portx_ &= ~(1 << brocheNegative_);
		*portx_ |= 1 << brochePositive_;
		_delay_ms(DELAI_ROUGE);
		*portx_ &= ~(1 << brochePositive_);
	}
}

void Del::allumerDel(Couleur couleur, uint16_t delai) {
		
	switch (couleur) {	
		case COULEUR_VERT :			
			*portx_ &= ~(1 << brochePositive_); // autre pin eteinte            
			*portx_ |= 1 << brocheNegative_;
			break;
		case COULEUR_ROUGE :			
			*portx_ &= ~(1 << brocheNegative_); // autre pin eteinte       
			*portx_ |= 1 << brochePositive_;
			break;	
		case COULEUR_AMBRE :
			allumerAmbre(delai);
			break;
		default: // ne devrait pas se rendre ici            
			break;
	}

	// delai pour COULEUR_ROUGE et COULEUR_VERT
	if (couleur != 2 && delai != 0) {
		for (uint16_t i = 0; i < (delai / AJUSTEMENT); i++) {
			_delay_ms(DELAI_ALLUMER);
		}
		// eteindre la DEL
		*portx_ &= ~(1 << brochePositive_);
		*portx_ &= ~(1 << brocheNegative_);
	}
}