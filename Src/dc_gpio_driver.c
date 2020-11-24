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



/***************************************************************************************************
*      Global Function Definitions
***************************************************************************************************/
void DGD_SetBit(uint32_t *address, uint8_t bit)
{
	*address |= (1 << bit);
}

void DGD_ClearBit(uint32_t *address, uint8_t bit)
{
	uint32_t temp = 0;
	temp |= (1 << bit);
	*address &= ~temp;
}

void DGD_Initialize(uint32_t *regAddr, DGD_GPIO_Port_e port)
{
	switch(port)
	{
	case PORTA:
		// Turn on clock to PORTA
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOAEN_BIT);
		break;

	case PORTB:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOBEN_BIT);
		break;

	case PORTC:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOCEN_BIT);
		break;

	case PORTD:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIODEN_BIT);
		break;

	case PORTE:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOEEN_BIT);
		break;

	case PORTF:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOFEN_BIT);
		break;

	case PORTG:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOGEN_BIT);
		break;

	case PORTH:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOHEN_BIT);
		break;

	case PORTI:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOIEN_BIT);
		break;

	case PORTJ:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOJEN_BIT);
		break;

	case PORTK:
		DGD_SetBit(regAddr, DGD_RCC_AHB1ENR_GPIOKEN_BIT);
		break;

	default:
		break;
	}

}


void DGD_Write_GPIO_Pin(GPIO_TypeDef *port, uint8_t pin, uint8_t level)
{
	uint8_t registerFieldPosition = pin * 2; // MODER has 2 bits per field for each pin
	port->MODER |= (level << registerFieldPosition);
}
