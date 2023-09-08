/*
 * TIMER.h
 *
 *  Created on: Aug 23, 2023
 *      Author: Manwil
 */

#ifndef TIMER_H_
#define TIMER_H_

//choose prescaler
//P.S. prescaler = 4 * binary

#define PRE_1    0b00000001
#define PRE_8    0b00000010
#define PRE_64   0b00000011
#define PRE_256  0b00000100
#define PRE_1024 0b00000101

//modes for timer0
#define NORMAL_0 0b00000000 //overflow
#define CTC_0    0b00001000 //compare
#define F_PWM_0  0b01001000 //fast pwm
#define P_PWM_0  0b00001000 //phase Correct PWM

//edges
#define RISE 0
#define FALL 1

//modes for timer 1

#define NORMAL_1 0
#define F_PWM_1  1

#define CHANNEL_A 0
#define CHANNEL_B 1
#define NULL      2

void TIMER_0_INIT(u8 mood , u8 prescaler);
void TIMER_0_SET_INIT(u8 initial_time);
void TIMER_0_SET_COMPARE(u8 compare_time);
u8 TIMER_0_GET_TCNT();

void TIMER_1_INIT(u8 ,u8 , u8 );
void TIMER_1_SET_COMPARE(u8 channel,u16 compare_value);
void TIMER_1_SET_ICR(u16 icr_value);
u16 TIMER_1_GET_ICR();
void TIMER_1_SET_TIMER(u16 timer);
void TIMER_1_SET_INT_EDGE(u8 edge);


#endif /* TIMER_H_ */
