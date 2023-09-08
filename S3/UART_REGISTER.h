/*
 * UART_REGISTER.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Manwil
 */

#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_

#include "STD_TYPES.h"

//UDR -> 8
#define UDR *((volatile u8*) 0x2C)

#define UCSRA *((volatile u8*) 0x2B)
#define UCSRB *((volatile u8*) 0x2A)
#define UCSRC *((volatile u8*) 0x40)

#define UBRRL *((volatile u8*) 0x29)
#define UBRRH *((volatile u8*) 0x40)

#endif /* UART_REGISTER_H_ */
