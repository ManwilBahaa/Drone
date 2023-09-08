/*
 * TIMER.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Manwil
 */

#include "STD_TYPES.h"
#include "TIMER.h"
#include "TIMER_REGISTER.h"
#include "BIT_MATH.h"



//timer 0
void TIMER_0_INIT(u8 mood , u8 prescaler)
{
	TCCR0 = 0b00000000 | mood  | prescaler;

	switch(mood){
	case NORMAL_0:
		SET_BIT(TIMSK,0);
		CLEAR_BIT(TIMSK,1);
		break;
	case CTC_0:
		CLEAR_BIT(TIMSK,0);
		SET_BIT(TIMSK,1);

		break;
	default:
		CLEAR_BIT(TIMSK,0);
		CLEAR_BIT(TIMSK,1);// turn off interrupt
		TCCR0 |= 0b0100000; // set pwm mood to clear on OC0 compare
		break;
	}
}
void TIMER_0_SET_INIT(u8 initial_time)
{
	TCNT0 = initial_time;
}
void TIMER_0_SET_COMPARE(u8 compare_time)
{
	OCR0 = compare_time;
}
u8 TIMER_0_GET_TCNT(){
	return TCNT0;
}

//timer 1

void TIMER_1_SET_INT_EDGE(u8 edge){
	switch(edge){
	case RISE:
		SET_BIT(TCCR1B,6);
		break;
	case  FALL:
		CLEAR_BIT(TCCR1B,6);
		break;
	}
}
void TIMER_1_INIT(u8 mood, u8 prescaler , u8 channel)
{
		switch(mood){
			case NORMAL_1:
				//common
				// wgm13-10 = 0000
				// cs12-10 = prescaler
				// TCCR1B is same for every case
				TCCR1B = 0b00000000 | prescaler;
				TIMER_1_SET_INT_EDGE(FALL);
				TCCR1A |= 0b00000000;

				SET_BIT(TIMSK, 2);
				CLEAR_BIT(TIMSK,3);
				CLEAR_BIT(TIMSK,4);
				SET_BIT(TIMSK, 5);
				break;

			case F_PWM_1:
				// disable interrupt if enabled
				CLEAR_BIT(TIMSK, 2);
				CLEAR_BIT(TIMSK,3);
				CLEAR_BIT(TIMSK,4);
				CLEAR_BIT(TIMSK, 5);

				TCCR1B = 0b00011000 | prescaler;
				//common
				// wgm13-10 = 1110

				switch(channel){
					case CHANNEL_A:
						TCCR1A = 0b10000000 | 0b00000010;
						break;
					case CHANNEL_B:
						TCCR1A = 0b00100000 | 0b00000010;
				}
				break;
			}
}

void TIMER_1_SET_COMPARE(u8 channel,u16 compare_value)
{
	switch(channel){
	case CHANNEL_A:
		OCR1A = compare_value;
		break;
	case CHANNEL_B:
		OCR1B= compare_value;
	}
}

void TIMER_1_SET_ICR(u16 icr_value)
{
	ICR1=icr_value;
}

u16 TIMER_1_GET_ICR(){
	return ICR1;
}

