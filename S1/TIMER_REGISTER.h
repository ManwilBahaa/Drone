/*
 * TIMER_REGISTER.h
 *
 *  Created on: Aug 23, 2023
 *      Author: Manwil
 */

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#include "STD_TYPES.h"

//timer 0
#define TCCR0 *((volatile u8*) 0x53)
#define TCNT0 *((volatile u8*) 0x52)
#define OCR0 *((volatile u8*) 0x5C)
#define TIMSK *((volatile u8*) 0x59)
#define TIFR *((volatile u8*) 0x58)

//timer 1
#define TCCR1A *((volatile u8*) 0x4F)
#define TCCR1B *((volatile u8*) 0x4E)

//#define TCNT1H *((volatile u8*) 0x4D)
#define TCNT1 *((volatile u16*) 0x4C)

//#define OCR1AH *((volatile u8*) 0x4B)
#define OCR1A *((volatile u16*) 0x4A)

//#define OCR1BH *((volatile u8*) 0x49)
#define OCR1B *((volatile u16*) 0x48)

//#define ICR1H *((volatile u8*) 0x47)
#define ICR1 *((volatile u16*) 0x46)

#endif /* TIMER_REGISTER_H_ */
