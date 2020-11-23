#include "dc_gpio_driver.h"
#include "unity.h"
#include "unity_fixture.h"


static uint32_t virtual_register = 0;


TEST_GROUP(dc_gpio_driver);


TEST_SETUP(dc_gpio_driver)
{
	//printf("Setting up test...\n");
	virtual_register = 0x0; // initialize to reset value
}

TEST_TEAR_DOWN(dc_gpio_driver)
{
	//printf("Tearing down test...\n");
}

TEST(dc_gpio_driver, SetBit)
{
	uint8_t bitToTest = 7;
	DGD_SetBit(&virtual_register, bitToTest);
	uint8_t temp = (virtual_register >> bitToTest) & 0x1; // read correct bit number
	TEST_ASSERT_EQUAL(1, temp);

	bitToTest = 0;
	DGD_SetBit(&virtual_register, bitToTest);
	temp = (virtual_register >> bitToTest) & 0x1; // read correct bit number
	TEST_ASSERT_EQUAL(1, temp);

	bitToTest = 31;
	DGD_SetBit(&virtual_register, bitToTest);
	temp = (virtual_register >> bitToTest) & 0x1; // read correct bit number
	TEST_ASSERT_EQUAL(1, temp);
}

TEST(dc_gpio_driver, ClearBit)
{
	/* NOTE: make sure SetBit() is tested and working before running these tests! */

	uint8_t bitToTest = 7;
	DGD_SetBit(&virtual_register, bitToTest);
	//DGD_ClearBit(&virtual_register, bitToTest);
	uint8_t temp = (virtual_register >> bitToTest) & 0x1; // read correct bit number
	TEST_ASSERT_NOT_EQUAL(0, temp);

	bitToTest = 7;
	DGD_SetBit(&virtual_register, bitToTest);
	DGD_ClearBit(&virtual_register, bitToTest);
	temp = (virtual_register >> bitToTest) & 0x1; // read correct bit number
	TEST_ASSERT_EQUAL(0, temp);

	bitToTest = 0;
	DGD_SetBit(&virtual_register, bitToTest);
	DGD_ClearBit(&virtual_register, bitToTest);
	temp = (virtual_register >> bitToTest) & 0x1; // read correct bit number
	TEST_ASSERT_EQUAL(0, temp);

	bitToTest = 31;
	DGD_SetBit(&virtual_register, bitToTest);
	DGD_ClearBit(&virtual_register, bitToTest);
	temp = (virtual_register >> bitToTest) & 0x1; // read correct bit number
	TEST_ASSERT_EQUAL(0, temp);
}

TEST(dc_gpio_driver, InitializeGPIOAPort)
{
	DGD_Initialize(&virtual_register);

	uint8_t bitValue = (virtual_register >> 0) & 0x1; // read correct bit number
	TEST_ASSERT_EQUAL(bitValue, 1);
}

