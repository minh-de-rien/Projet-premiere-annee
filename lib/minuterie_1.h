/* -------------------------------------------------|
| Fichier:     minuterie_1.h                        |
| Auteurss:    Nils Coulier                         |
|              Minh Ngoc Do                         |
|              Jolan Le Clainche-Vernaudon          |
|              Rosie Morissette                     |
| Date:        8 décembre 2021                      |
| Description: Ce programme permet de partir la     |
|              minuterie 1 selon un mode et un      |
|              prescaler donné.                     |
|---------------------------------------------------|
*/

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <avr/interrupt.h>

enum Mode {
	MODE_NORMAL,
	MODE_CTC,
	MODE_PHASE_CORRECTE,
	MODE_PWM_RAPIDE
};

enum Prescaler {
	PRESCALER_1,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024
};

class Minuterie {
public:
	Minuterie(uint8_t modeMinuterie, uint16_t modePrescaler, 
		       uint16_t dureeA = 0, uint16_t dureeB = 0) {
		modeMinuterie_ = modeMinuterie;
		modePrescaler_ = modePrescaler;
		dureeA_		   = dureeA;
		dureeB_		   = dureeB;
	}

	void partirMinuterie();

protected:
	void fixerModeMinuterie();
	void fixerPrescaler();

private:
	uint8_t modeMinuterie_;
	uint8_t modePrescaler_;
	uint16_t dureeA_;
	uint16_t dureeB_;
};

