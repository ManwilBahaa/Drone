
/*
 * main.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Abanob
 */

#include "DIO.h"
#include "UART.h"
#include "STD_TYPES.h"
#include "TIMER.h"
#include "CONTROLS.h"
#include "STD_TYPES.h"
#include "ADC.h"

#define SLAVE_ID SLAVE1

u8 req;
u8 id;
u8 command;

void main(){
	//SLAVE 1
	UART_INIT();
	ADC_INIT();
	DIO_u8_SET_PIN(PORTB , PIN3 , OUTPUT);
	DIO_u8_SET_PORT(PORTC, PORT_OUTPUT);

	TIMER_0_SET_COMPARE(0);
	TIMER_0_INIT(F_PWM_0 , PRE_8);

	while(1){

		req = UART_RECIEVE_DATA();
		id = req & 0b11000000;
		command = req & 0b00111111;

		u8 pres_reading = (u8)(((ADC_u16_READ(ADC0)/1023.0)*255.0));
		DIO_u8_WRITE_PORT(PORTC ,  pres_reading);


		if(id == SLAVE_ID){


			switch(command)
			{
			case MOTOR:
			{
				u8 data= UART_RECIEVE_DATA();

				TIMER_0_SET_COMPARE(data);

				break;
			}
			case PRESSURE:
			{

				break;
			}
			default:
				UART_RECIEVE_DATA();
				break;
			}
		}else{
			UART_RECIEVE_DATA();

//			u8 pres_reading = (u8)(((ADC_u16_READ(ADC0)/1024.0)*255.0));
//			DIO_u8_WRITE_PORT(PORTC ,  pres_reading);
		}

	}
}
