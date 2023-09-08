/*
 * UART.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Manwil
 */

#include "BIT_MATH.h"
#include "UART_REGISTER.h"
#include "UART.h"

void UART_INIT(){
	// enable send and recieve
	SET_BIT(UCSRB, RXEN);
	SET_BIT(UCSRB, TXEN);

	//set data bit size to 8 bit

	SET_BIT(UCSRC, 7);

	CLEAR_BIT(UCSRB, UCSZ2);
	SET_BIT(UCSRC, UCSZ1);
	SET_BIT(UCSRC, UCSZ0);

	//set baud rate to 9600 at 8 mhz
	UBRRL = 51;
}



void UART_SEND_DATA(u8 data){
	//udre=1 --> buffer empty
	while(GET_BIT(UCSRA, UDRE)==0){}
	UDR=data;
}

u8 UART_RECIEVE_DATA(){
	while(GET_BIT(UCSRA, RXC)==0){}
	return UDR;
}
