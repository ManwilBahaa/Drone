#ifndef _DIO_REGISTER_H
#define _DIO_REGISTER_H

//Group Port A
#define PORTA_REGISTER *((volatile u8 * )0x3B)
#define DDRA_REGISTER *((volatile u8 * )0x3A)
#define PINA_REGISTER *((volatile u8 * )0x39)

//Group Port B
#define PORTB_REGISTER *((volatile u8 * )0x38)
#define DDRB_REGISTER *((volatile u8 * )0x37)
#define PINB_REGISTER *((volatile u8 * )0x36)

//Group Port C
#define PORTC_REGISTER *((volatile u8 * )0x35)
#define DDRC_REGISTER *((volatile u8 * )0x34)
#define PINC_REGISTER *((volatile u8 * )0x33)

//Group Port D
#define PORTD_REGISTER *((volatile u8 * )0x32)
#define DDRD_REGISTER *((volatile u8 * )0x31)
#define PIND_REGISTER *((volatile u8 * )0x30)

#endif