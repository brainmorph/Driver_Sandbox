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
