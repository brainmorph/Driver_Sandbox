/*
 * dc_gpio_driver.c
 *
 *  Created on: Nov 22, 2020
 *      Author: DC
 */


#include "dc_gpio_driver.h"
#include "stm32f407xx.h"

void DGD_Initialize(uint32_t *regAddr)
{
	// Turn on RCC.  But write test function first.
	*regAddr |= 1;
}

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
