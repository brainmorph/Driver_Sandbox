/*
 * dc_spi_driver.h
 *
 *  Created on: Nov 30, 2020
 *      Author: DC
 */

#ifndef DC_SPI_DRIVER_H_
#define DC_SPI_DRIVER_H_

/**********************************************************************
*     Include Files
**********************************************************************/
#include <stdint.h>
#include "stm32f407xx.h"

/**********************************************************************
* Global Macro Definitions
**********************************************************************/
#ifdef UNIT_TEST
#define unit_static
#else
#define unit_static static
#endif

/**********************************************************************
* Global Type Definitions
**********************************************************************/

// Lifted from stm32f407xx.h
typedef struct
{
  __IO uint32_t CR1;        /*!< SPI control register 1 (not used in I2S mode),      Address offset: 0x00 */
  __IO uint32_t CR2;        /*!< SPI control register 2,                             Address offset: 0x04 */
  __IO uint32_t SR;         /*!< SPI status register,                                Address offset: 0x08 */
  __IO uint32_t DR;         /*!< SPI data register,                                  Address offset: 0x0C */
  __IO uint32_t CRCPR;      /*!< SPI CRC polynomial register (not used in I2S mode), Address offset: 0x10 */
  __IO uint32_t RXCRCR;     /*!< SPI RX CRC register (not used in I2S mode),         Address offset: 0x14 */
  __IO uint32_t TXCRCR;     /*!< SPI TX CRC register (not used in I2S mode),         Address offset: 0x18 */
  __IO uint32_t I2SCFGR;    /*!< SPI_I2S configuration register,                     Address offset: 0x1C */
  __IO uint32_t I2SPR;      /*!< SPI_I2S prescaler register,                         Address offset: 0x20 */
} DSD_SPI_TypeDef;


typedef struct
{
	volatile uint32_t* clock; /* Pointer to register that enables this SPI clock */
	DSD_SPI_TypeDef* registers; /* Pointer to struct of all registers for SPI interface */
}DSD_SPI_t;



/***************************************************************************************************
* Global Function Declarations
***************************************************************************************************/
void DSD_SetBit(volatile uint32_t *address, uint8_t bit);
void DSD_ClearBit(volatile uint32_t *address, uint8_t bit);

void DSD_InitSPI();

void DSD_SendTestSPI();

uint8_t DSD_SendBytes(uint8_t* txBuffer, uint8_t* rxBuffer, uint8_t size);
uint8_t DSD_ReadByte();


#endif /* DC_SPI_DRIVER_H_ */
