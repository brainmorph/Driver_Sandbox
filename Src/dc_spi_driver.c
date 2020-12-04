/*
 * dc_spi_driver.c
 *
 *  Created on: Nov 30, 2020
 *      Author: DC
 */

/**********************************************************************
*     Include Files
**********************************************************************/
#include "dc_spi_driver.h"

#ifndef UNIT_TEST
#include "stm32f4xx_hal.h" // useful for HAL_Delay()
#endif

/***************************************************************************************************
*     Static Variable Definitions
***************************************************************************************************/
static DSD_SPI_t activeSPIhandle;

/***************************************************************************************************
*     Static Function Declarations
***************************************************************************************************/
static void DSD_WaitForTXE();


/***************************************************************************************************
*      Global Function Definitions
***************************************************************************************************/
inline void DSD_SetBit(volatile uint32_t* address, uint8_t bit)
{
	*address |= (1 << bit);
}

inline void DSD_ClearBit(volatile uint32_t* address, uint8_t bit)
{
	uint32_t temp = 0;
	temp |= (1 << bit);
	*address &= ~temp;
}

inline uint8_t DSD_GetBit(volatile uint32_t* address, uint8_t bit)
{
	uint8_t value = (*address >> bit) & 0x1;
	return value;
}


void DSD_InitSPI()
{
#ifndef UNIT_TEST
	// If unit testing, don't change the RCC SPI clock enable address
	// We don't want unit test (which runs on host pc) to modify memory outside the virtual GPIO port
	activeSPIhandle.clock = &RCC->APB2ENR;
	activeSPIhandle.registers = (DSD_SPI_TypeDef*)SPI1;
#endif

	// Enable clock for SPI interface
	DSD_SetBit(activeSPIhandle.clock, 12);

	// Set MASTER mode
	DSD_SetBit(&activeSPIhandle.registers->CR1, 2);

	// Set clock prescalar
	DSD_SetBit(&activeSPIhandle.registers->CR1, 3); // divide by 4

	// Set NSS to hardware output mode (seems necessary but not sure why)
	DSD_SetBit(&activeSPIhandle.registers->CR2, 2);

	// Enable SPI1
	DSD_SetBit(&activeSPIhandle.registers->CR1, 6);
}

static void DSD_WaitForTXE()
{
#ifndef UNIT_TEST
	while(!DSD_GetBit(&activeSPIhandle.registers->SR, 1))
	{
		// Do nothing
		asm("NOP");
	}
#endif
}

void DSD_SendTestSPI()
{
	// Send test byte
	activeSPIhandle.registers->DR = 0xA5;

#ifndef UNIT_TEST
	HAL_Delay(5);
#endif

	// Try to send a buffer of data.
	activeSPIhandle.registers->DR = 0x81;


	activeSPIhandle.registers->DR = 0x42;
	DSD_WaitForTXE();

	activeSPIhandle.registers->DR = 0x24;
	DSD_WaitForTXE();

	activeSPIhandle.registers->DR = 0x18;
	DSD_WaitForTXE();

	activeSPIhandle.registers->DR = 0x24;
	DSD_WaitForTXE();

	activeSPIhandle.registers->DR = 0x42;
	DSD_WaitForTXE();

	activeSPIhandle.registers->DR = 0x81;
}


uint8_t DSD_SendBytes(uint8_t* buffer, uint8_t size)
{
	uint8_t i = 0;

	while(i < size)
	{
		activeSPIhandle.registers->DR = buffer[i];
		DSD_WaitForTXE();

		i++;
	}

	return i; // export i as bytes written
}




#ifdef UNIT_TEST
/***************************************************************************************************
*      Functions in this section are only to be used for unit testing internal functionality of module
*      !DO NOT USE IN PRODUCTION CODE!
***************************************************************************************************/

/* Allow activeGPIOhandle to be changed by outside world */
unit_static void UT_SetActiveSPIhandle(DSD_SPI_t* newHandle)
{
	activeSPIhandle = *newHandle;
}

/* Expose activeGPIOhandle to outside world */
unit_static DSD_SPI_t* UT_GetActiveSPIhandle()
{
	return &activeSPIhandle;
}
/***************************************************************************************************
****************************************************************************************************/
#endif
