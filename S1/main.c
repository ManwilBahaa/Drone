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

#define SLAVE_ID SLAVE0

u8 req;
u8 id;
u8 command;
u8 tem_reading;

void main(){
	//SLAVE 0
	UART_INIT();
	ADC_INIT();
	DIO_u8_SET_PIN(PORTB , PIN3 , OUTPUT);
	DIO_u8_SET_PORT(PORTC, PORT_OUTPUT);

	TIMER_0_SET_COMPARE(0);
	TIMER_0_INIT(F_PWM_0 , PRE_8);

	while(1){
		tem_reading= (u8)(((ADC_u16_READ(ADC0)/1023.0)*5.0)*100.0);
		DIO_u8_WRITE_PORT(PORTC ,  tem_reading);

		req = UART_RECIEVE_DATA();
		id = req & 0b11000000;
		command = req & 0b00111111;

		if(id == SLAVE_ID){
			switch(command)
			{
			case MOTOR:
			{
				u8 data= UART_RECIEVE_DATA();

			TIMER_0_SET_COMPARE(data);

				break;
			}
			case TEM:
			{
//				tem_reading= (u8)(((ADC_u16_READ(ADC0)/1023.0)*5.0)*100.0);
//				DIO_u8_WRITE_PORT(PORTC ,  tem_reading);
//				UART_SEND_DATA( tem_reading);
				break;
			}
			default:
				//do nothing with the data that comes next
				UART_RECIEVE_DATA();
				break;
			}
		}else{
			//do nothing with the data that comes next
			UART_RECIEVE_DATA();
		}


	}
}
