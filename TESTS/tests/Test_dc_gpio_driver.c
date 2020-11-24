/***************************************************************************************************
*     Include Files
***************************************************************************************************/
#include "dc_gpio_driver.h"
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
static GPIO_TypeDef virtual_port;



TEST_GROUP(dc_gpio_driver);


TEST_SETUP(dc_gpio_driver) // This runs before every test
{
	//printf("Setting up test...\n");
	virtual_register = 0x0;

	virtual_port.MODER = 0x0;
}

TEST_TEAR_DOWN(dc_gpio_driver)
{
	//printf("Tearing down test...\n");
}

TEST(dc_gpio_driver, SetBit)
{
	// This test proves that without calling SetBit(), the bit doesn't set (obvious but useful)
	uint8_t bitToTest = 7;
	TEST_ASSERT_NOT_EQUAL(1, CHECK_BIT(virtual_register, bitToTest)); // notice the NOT equal in the test

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



TEST(dc_gpio_driver, InitializeGPIOPort)
{
	// Initialization of GPIO Port A should set bit 0 in RCC_AHB1ENR
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, DGD_RCC_AHB1ENR_GPIOAEN_BIT));
	DGD_Initialize(&virtual_register, PORTA);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, DGD_RCC_AHB1ENR_GPIOAEN_BIT));


	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, DGD_RCC_AHB1ENR_GPIOBEN_BIT));
	DGD_Initialize(&virtual_register, PORTB);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, DGD_RCC_AHB1ENR_GPIOBEN_BIT));


	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, DGD_RCC_AHB1ENR_GPIOCEN_BIT));
	DGD_Initialize(&virtual_register, PORTC);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, DGD_RCC_AHB1ENR_GPIOCEN_BIT));

	// ...

	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, DGD_RCC_AHB1ENR_GPIOKEN_BIT));
	DGD_Initialize(&virtual_register, PORTK);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, DGD_RCC_AHB1ENR_GPIOKEN_BIT));
}



TEST(dc_gpio_driver, WriteGPIOOutputHigh)
{
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_port.MODER, 0));
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_port.MODER, 1));
	DGD_Write_GPIO_Pin(&virtual_port, 0, 1);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_port.MODER, 0));
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_port.MODER, 1));
}

