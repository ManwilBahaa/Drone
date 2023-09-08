/*
 * INTERRUPT.h
 *
 *  Created on: Aug 20, 2023
 *      Author: Manwil
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

//INTERRUPT VECTORS
#define INT0 __vector_1
#define INT1 __vector_2
#define INT2 __vector_3

#define TIMER_0_OVF __vector_11
#define TIMER_0_COMP __vector_10

//MOOD SELECT Pg 65
//MCUCR
#define ISC00 0 //INT0
#define ISC01 1

#define ISC10 2 //INT1
#define ISC11 3

//MCUCSR
#define ISC2 6 //INT2

//GIE ENABLE ON PINS
#define GICR_INT0 6
#define GICR_INT1 7
#define GICR_INT2 5

#define SREG_I 7

#define INTERRUPT_PIN_0 0
#define INTERRUPT_PIN_1 1
#define INTERRUPT_PIN_2 2

//P.S INT2 has only 2 modes rise and fall
// NO MOOD_LOGIC for INT2

#define MOOD_FALL 0
#define MOOD_RISE 1
#define MOOD_LOGIC 2

void INTERRUPT_INIT(u8 INTERRUPT_PIN_X , u8 MOOD_X);
void  INTERRUPT_GIE_DISABLE();
void  INTERRUPT_GIE_ENABLE();

#define ISR(INT_VECT)void INT_VECT(void)  __attribute__((signal,used));\
void INT_VECT(void)

#endif /* INTERRUPT_H_ */
