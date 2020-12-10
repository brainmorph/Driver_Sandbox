/*
 * dc_rfm95_driver.c
 *
 *  Created on: Dec 6, 2020
 *      Author: DC
 */

/**********************************************************************
*     Include Files
**********************************************************************/
#include "dc_rfm95_driver.h"
#include "dc_spi_driver.h"



/***************************************************************************************************
*     Static Variable Definitions
***************************************************************************************************/
#ifdef UNIT_TEST
static TestHandle* th;
#endif

/***************************************************************************************************
*      Global Function Definitions
***************************************************************************************************/
unit_static uint8_t DRD_ReadRegister(uint8_t regAddress)
{
	regAddress &= 0x7F; // make sure it's a read cmd (7th bit = 0)

	uint8_t txBuffer[2] = {regAddress, 0xa5}; // send register address in read mode along with dummy byte
	uint8_t rxBuffer[2];

#ifdef UNIT_TEST
	th->virtualRegister = txBuffer[0];
#else
	DSD_SendBytes(txBuffer, rxBuffer, 2);
#endif

	return rxBuffer[1]; // return last byte received
}

unit_static void DRD_WriteRegister(uint8_t regAddress, uint8_t data)
{
	regAddress |= 0x80; // make sure it's a write cmd (7th bit = 1)

	uint8_t txBuffer[2] = {regAddress, data}; // send register address in write mode along with data byte
	uint8_t rxBuffer[2];

#ifdef UNIT_TEST
	th->virtualRegister = txBuffer[0];
#else
	DSD_SendBytes(txBuffer, rxBuffer, 2);
#endif
}





void DRD_TransmitTest()
{
	DRD_SetModeIdle();

	// Set TX base address
	volatile uint8_t reg = DRD_ReadRegister(DRD_RFM95_REG_0E_FIFO_TX_BASE_ADDR);
	DRD_WriteRegister(DRD_RFM95_REG_0E_FIFO_TX_BASE_ADDR, 0x00);
	reg = DRD_ReadRegister(DRD_RFM95_REG_0E_FIFO_TX_BASE_ADDR);

	// Fill TX dummy bytes in FIFO
	DRD_WriteRegister(DRD_RFM95_REG_00_FIFO, 0x81);
	DRD_WriteRegister(DRD_RFM95_REG_00_FIFO, 0x42);
	DRD_WriteRegister(DRD_RFM95_REG_00_FIFO, 0x24);
	DRD_WriteRegister(DRD_RFM95_REG_00_FIFO, 0x18);

	// Turn on TX mode
	DRD_SetModeTransmit();

	// Check mode
	reg = DRD_ReadCurrentMode();

	while(reg != 0x01)
	{
		reg = DRD_ReadCurrentMode();
	}
}

uint8_t DRD_ReadCurrentMode()
{
	uint8_t mode = DRD_ReadRegister(DRD_RFM95_REG_01_OP_MODE);
	mode &= 0x07; // read mode bits [2:0]
	return mode;
}

void DRD_SetLORAMode()
{
	DRD_SetModeSleep();


	uint8_t regAddress = DRD_RFM95_REG_01_OP_MODE;
	regAddress |= 0x80; // make sure it's a write command (7th bit = 1)

	/* Get previous DRD_RFM95_REG_01_OP_MODE bits */
	uint8_t previous = DRD_ReadRegister(DRD_RFM95_REG_01_OP_MODE);

	previous |= 0x80; // set LORA mode (set bit 7)

	uint8_t txBuffer[2] = {regAddress, previous};
	uint8_t rxBuffer[2];
	DSD_SendBytes(txBuffer, rxBuffer, 2);


	volatile uint8_t confirmBytes = DRD_ReadRegister(DRD_RFM95_REG_01_OP_MODE);
	confirmBytes = confirmBytes;
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

void DRD_SetModeTransmit()
{
	uint8_t regAddress = DRD_RFM95_REG_01_OP_MODE;
	regAddress |= 0x80; // make sure it's a write command (7th bit = 1)

	/* Get previous DRD_RFM95_REG_01_OP_MODE bits */
	uint8_t previous = DRD_ReadRegister(DRD_RFM95_REG_01_OP_MODE);
	previous &= 0xF8; // clear bits in Mode field

	previous |= 0x03; // set TX mode

	uint8_t txBuffer[2] = {regAddress, previous};
	uint8_t rxBuffer[2];
	DSD_SendBytes(txBuffer, rxBuffer, 2);
}

void DRD_SetModeReceiveOnce()
{
	uint8_t regAddress = DRD_RFM95_REG_01_OP_MODE;
	regAddress |= 0x80; // make sure it's a write command (7th bit = 1)

	/* Get previous DRD_RFM95_REG_01_OP_MODE bits */
	uint8_t previous = DRD_ReadRegister(DRD_RFM95_REG_01_OP_MODE);
	previous &= 0xF8; // clear bits in Mode field

	//previous |= 0x06; // set RXSINGLE mode

	previous |= 0x07; // set CAD mode

	uint8_t txBuffer[2] = {regAddress, previous};
	uint8_t rxBuffer[2];
	DSD_SendBytes(txBuffer, rxBuffer, 2);

	// Check mode
	volatile uint8_t reg = DRD_ReadCurrentMode();

	while(reg != 0x01)
	{
		reg = DRD_ReadCurrentMode();
	}

	reg = DRD_ReadRegister(DRD_RFM95_REG_12_IRQ_FLAGS);


	DRD_WriteRegister(DRD_RFM95_REG_12_IRQ_FLAGS, 0xFF); // clear RxTimeout IRQ and CadDone

	reg = DRD_ReadRegister(DRD_RFM95_REG_1B_RSSI_VALUE);
	reg = reg;


}






#ifdef UNIT_TEST
/***************************************************************************************************
*      Functions in this section are only to be used for unit testing internal functionality of module
*      !DO NOT USE IN PRODUCTION CODE!
***************************************************************************************************/
/* Allow TestHandle to be changed by outside world */
unit_static void UT_SetActiveTestHandle(TestHandle* newHandle)
{
	th = newHandle;
}
/***************************************************************************************************
****************************************************************************************************/
#endif
