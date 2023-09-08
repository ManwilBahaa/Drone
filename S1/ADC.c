/*
 * ADC.c
 *
 *  Created on: Aug 21, 2023
 *      Author: Manwil
 */

#include "ADC_REGISTER.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "INTERRUPT.h"

void ADC_INIT()
{
	/* ADMUX
			bit7-6 - refrence voltage selection (AREF - 00 , VCC -01)
			bit5 - left adjust

			bit4-0 -analog channel selection (00xxx - single ended )
	 */

	/* ADCSRA
			bit7 - ADC ENABLE (1)
			bit6 - start conversation
			bit5 - auto trigger (0)
			bit4 - ADC INTERRUPT FLAG
			bit3 - ADC INTERRUPT enable

			bit2-0 - prescaler select bits (division factor
											000 - 2
											010 - 4
											011 - 8
											100 - 16
											101 - 32
											110 - 64
											111 - 128 )
	 */

	ADMUX = 0b01000000;

	// enable adc - set prescaler to 128 division
	ADCSRA = 0b10000111;

}

u16 ADC_u16_READ(u8 channel)
{
	channel &=0b00000111;
	ADMUX &= 0b11100000;

	ADMUX |= channel;
	// disable interrupts
	INTERRUPT_GIE_DISABLE();

	// start conversation , enable adc interrupt , set prescaler to 123
	ADCSRA |=0b01001111;

	while(GET_BIT(ADCSRA , 4)==0){}

	// clear interrupt flag
	SET_BIT(ADCSRA , 4);

	// enable interrupts
	INTERRUPT_GIE_ENABLE();


	u16 data =  ADCL | ADCH<<8;

	return data;

}
