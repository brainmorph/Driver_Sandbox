/*
 * dc_gpio_driver.c
 *
 *  Created on: Nov 22, 2020
 *      Author: DC
 */

/**********************************************************************
*     Include Files
**********************************************************************/
#include "dc_gpio_driver.h"
#include <stddef.h>


/***************************************************************************************************
*     Local Type Definitions
***************************************************************************************************/
typedef struct
{
//	GPIO_TypeDef* GPIOA;
//	GPIO_TypeDef* GPIOB;
}DGD_GPIO_t;



/***************************************************************************************************
*     Static Variable Definitions
***************************************************************************************************/
static DGD_GPIO_Port_t activeGPIOhandle;



/***************************************************************************************************
*     Static Function Declarations
***************************************************************************************************/
unit_static int DGD_Select_Port_BaseAddress(DGD_GPIO_Port_t* activeGPIOhandle, DGD_Port_enum port);


/***************************************************************************************************
*      Global Function Definitions
***************************************************************************************************/
void DGD_SetBit(volatile uint32_t *address, uint8_t bit)
{
	*address |= (1 << bit);
}

void DGD_ClearBit(volatile uint32_t *address, uint8_t bit)
{
	uint32_t temp = 0;
	temp |= (1 << bit);
	*address &= ~temp;
}

void DGD_InitPort(DGD_Port_enum port)
{
#ifndef UNIT_TEST
	// If unit testing, don't change the RCC GPIO clock enable address
	// We don't want unit test (which runs on host pc) to modify memory outside the virtual GPIO port
	activeGPIOhandle.portClock = &RCC->AHB1ENR;
#endif

	switch(port)
	{
	case PORTA:
		DGD_SetBit(activeGPIOhandle.portClock, 0);
		break;
	case PORTB:
		DGD_SetBit(activeGPIOhandle.portClock, 1);
		break;
	default:
		break;
	}
}


void DGD_SetPinDirection(DGD_Port_enum port, uint8_t pin, DGD_Pin_Mode_enum mode)
{
#ifndef UNIT_TEST
	// We don't want unit test (which runs on host pc) to modify memory outside the virtual GPIO port.
	// Select appropriate GPIO Port base address
	DGD_Select_Port_BaseAddress(&activeGPIOhandle, port);
#endif

	if(mode == OUTPUT)
	{
		// Set MODER bits to output mode
		DGD_SetBit(&(activeGPIOhandle.portRegisters->MODER), 0);
		DGD_ClearBit(&(activeGPIOhandle.portRegisters->MODER), 1);
	}
	else if(mode == INPUT)
	{
		// Set MODER bits to input mode
		DGD_ClearBit(&(activeGPIOhandle.portRegisters->MODER), 0);
		DGD_ClearBit(&(activeGPIOhandle.portRegisters->MODER), 1);
	}
}


void DGD_WritePin(DGD_Port_enum port, uint8_t pin, DGD_Pin_Level_enum level)
{
#ifndef UNIT_TEST
	// We don't want unit test (which runs on host pc) to modify memory outside the virtual GPIO port.
	// Select appropriate GPIO Port base address
	DGD_Select_Port_BaseAddress(&activeGPIOhandle, port);
#endif

	// Set pin level
	if(level == HIGH)
	{
		DGD_SetBit(&activeGPIOhandle.portRegisters->BSRR, pin);
	}
	else
	{
		DGD_SetBit(&activeGPIOhandle.portRegisters->BSRR, pin + 16);
	}
}

uint8_t DGD_ReadPin(DGD_Port_enum port, uint8_t pin)
{
#ifndef UNIT_TEST
	// We don't want unit test (which runs on host pc) to modify memory outside the virtual GPIO port.
	// Select appropriate GPIO Port base address
	DGD_Select_Port_BaseAddress(&activeGPIOhandle, port);
#endif

	uint8_t value = (activeGPIOhandle.portRegisters->IDR >> pin) & 0x1;

	return value;
}

/*
 * Use enum as a way to set base address of the GPIO port inside the GPIO handle
 */
unit_static int DGD_Select_Port_BaseAddress(DGD_GPIO_Port_t* activeGPIOhandle, DGD_Port_enum port)
{
	switch(port)
	{
	case PORTA:
		activeGPIOhandle->portRegisters = (DGD_GPIO_TypeDef*)GPIOA;
		break;
	case PORTB:
		activeGPIOhandle->portRegisters = (DGD_GPIO_TypeDef*)GPIOB;
		break;
	case PORTC:
		activeGPIOhandle->portRegisters = (DGD_GPIO_TypeDef*)GPIOC;
		break;
	case PORTD:
		activeGPIOhandle->portRegisters = (DGD_GPIO_TypeDef*)GPIOD;
		break;
	case PORTE:
		activeGPIOhandle->portRegisters = (DGD_GPIO_TypeDef*)GPIOE;
		break;
	case PORTF:
		activeGPIOhandle->portRegisters = (DGD_GPIO_TypeDef*)GPIOF;
		break;
	case PORTG:
		activeGPIOhandle->portRegisters = (DGD_GPIO_TypeDef*)GPIOG;
		break;
	case PORTH:
		activeGPIOhandle->portRegisters = (DGD_GPIO_TypeDef*)GPIOH;
		break;
	case PORTI:
		activeGPIOhandle->portRegisters = (DGD_GPIO_TypeDef*)GPIOI;
		break;

	default:
		return -1;
	}

	return 0;
}


#ifdef UNIT_TEST
/***************************************************************************************************
*      Functions in this section are only to be used for unit testing internal functionality of module
*      !DO NOT USE IN PRODUCTION CODE!
***************************************************************************************************/

/* Allow activeGPIOhandle to be changed by outside world */
unit_static void UT_SetActiveGPIOhandle(DGD_GPIO_Port_t* newHandle)
{
	activeGPIOhandle = *newHandle;
}

/* Expose activeGPIOhandle to outside world */
unit_static DGD_GPIO_Port_t* UT_GetActiveGPIOhandle()
{
	return &activeGPIOhandle;
}
/***************************************************************************************************
****************************************************************************************************/
#endif






/* --- Everything below this line is sandbox --- */

//void DGD_Initialize_OBSOLETE(uint32_t *regAddr, DGD_GPIO_Port_e port)
//{
//	// a better way to do it is to pass in GPIO_TypeDef *port as an argument
//	// and let the direct address pointing handle which port is being used a.k.a
//	// port->
//	switch(port)
//	{
//	case PORTA:
//		// Turn on clock to PORTA
//		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOAEN_BIT);
//		break;
//
//	case PORTB:
//		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOBEN_BIT);
//		break;
//
//	case PORTC:
//		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOCEN_BIT);
//		break;
//
//	case PORTD:
//		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIODEN_BIT);
//		break;
//
//	case PORTE:
//		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOEEN_BIT);
//		break;
//
//	case PORTF:
//		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOFEN_BIT);
//		break;
//
//	case PORTG:
//		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOGEN_BIT);
//		break;
//
//	case PORTH:
//		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOHEN_BIT);
//		break;
//
//	case PORTI:
//		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOIEN_BIT);
//		break;
//
//	default:
//		break;
//	}
//
//}
//
//
//void DGD_Write_GPIO_Pin(GPIO_TypeDef *port, uint8_t pin, uint8_t level)
//{
//	uint8_t registerFieldPosition = pin * 2; // Each pin bit field is located 2 bits ahead of the one before
//	port->MODER |= (level << registerFieldPosition);
//}
