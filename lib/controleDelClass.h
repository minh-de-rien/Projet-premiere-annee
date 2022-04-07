/* -------------------------------------------------|
| Fichier:     controlDelClass.h                    |
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

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>

enum Couleur {
	COULEUR_VERT,
	COULEUR_ROUGE,	
	COULEUR_AMBRE
};

// Les deux broches pour le branchement de la DEL doivent
// etre sur le même port.

class Del
{
public:
	// ddrx: DDRA, DDRB, DDRC, DDRD (en majuscules)
	// portx: PORTA, PORTB, PORTC, PORTD (en majuscules)
	// broches: 0 à 7
	Del(volatile uint8_t* ddrx, volatile uint8_t* portx, uint8_t brocheNegative,
		uint8_t brochePositive) :
		ddrx_(ddrx), portx_(portx),
		brocheNegative_(brocheNegative),
		brochePositive_(brochePositive) 
		{ *ddrx_ = 0xff; }

	~Del() {}

	// Restriction: la couleur ambre necessite de specifier un delai.
	void allumerAmbre(uint16_t delai);

	// Le delai est optionnel et est par defaut à 0.
	// Si un delai est specifie, la DEL s'eteint apres le delai specifie.
	
	// delai:
	// doit être en ms
	// minimum : 10 ms 
	// maximum : 655 s 
	void allumerDel(Couleur couleur, uint16_t delai = 0);

	void eteindreDel() {
		*portx_ &= ~(1 << brochePositive_);
		*portx_ &= ~(1 << brocheNegative_);
	}

private:
	volatile uint8_t* ddrx_;
	volatile uint8_t* portx_;
	uint8_t brocheNegative_;
	uint8_t brochePositive_;
};
