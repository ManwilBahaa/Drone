/*
 * LCD.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Manwil
 */

#ifndef LCD_H_
#define LCD_H_

#include"DIO.h"
#include "STD_TYPES.h"

#define DATA_PORT PORTC
#define CONTROL_PORT PORTD

#define RS PIN5
#define RW PIN6
#define E  PIN7

#define LEFT 0
#define RIGHT 1

void LCD_INIT();
void LCD_CLEAR();
void LCD_WRITE_COMMAND(u8 Data);
void LCD_WRITE_INT(u16 integer);

//write a character to screen
void LCD_WRITE_CHAR(u8 Data);
//write string to screen
void LCD_WRITE_STRING(u8 * String);

//Change position of cursor to the x & y position
void LCD_GOTO(u8 x_position, u8 y_position);
// Shift entire screen
void LCD_SHIFT(u8 Direction);

#endif /* LCD_H_ */
