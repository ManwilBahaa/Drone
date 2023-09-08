/*
 * UART.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Manwil
 */

#ifndef UART_H_
#define UART_H_

#define UDRE 5 //UCSRA - Buffer Ready to recieve new data

#define RXC 7

#define RXEN 4 //UCSRB - reciver enable
#define TXEN 3 //UCSRB - transmitter enable

#define UCSZ2 2 //UCSRB - character size
#define UCSZ1 2 //UCSRC
#define UCSZ0 1 //UCSRC

void UART_INIT();
void UART_SEND_DATA(u8 data);
u8 UART_RECIEVE_DATA();

#endif /* UART_H_ */
