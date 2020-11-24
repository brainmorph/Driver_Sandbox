/*
 * dc_gpio_driver.h
 *
 *  Created on: Nov 22, 2020
 *      Author: DC
 */

#ifndef DC_GPIO_DRIVER_H_
#define DC_GPIO_DRIVER_H_

/**********************************************************************
*     Include Files
**********************************************************************/
#include <stdint.h>
#include "stm32f407xx.h"

/**********************************************************************
* Global Macro Definitions
**********************************************************************/
#define DGD_RCC_AHB1ENR_GPIOAEN_BIT 0
#define DGD_RCC_AHB1ENR_GPIOBEN_BIT 1
#define DGD_RCC_AHB1ENR_GPIOCEN_BIT 2
#define DGD_RCC_AHB1ENR_GPIODEN_BIT 3
#define DGD_RCC_AHB1ENR_GPIOEEN_BIT 4
#define DGD_RCC_AHB1ENR_GPIOFEN_BIT 5
#define DGD_RCC_AHB1ENR_GPIOGEN_BIT 6
#define DGD_RCC_AHB1ENR_GPIOHEN_BIT 7
#define DGD_RCC_AHB1ENR_GPIOIEN_BIT 8
#define DGD_RCC_AHB1ENR_GPIOJEN_BIT 9
#define DGD_RCC_AHB1ENR_GPIOKEN_BIT 10

/**********************************************************************
* Global Type Definitions
**********************************************************************/
typedef enum
{
	PORTA = 0,
	PORTB = 1,
	PORTC = 2,
	PORTD = 3,
	PORTE = 4,
	PORTF = 5,
	PORTG = 6,
	PORTH = 7,
	PORTI = 8,
	PORTJ = 9,
	PORTK = 10,
}DGD_GPIO_Port_e;

typedef enum
{
	INPUT = 0,
	OUTPUT = 1,
	INPUT_PD = 2,
	INPUT_PU = 3,
}DGD_GPIO_Pin_Mode_t;


/***************************************************************************************************
* Global Function Declarations
***************************************************************************************************/
void DGD_SetBit(uint32_t *address, uint8_t bit);
void DGD_ClearBit(uint32_t *address, uint8_t bit);

void DGD_Initialize(uint32_t *regAddr, DGD_GPIO_Port_e port);
void DGD_Write_GPIO_Pin(GPIO_TypeDef *port, uint8_t pin, uint8_t level);


#endif /* DC_GPIO_DRIVER_H_ */
