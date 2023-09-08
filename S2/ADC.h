/*
 * ADC.h
 *
 *  Created on: Aug 21, 2023
 *      Author: Manwil
 */

#ifndef ADC_H_
#define ADC_H_

#include "STD_TYPES.h"

//single
#define ADC0 0b00000000
#define ADC1 0b00000001
#define ADC2 0b00000010
#define ADC3 0b00000011
#define ADC4 0b00000100
#define ADC5 0b00000101
#define ADC6 0b00000110
#define ADC7 0b00000111

void ADC_INIT();
u16 ADC_u16_READ(u8 channel);

#endif /* ADC_H_ */
