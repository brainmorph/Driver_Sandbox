#include "dc_gpio_driver.h"
#include "unity.h"
#include "unity_fixture.h"


static uint32_t virtual_RCC_AHB1ENR = 0x0;


TEST_GROUP(dc_gpio_driver);


TEST_SETUP(dc_gpio_driver)
{
	//Nothing
}

TEST_TEAR_DOWN(dc_gpio_driver)
{
	//Nothing
}

TEST(dc_gpio_driver, InitializeGPIOAPort)
{
	DGD_Initialize(&virtual_RCC_AHB1ENR);

	//Get bit 0 value
	uint8_t bitValue = (virtual_RCC_AHB1ENR >> 0) & 1;
	TEST_ASSERT_EQUAL(bitValue, 1);
}

TEST(dc_gpio_driver, PositiveNumbers)
{
	//int a = 10, b = 29;
	
	TEST_PASS_MESSAGE("Tests work and are running!");
	
	//TEST_ASSERT_EQUAL(39, sillyAdd(a, b));
	// TEST_ASSERT_NOT_EQUAL(40, sillyAdd(a, b));
	// //TEST_IGNORE();
	// TEST_ASSERT_EQUAL(40, sillyAdd(a, b));
	// TEST_IGNORE();
}
