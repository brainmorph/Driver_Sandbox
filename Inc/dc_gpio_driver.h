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
#if UNIT_TEST
#define unit_static
#else
#define unit_static static
#endif

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
	PORTI = 8
}DGD_Port_enum;

typedef enum
{
	LOW = 0,
	HIGH = 1
}DGD_Pin_Level_enum;



// Lifted from stm32f407xx.h
typedef struct
{
  __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
  __IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} DGD_GPIO_TypeDef;


typedef struct
{
	volatile uint32_t* portClock; /* Pointer to register that enables this GPIO port clock */
	DGD_GPIO_TypeDef* portRegisters; /* Pointer to struct of all registers for this GPIO port */
}DGD_GPIO_Port_t;



/***************************************************************************************************
* Global Function Declarations
***************************************************************************************************/
void DGD_SetBit(uint32_t *address, uint8_t bit);
void DGD_ClearBit(uint32_t *address, uint8_t bit);

void DGD_Initialize(uint32_t *regAddr, DGD_Port_enum port);
void DGD_Write_GPIO_Pin(DGD_Port_enum port, uint8_t pin, DGD_Pin_Level_enum level);


#endif /* DC_GPIO_DRIVER_H_ */
