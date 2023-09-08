/*
 * LCD.c
 *
 *  Created on: Aug 15, 2023
 *      Author: Manwil
 */

#include "DIO.h"
#include "STD_TYPES.h"
#include "LCD.h"
#include "avr/delay.h"


void intToString(int num, char str[]) {
	int index = 0;

	if (num == 0) {
		str[index++] = '0';
	} else {
		while (num > 0) {
			str[index++] = num % 10 + '0';
			num /= 10;
		}
	}

	str[index] = '\0';

	// Reverse the string
	for (int i = 0, j = index - 1; i < j; i++, j--) {
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}


void LCD_WRITE_COMMAND(u8 Data)
{
	DIO_u8_WRITE_PIN(CONTROL_PORT, RS , 0);
	DIO_u8_WRITE_PIN(CONTROL_PORT, RW , 0);

	DIO_u8_WRITE_PORT(DATA_PORT, Data);


	DIO_u8_WRITE_PIN(CONTROL_PORT, E , 1);
	_delay_ms(1);
	DIO_u8_WRITE_PIN(CONTROL_PORT, E , 0);
}

void LCD_CLEAR(){
	LCD_WRITE_COMMAND(0b00000001);
	_delay_ms(2);
}

void LCD_INIT()
{

	DIO_u8_SET_PIN(CONTROL_PORT , RS, OUTPUT);
	DIO_u8_SET_PIN(CONTROL_PORT , RW, OUTPUT);
	DIO_u8_SET_PIN(CONTROL_PORT , E , OUTPUT);

	DIO_u8_SET_PORT(DATA_PORT, PORT_OUTPUT);

	//function set
	LCD_WRITE_COMMAND(0b00111000);
	_delay_ms(1);


	//on-off control
	LCD_WRITE_COMMAND(0b00001110);
	_delay_ms(1);

	LCD_CLEAR();

	//entry mood
	LCD_WRITE_COMMAND(0b00000110);
}

void LCD_WRITE_CHAR(u8 Data)
{
	DIO_u8_WRITE_PIN(CONTROL_PORT, RS , 1);
	DIO_u8_WRITE_PIN(CONTROL_PORT, RW , 0);

	DIO_u8_WRITE_PORT(DATA_PORT, Data);


	DIO_u8_WRITE_PIN(CONTROL_PORT, E , 1);
	_delay_ms(1);
	DIO_u8_WRITE_PIN(CONTROL_PORT, E , 0);
}

void LCD_WRITE_STRING(u8 * Str)
{
	for(u8 i=0 ; Str[i] != '\0'; i++)
	{
		LCD_WRITE_CHAR(Str[i]);
	}
}

// setting position of display cursor in DDRAM
void LCD_GOTO(u8 x, u8 y)
{
	LCD_WRITE_COMMAND(128+ y*0x40 + x);
}

void LCD_SHIFT(u8 Direction)
{

	switch(Direction){
	case LEFT:
		LCD_WRITE_COMMAND(0b00011000);
		break;
	case RIGHT:
		LCD_WRITE_COMMAND(0b00011100);
		break;
	}

}

void LCD_WRITE_INT(u16 integer){
	u8 arr[8];
	intToString(integer, arr);
	LCD_WRITE_STRING(arr);
}
