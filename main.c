/*
============================================================================
Name		: main.C
Author		: Mateusz Kaczmarczyk
Version		: Voltage conversion and frequency measurnment at ICP1 PIN
				with display result at LCD HD44780
Description : Voltage measurement is with +/- 0.05V tolerance,
				Frequency measure
				PWM generation controlled with incrementing / decrementing keys
============================================================================
*/
#include "main.h"

int main(void) {
	char LCDbuffer[16];

	LCD_Initalize();

	key upKey = keyInit(&DDRC, &PORTC, &PINC, UP_BTN_MASK);
	key dwnKey = keyInit(&DDRC, &PORTC, &PINC, DOWN_BTN_MASK);

	SPI_init();
	_delay_ms(50);

	int8_t SD_InitStatus = SD_init();

	while(1) {
//		keyIncrDcr(&upKey, &dwnKey, &dutyCycle, 255);

		LCD_Clear();
		sprintf(LCDbuffer, "SD_Init: %d", SD_InitStatus);
		LCD_WriteText(LCDbuffer);

		sprintf(LCDbuffer, "Empty yet");
		LCD_GoTo(0,1);
		LCD_WriteText(LCDbuffer);
		_delay_ms(1000);
	}
}
