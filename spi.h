/*
 ============================================================================
 Name        :	spi.h
 Author      :	Mateusz Kaczmarczyk
 Version     :	Atmega8, should work at Atmega32 too
 Description :	See uart.h
 ============================================================================
 */
#ifndef _SPI_H
#define _SPI_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define MOSI (1 << 3)
#define MISO (1 << 4)
#define SCK (1 << 5)

#define CS_DDR DDRB
#define CS (1<<2)					// TODO: check PINout for CS
#define CS_ENABLE() (PORTB &= ~CS)
#define CS_DISABLE() (PORTB |= CS)

void SPI_init();
unsigned char SPI_write(unsigned char byte);

#endif
