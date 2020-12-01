/***************************************************************************************************
*     Include Files
***************************************************************************************************/
#include "dc_spi_driver.h"
#include "unity.h"
#include "unity_fixture.h"


/***************************************************************************************************
*     Local Macro Definitions
***************************************************************************************************/
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

	virtual_SPI_registers.CR1 = 0x0;

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
}
