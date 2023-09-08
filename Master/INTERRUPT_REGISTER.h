/*
 * INTERRUPT_REGISTER.h
 *
 *  Created on: Aug 20, 2023
 *      Author: Manwil
 */

#ifndef INTERRUPT_REGISTER_H_
#define INTERRUPT_REGISTER_H_

#include "STD_TYPES.h"

#define MCUCR *((volatile u8*) 0x55)
#define MCUCSR *((volatile u8*) 0x54)
#define GICR *((volatile u8*) 0x5B)
#define SREG *((volatile u8*) 0x5F)

#endif /* INTERRUPT_REGISTER_H_ */
