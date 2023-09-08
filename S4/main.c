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

#define SLAVE_ID SLAVE3

u8 req;
u8 id;
u8 command;

void main(){
	//SLAVE 2
	UART_INIT();

	DIO_u8_SET_PIN(PORTB , PIN3 , OUTPUT);

	TIMER_0_SET_COMPARE(0);
	TIMER_0_INIT(F_PWM_0 , PRE_8);


	while(1){

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
			default:
				UART_RECIEVE_DATA();
				break;
			}
		}else{
			UART_RECIEVE_DATA();
		}
	}
}
