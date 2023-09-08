#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include "DIO_REGISTER.h"

u8 DIO_u8_SET_PIN(u8 Port , u8 Pin , u8 Direction)
{
	u8 Local_u8_error_state ;

	if ((Port >= PORTA && Port <= PORTD) && (Pin >= PIN0 && Pin <= PIN7) && (Direction == INPUT || Direction == OUTPUT))
	{
		Local_u8_error_state = OK;
		switch(Port){
		case PORTA:
			if(Direction == INPUT)
				CLEAR_BIT(DDRA_REGISTER, Pin);
			else if(Direction == OUTPUT)
				SET_BIT(DDRA_REGISTER, Pin);
			break;

		case PORTB:
			if(Direction == INPUT)
				CLEAR_BIT(DDRB_REGISTER, Pin);
			else if(Direction == OUTPUT)
				SET_BIT(DDRB_REGISTER, Pin);
			break;

		case PORTC:
			if(Direction == INPUT)
				CLEAR_BIT(DDRC_REGISTER, Pin);
			else if(Direction == OUTPUT)
				SET_BIT(DDRC_REGISTER, Pin);
			break;

		case PORTD:
			if(Direction == INPUT)
				CLEAR_BIT(DDRD_REGISTER, Pin);
			else if(Direction == OUTPUT)
				SET_BIT(DDRD_REGISTER, Pin);
			break;
		}
	}
	else{
		Local_u8_error_state = ERR;
	}

	return Local_u8_error_state;
}
u8 DIO_u8_SET_PORT(u8 Port , u8 Direction)
{
	u8 Local_u8_error_state = OK;
	if(Port > PORTD || Port < PORTA){
		Local_u8_error_state = ERR;
	}else{
		switch(Port)
		{
		case PORTA:
			DDRA_REGISTER= Direction;
			break;
		case PORTB:
			DDRB_REGISTER= Direction;
			break;
		case PORTC:
			DDRC_REGISTER= Direction;
			break;
		case PORTD:
			DDRD_REGISTER= Direction;
			break;
		}
	}
	return Local_u8_error_state;

}

u8 DIO_u8_WRITE_PIN(u8 Port , u8 Pin , u8 Value)
{
	u8 Local_u8_error_state = OK;
	if(Port > PORTD || Port < PORTA || Pin > PIN7 || Pin < PIN0 || (Value != HIGH && Value != LOW)){
		Local_u8_error_state = ERR;
	}
	else{

		switch(Port){
		case PORTA:
			if(Value == LOW)
				CLEAR_BIT(PORTA_REGISTER, Pin);
			else if(Value == HIGH)
				SET_BIT(PORTA_REGISTER, Pin);
			break;

		case PORTB:
			if(Value == LOW)
				CLEAR_BIT(PORTB_REGISTER, Pin);
			else if(Value == HIGH)
				SET_BIT(PORTB_REGISTER, Pin);
			break;

		case PORTC:
			if(Value == LOW)
				CLEAR_BIT(PORTC_REGISTER, Pin);
			else if(Value == HIGH)
				SET_BIT(PORTC_REGISTER, Pin);
			break;

		case PORTD:
			if(Value == LOW)
				CLEAR_BIT(PORTD_REGISTER, Pin);
			else if(Value == HIGH)
				SET_BIT(PORTD_REGISTER, Pin);
			break;
		}
	}

	return Local_u8_error_state;

}
u8 DIO_u8_WRITE_PORT(u8 Port , u8 Value)
{
	u8 Local_u8_error_state = OK;
	if(Port > PORTD || Port < PORTA)
	{
		Local_u8_error_state = ERR;
	}else{
		switch(Port){
		case PORTA:
			PORTA_REGISTER=Value;
			break;
		case PORTB:
			PORTB_REGISTER=Value;
			break;
		case PORTC:
			PORTC_REGISTER=Value;
			break;
		case PORTD:
			PORTD_REGISTER=Value;
			break;
		}
	}
	return Local_u8_error_state;
}

u8 DIO_u8_READ_PORT(u8 Port )
{
	if (Port >= PORTA && Port <= PORTD){
		u8 Value;
		switch(Port){
		case PORTA:
			Value = PINA_REGISTER;
			break;

		case PORTB:
			Value = PINB_REGISTER;
			break;

		case PORTC:
			Value = PINC_REGISTER;
			break;

		case PORTD:
			Value = PIND_REGISTER;
			break;
		}
		return Value;
	}else{
		u8 Local_u8_error_state=ERR;
		return Local_u8_error_state;
	}
}
u8 DIO_u8_READ_PIN(u8 Port , u8 Pin)
{
	u8 Local_u8_error_state =OK;

	if ((Port >= PORTA && Port <= PORTD) && (Pin >= PIN0 && Pin <= PIN7))
	{
		Local_u8_error_state = OK;
		u8 Value;
		switch(Port){
		case PORTA:
			Value= GET_BIT(PINA_REGISTER,Pin);
			break;

		case PORTB:
			Value= GET_BIT(PINB_REGISTER,Pin);
			break;

		case PORTC:
			Value= GET_BIT(PINC_REGISTER,Pin);
			break;

		case PORTD:
			Value= GET_BIT(PIND_REGISTER,Pin);
			break;
		}
		return Value;

	}else{
		Local_u8_error_state=ERR;
		return Local_u8_error_state;
	}
}

