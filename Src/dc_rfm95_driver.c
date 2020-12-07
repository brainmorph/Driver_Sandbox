/*
 * dc_rfm95_driver.c
 *
 *  Created on: Dec 6, 2020
 *      Author: DC
 */

#include "dc_rfm95_driver.h"
#include "dc_spi_driver.h"

uint8_t DRD_ReadRegister(uint8_t regAddress)
{
	regAddress &= 0x7F; // make sure it's read only (7th bit = 0)

	uint8_t txBuffer[2] = {regAddress, 0xa5};
	uint8_t rxBuffer[2];
	DSD_SendBytes(txBuffer, rxBuffer, 2);

	return rxBuffer[1]; // return last byte received
}
