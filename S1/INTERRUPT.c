/*
 * INTERRUPT.c
 *
 *  Created on: Aug 20, 2023
 *      Author: Manwil
 */

#include "INTERRUPT_REGISTER.h"
#include "INTERRUPT.h"
#include "BIT_MATH.h"

// MCUCR & MCUCSR - controls the type of trigger - rising edge , falling edge etc...

void INTERRUPT_GIE_ENABLE()
{
	SET_BIT(SREG,SREG_I);
}

void  INTERRUPT_GIE_DISABLE()
{
	CLEAR_BIT(SREG,SREG_I);
}

void INTERRUPT_INIT(u8 INTERRUPT_PIN_X , u8 MOOD_X)
{
	switch(INTERRUPT_PIN_X){

	case INTERRUPT_PIN_0:
		switch(MOOD_X){
		case MOOD_FALL:
			// set sense control for Int0 to falling edge
			SET_BIT(MCUCR , ISC01);
			CLEAR_BIT(MCUCR , ISC00);
			break;
		case MOOD_RISE:
			// set sense control for Int0 to Rising edge
			SET_BIT(MCUCR , ISC01);
			SET_BIT(MCUCR , ISC00);
			break;
		case MOOD_LOGIC:
			// set sense control for Int0 to Logical Change
			CLEAR_BIT(MCUCR , ISC01);
			SET_BIT(MCUCR , ISC00);
			break;
		}
		SET_BIT(GICR, GICR_INT0);
		break;

		case INTERRUPT_PIN_1:
			switch(MOOD_X){
			case MOOD_FALL:
				// set sense control for Int0 to falling edge
				SET_BIT(MCUCR , ISC11);
				CLEAR_BIT(MCUCR , ISC10);
				break;
			case MOOD_RISE:
				// set sense control for Int0 to Rising edge
				SET_BIT(MCUCR , ISC11);
				SET_BIT(MCUCR , ISC10);
				break;
			case MOOD_LOGIC:
				// set sense control for Int0 to Logical Change
				CLEAR_BIT(MCUCR , ISC11);
				SET_BIT(MCUCR , ISC10);
				break;
			}
			SET_BIT(GICR, GICR_INT1);
			break;

			case INTERRUPT_PIN_2:
				switch(MOOD_X){
				case MOOD_FALL:
					CLEAR_BIT(MCUCSR,ISC2);
					break;
				case MOOD_RISE:
					SET_BIT(MCUCSR,ISC2);
					break;
				}
				SET_BIT(GICR, GICR_INT2);
				break;
	}
}
