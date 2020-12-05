/***************************************************************************************************
*     Include Files
***************************************************************************************************/
#include "dc_spi_driver.h"
#include "unity.h"
#include "unity_fixture.h"


/***************************************************************************************************
*     Local Macro Definitions
***************************************************************************************************/
#define NULL ((void *)0)
#define CHECK_BIT(reg, num) (((reg) >> num) & 0x1)

/***************************************************************************************************
*     Static Function Declarations
***************************************************************************************************/

/***************************************************************************************************
*     Static Variable Definitions
***************************************************************************************************/
static uint32_t virtual_register = 0;
static SPI_TypeDef virtual_SPI_registers;
static DSD_SPI_t virtual_SPI_handle;


TEST_GROUP(dc_spi_driver);

TEST_SETUP(dc_spi_driver) // This runs before every test
{
	//printf("Setting up test...\n");
	virtual_register = 0x0;

	// Zero out virtual registers
	virtual_SPI_registers.CR1 = 0x0;
	virtual_SPI_registers.CR2 = 0x0;
	virtual_SPI_registers.SR = 0x0;
	virtual_SPI_registers.DR = 0x0;
	virtual_SPI_registers.CRCPR = 0x0;
	virtual_SPI_registers.RXCRCR = 0x0;
	virtual_SPI_registers.TXCRCR = 0x0;
	virtual_SPI_registers.I2SCFGR = 0x0;
	virtual_SPI_registers.I2SCFGR = 0x0;

	virtual_SPI_handle.registers = &virtual_SPI_registers;
	virtual_SPI_handle.clock = &virtual_register;

	UT_SetActiveGPIOhandle(&virtual_SPI_handle); // inject virtual GPIO handle into driver
}

TEST_TEAR_DOWN(dc_spi_driver)
{
	//printf("Tearing down test...\n");
}

TEST(dc_spi_driver, DSD_InitSPI)
{
	printf("initial APB1ENR = 0x%x \n", *virtual_SPI_handle.clock);
	printf("initial CR1 = 0x%x \n", virtual_SPI_handle.registers->CR1);
	
	UT_SetActiveSPIhandle(&virtual_SPI_handle);
	DSD_InitSPI();

	// Check CR1 bits
	printf("after init APB1ENR = 0x%x \n", *virtual_SPI_handle.clock);
	printf("after init CR1 = 0x%x \n", virtual_SPI_handle.registers->CR1);

	TEST_ASSERT_EQUAL(1, CHECK_BIT(*virtual_SPI_handle.clock, 12));
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_SPI_handle.registers->CR1, 2));
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_SPI_handle.registers->CR1, 6));
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_SPI_handle.registers->CR1, 11));
}

TEST(dc_spi_driver, DSD_SendBytes)
{
	// Check correct number of bytes are processed in the function
	uint8_t numBytes = 23;
	uint8_t dummyBytes[numBytes];
	int value = DSD_SendBytes(dummyBytes, dummyBytes, numBytes);
	TEST_ASSERT_EQUAL(numBytes, value);
	printf("Bytes written = %d\n", numBytes);

	// Check correct number of bytes are processed in the function
	numBytes = 155;
	dummyBytes[numBytes];
	value = DSD_SendBytes(dummyBytes, dummyBytes, numBytes);
	TEST_ASSERT_EQUAL(numBytes, value);
	printf("Bytes written = %d\n", numBytes);
	// Check last byte written to SPI_DR is the last byte in the buffer
	TEST_ASSERT_EQUAL(dummyBytes[numBytes - 1], (uint8_t)virtual_SPI_handle.registers->DR);
	printf("Last byte in buffer = 0x%x\n", dummyBytes[numBytes - 1]);
	printf("Last byte written = 0x%x\n", (uint8_t)virtual_SPI_handle.registers->DR);
}
