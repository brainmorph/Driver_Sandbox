/***************************************************************************************************
*     Include Files
***************************************************************************************************/
#include "dc_gpio_driver.h"
#include "unity.h"
#include "unity_fixture.h"


/***************************************************************************************************
*     Local Macro Definitions
***************************************************************************************************/
#define CHECK_BIT(reg, num) ((reg >> num) & 0x1)

/***************************************************************************************************
*     Static Function Declarations
***************************************************************************************************/

/***************************************************************************************************
*     Static Variable Definitions
***************************************************************************************************/
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
	// This test proves that without calling SetBit(), the bit doesn't set (obvious but useful)
	uint8_t bitToTest = 7;
	TEST_ASSERT_NOT_EQUAL(1, CHECK_BIT(virtual_register, bitToTest));

	// Now confirm that SetBit() does its job
	bitToTest = 7;
	DGD_SetBit(&virtual_register, bitToTest);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, bitToTest));

	bitToTest = 0;
	DGD_SetBit(&virtual_register, bitToTest);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, bitToTest));

	bitToTest = 31;
	DGD_SetBit(&virtual_register, bitToTest);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, bitToTest));
}

TEST(dc_gpio_driver, ClearBit)
{
	/***
	 * NOTE: make sure DGD_SetBit() is tested and working before running these tests!
	 ***/

	// This test proves that without calling ClearBit(), the bit doesn't clear (obvious but useful)
	uint8_t bitToTest = 7;
	DGD_SetBit(&virtual_register, bitToTest);
	TEST_ASSERT_NOT_EQUAL(0, CHECK_BIT(virtual_register, bitToTest)); // notice the NOT equal in the test

	// Now confirm that ClearBit() does its job
	bitToTest = 7;
	DGD_SetBit(&virtual_register, bitToTest);
	DGD_ClearBit(&virtual_register, bitToTest);
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, bitToTest));

	bitToTest = 0;
	DGD_SetBit(&virtual_register, bitToTest);
	DGD_ClearBit(&virtual_register, bitToTest);
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, bitToTest));

	bitToTest = 31;
	DGD_SetBit(&virtual_register, bitToTest);
	DGD_ClearBit(&virtual_register, bitToTest);
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, bitToTest));
}

TEST(dc_gpio_driver, InitializeGPIOAPort)
{
	DGD_Initialize(&virtual_register);

	uint8_t bitValue = (virtual_register >> 0) & 0x1; // read correct bit number
	TEST_ASSERT_EQUAL(bitValue, 1);
}

