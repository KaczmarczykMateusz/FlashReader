/*
============================================================================
Name		: main.C
Author		: Mateusz Kaczmarczyk
Version		: Voltage conversion and frequency measurnment at ICP1 PIN
				with display result at LCD HD44780
Description : Voltage measurement is with +/- 0.05V tolerance,
				Frequency measure
				PWM generation controlled with incrementing / decrementing keys
				If doesn't initialize correctly try addindg delays after
				initialization SPI and FAT
============================================================================
*/
#include "main.h"

int main(void) {
	char LCDbuffer[16];
	int8_t readFileStatus;

	key upKey = keyInit(&DDRC, &PORTC, &PINC, UP_BTN_MASK);
	key dwnKey = keyInit(&DDRC, &PORTC, &PINC, DOWN_BTN_MASK);

	LCD_Initalize();
	SPI_init();

	int8_t SD_InitStatus = SD_init();
	int8_t FAT_InitStatus = fat16_init();
	int8_t openFileStatus = fat16_open_file("HAMLET  ", "TXT");

	while(1) {
		LCD_Clear();
		sprintf(LCDbuffer, "Initialisation:");
		LCD_WriteText(LCDbuffer);

		sprintf(LCDbuffer, "SD:%d FAT:%d F:%d", SD_InitStatus, FAT_InitStatus, openFileStatus);
		LCD_GoTo(0,1);
		LCD_WriteText(LCDbuffer);
		_delay_ms(5000);

	    while(fat16_state.file_left) {
	        readFileStatus = fat16_read_file(FAT16_BUFFER_SIZE);

	        for(uint8_t i=0; i<16 ; i++) {
	        	if(fat16_buffer[i] == 0x0D) {	//Replace ENTER with whitespace
	        		fat16_buffer[i] = ' ';
	        	}
	        	LCDbuffer[i] = fat16_buffer[i];
	        }

			LCD_Clear();
			LCD_WriteText(LCDbuffer);

			for(uint8_t i=16; i<32 ; i++) {
				if(fat16_buffer[i] == 0x0D) {	//Replace ENTER with whitespace
					fat16_buffer[i] = ' ';
				}
				LCDbuffer[i-16] = fat16_buffer[i];
			}
			LCD_GoTo(0, 1);
			LCD_WriteText(LCDbuffer);
			_delay_ms(2000);
#if 0
			keyIncrDcr(&upKey, &dwnKey, &dutyCycle, 255);
			for(int8_t i=0; i<readFileStatus; i+8) {
	        uartPutc(fat16_buffer[i]);
	        }
			for(int8_t i=0; i<readFileStatus; i+8) {
				uartPutc(fat16_buffer[i]);
			}
#endif
	    }
	}
}
