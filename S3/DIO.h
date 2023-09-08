#ifndef _DIO_H
#define _DIO_H

// Port define


#include "STD_TYPES.h"

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define HIGH 1
#define LOW 0

#define OUTPUT 1
#define INPUT 0

#define PORT_OUTPUT 0xff
#define PORT_INPUT 0x00

#define PORT_HIGH 0xff
#define PORT_LOW 0x00

#define OK 1
#define ERR 0


u8 DIO_u8_SET_PIN(u8 Port , u8 Pin , u8 Direction);
u8 DIO_u8_SET_PORT(u8 Port , u8 Direction);


u8 DIO_u8_WRITE_PIN(u8 Port , u8 Pin , u8 Value);
u8 DIO_u8_WRITE_PORT(u8 Port , u8 Value);

u8 DIO_u8_READ_PORT(u8 Port);
u8 DIO_u8_READ_PIN(u8 Port , u8 Pin);


#endif
