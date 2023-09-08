/*
 * main.c
 *
 *  Created on: Sep 3, 2023
 *      Author: Manwil
 */

#include "DIO.h"
#include "UART.h"
#include "LCD.h"
#include "INTERRUPT.h"
#include "ADC.h"
#include "CONTROLS.h"

#include <avr/delay.h>
#include "STD_TYPES.h"

u8 m0 = 0;
u8 m1 = 0;
u8 m2 = 0;
u8 m3 = 0;

u8 last_m0=10;
u8 last_m1=10;
u8 last_m2=10;
u8 last_m3=10;

void motor_control(u8 slave , u8 speed){
	UART_SEND_DATA(slave | MOTOR);
	UART_SEND_DATA(speed);
}

u8 check_num_add(u8 speed, u8 number) {
	if (speed > (255 - number)) {

		// 240 > 255 - 20
		// 240 > 235

		return 255;
	} else {
		return speed + number;
	}
}

u8 check_num_sub(u8 speed, u8 number) {
	if (speed < number) {
		return 0;
	} else {
		return speed - number;
	}
}

void mov_hor(u16 value){

	if(value > (1024.0/2.0 + 70)){ // 140 neutral zone |...(+ve)...|...70...0...70...|...(-ve)...|
		//move left
		//if value greate than half by little ... make change to speed by little

		// - +
		// - +

		u8 correction_factor = ((value-512) / 512.0)*20;

		m0 = check_num_sub(m0,correction_factor);

		m1 = check_num_add(m1,correction_factor);

		m2 = check_num_sub(m2,correction_factor);

		m3 = check_num_add(m3,correction_factor);


	}else if(value < (1024.0/2.0 - 50)){ // move right
		// + -
		// + -
		u8 correction_factor = ((512-value) / 512.0)*20;
		m0 = check_num_add(m0,correction_factor);
		m1 = check_num_sub(m1,correction_factor);
		m2 = check_num_add(m2,correction_factor);
		m3 = check_num_sub(m3,correction_factor);
	}
	_delay_ms(20);
}

void mov_ver(u16 value){
	if(value > (1024.0/2.0 + 70)){
		// 140 neutral zone |...(+ve)...|...70...0...70...|...(-ve)...|
		//move front
		//if value greate than half by little ... make change to speed by little


		// - -
		// + +
		u8 correction_factor = ((value-512) / 512.0)*20;
		m0 = check_num_sub(m0,correction_factor);
		m1 = check_num_sub(m1,correction_factor);
		m2 = check_num_add(m2,correction_factor);
		m3 = check_num_add(m3,correction_factor);

	}else if(value < (1024.0/2.0 - 50)){
		// move back

		// + +
		// - -
		u8 correction_factor = ((512-value) / 512.0)*20;
		m0 = check_num_add(m0,correction_factor);
		m1 = check_num_add(m1,correction_factor);
		m2 = check_num_sub(m2,correction_factor);
		m3 = check_num_sub(m3,correction_factor);
	}
	_delay_ms(20);
}

void main(){
	// MASTER
	DIO_u8_SET_PIN(PORTB , PIN0 , OUTPUT);
	DIO_u8_WRITE_PIN(PORTB , PIN0, HIGH);
	DIO_u8_SET_PIN(PORTB , PIN1 , OUTPUT);

	LCD_INIT();
	UART_INIT();
	ADC_INIT();

	INTERRUPT_INIT(INTERRUPT_PIN_0 , MOOD_FALL);
	DIO_u8_SET_PIN(PORTD , PIN2 , INPUT);
	DIO_u8_WRITE_PIN(PORTD , PIN2, HIGH);

	INTERRUPT_INIT(INTERRUPT_PIN_1 , MOOD_FALL);

	DIO_u8_SET_PIN(PORTD , PIN3 , INPUT);
	DIO_u8_WRITE_PIN(PORTD , PIN3, HIGH);

	DIO_u8_WRITE_PIN(PORTB , PIN0, LOW);
	DIO_u8_WRITE_PIN(PORTB , PIN1, HIGH);

	u16 hor;
	u16 ver;

	while(1){

		hor = (u16)ADC_u16_READ(ADC0);
		ver = (u16)ADC_u16_READ(ADC1);

		mov_hor(hor);
		mov_ver(ver);

		if((last_m0 != m0) |(last_m1 != m1 )|(last_m2 != m2) |(last_m3 != m3) ){
			motor_control(SLAVE0 , m0);
			motor_control(SLAVE1 , m1);
			motor_control(SLAVE2 , m2);
			motor_control(SLAVE3 , m3);

			/******* MODIFY LCD *******/
			LCD_CLEAR();

			LCD_WRITE_STRING("M0 :");
			LCD_WRITE_INT(m0);
			LCD_WRITE_STRING(" |M1 :");
			LCD_WRITE_INT(m1);

			LCD_GOTO(0,1);

			LCD_WRITE_STRING("M2 :");
			LCD_WRITE_INT(m2);
			LCD_WRITE_STRING(" |M3 :");
			LCD_WRITE_INT(m3);

			last_m0 =m0;
			last_m1 =m1;
			last_m2 =m2;
			last_m3 =m3;
		}

	}
}

ISR(INT0){

	    DIO_u8_WRITE_PIN(PORTB , PIN1, LOW);
	    DIO_u8_WRITE_PIN(PORTB , PIN0, HIGH);
	    LCD_CLEAR();
	    LCD_WRITE_STRING("ASCENDING ...");

	    m0 = check_num_add(m0,20);
	    m1 = check_num_add(m1,20);
	    m2 = check_num_add(m2,20);
	    m3 = check_num_add(m3,20);

	    _delay_ms(20);

	    DIO_u8_WRITE_PIN(PORTB , PIN0, LOW);
	    DIO_u8_WRITE_PIN(PORTB , PIN1, HIGH);

}


ISR(INT1){
	//land
	DIO_u8_WRITE_PIN(PORTB , PIN1, LOW);
	DIO_u8_WRITE_PIN(PORTB , PIN0, HIGH);

	LCD_CLEAR();
	LCD_WRITE_STRING("DESCENDING ...");

	m0 = check_num_sub(m0,20);
	m1 = check_num_sub(m1,20);
	m2 = check_num_sub(m2,20);
	m3 = check_num_sub(m3,20);

	_delay_ms(20);

	DIO_u8_WRITE_PIN(PORTB , PIN0, LOW);
	DIO_u8_WRITE_PIN(PORTB , PIN1, HIGH);

}
