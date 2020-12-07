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

	uint8_t txBuffer[2] = {regAddress, 0xa5}; // send register address in read mode along with dummy byte
	uint8_t rxBuffer[2];
	DSD_SendBytes(txBuffer, rxBuffer, 2);

	return rxBuffer[1]; // return last byte received
}


void DRD_SetModeIdle()
{
	uint8_t regAddress = DRD_RFM95_REG_01_OP_MODE;
	regAddress |= 0x80; // make sure it's a write command (7th bit = 1)

	/* Get previous DRD_RFM95_REG_01_OP_MODE bits */
	uint8_t previous = DRD_ReadRegister(DRD_RFM95_REG_01_OP_MODE);
	previous &= 0xF8; // clear bits in Mode field
	previous |= 0x01; // set STDBY mode

	uint8_t txBuffer[2] = {regAddress, previous};
	uint8_t rxBuffer[2];
	DSD_SendBytes(txBuffer, rxBuffer, 2);
}

void DRD_SetModeSleep()
{
	uint8_t regAddress = DRD_RFM95_REG_01_OP_MODE;
	regAddress |= 0x80; // make sure it's a write command (7th bit = 1)

	/* Get previous DRD_RFM95_REG_01_OP_MODE bits */
	uint8_t previous = DRD_ReadRegister(DRD_RFM95_REG_01_OP_MODE);
	previous &= 0xF8; // clear bits in Mode field
	previous |= 0x00; // set SLEEP mode

	uint8_t txBuffer[2] = {regAddress, previous};
	uint8_t rxBuffer[2];
	DSD_SendBytes(txBuffer, rxBuffer, 2);
}
