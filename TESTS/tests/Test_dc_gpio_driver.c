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
static DGD_GPIO_Port_t virtual_gpio_handle;


TEST_GROUP(dc_gpio_driver);


TEST_SETUP(dc_gpio_driver) // This runs before every test
{
	//printf("Setting up test...\n");
	virtual_register = 0x0;

	virtual_port.MODER = 0x0;
	virtual_port.BSRR = 0x0;
	virtual_port.IDR = 0x0;

	virtual_gpio_handle.portRegisters = &virtual_port;

	UT_SetActiveGPIOhandle(&virtual_gpio_handle); // inject virtual GPIO handle into driver
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



//TEST(dc_gpio_driver, InitializeGPIOPort)
//{
//	// Initialization of GPIO Port A should set bit 0 in RCC_AHB1ENR
//	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, 0));
//	DGD_Initialize(&virtual_register, PORTA);
//	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, 0));
//
//
//	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, 1));
//	DGD_Initialize(&virtual_register, PORTB);
//	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, 1));
//
//
//	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, 2));
//	DGD_Initialize(&virtual_register, PORTC);
//	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, 2));
//
//	// ...
//
//	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_register, 3));
//	DGD_Initialize(&virtual_register, PORTI);
//	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_register, 3));
//}



TEST(dc_gpio_driver, DGD_Select_Port_BaseAddress)
{
	// Test return value of function
	TEST_ASSERT_EQUAL(0, DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTA));
	TEST_ASSERT_EQUAL(0, DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTB));
	TEST_ASSERT_EQUAL(0, DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTC));
	TEST_ASSERT_EQUAL(0, DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTD));
	TEST_ASSERT_EQUAL(-1, DGD_Select_Port_BaseAddress(&virtual_gpio_handle, 33));


	printf("\nGPIO A address = %x\n", GPIOA);
	printf("GPIO B address = %x\n", GPIOB);
	printf("GPIO C address = %x\n", GPIOC);
	printf("GPIO D address = %x\n", GPIOD);
	printf("GPIO E address = %x\n", GPIOE);
	printf("GPIO F address = %x\n", GPIOF);
	printf("GPIO G address = %x\n", GPIOG);
	printf("GPIO H address = %x\n", GPIOH);
	printf("GPIO I address = %x\n", GPIOI);


	// Check register base address is set correctly
	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTA);
	printf("virtual gpio A port register base = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(GPIOA, virtual_gpio_handle.portRegisters);

	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTB);
	printf("virtual gpio B port register base = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(GPIOB, virtual_gpio_handle.portRegisters);

	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTC);
	printf("virtual gpio C port register base = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(GPIOC, virtual_gpio_handle.portRegisters);

	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTD);
	printf("virtual gpio D port register base = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(GPIOD, virtual_gpio_handle.portRegisters);

	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTE);
	printf("virtual gpio E port register base = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(GPIOE, virtual_gpio_handle.portRegisters);

	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTF);
	printf("virtual gpio F port register base = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(GPIOF, virtual_gpio_handle.portRegisters);

	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTG);
	printf("virtual gpio G port register base = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(GPIOG, virtual_gpio_handle.portRegisters);

	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTH);
	printf("virtual gpio H port register base = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(GPIOH, virtual_gpio_handle.portRegisters);

	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, PORTI);
	printf("virtual gpio I port register base = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(GPIOI, virtual_gpio_handle.portRegisters);


	// If port selection is out of bounds, test that function doesn't alter the base register address
	DGD_GPIO_TypeDef* temp = virtual_gpio_handle.portRegisters;
	printf("virtual port register base BEFORE invalid selection = %x\n", temp);
	DGD_Select_Port_BaseAddress(&virtual_gpio_handle, 33);
	printf("virtual port register base AFTER invalid selection = %x\n", virtual_gpio_handle.portRegisters);
	TEST_ASSERT_EQUAL(temp, virtual_gpio_handle.portRegisters);
}

TEST(dc_gpio_driver, DGD_Set_GPIO_Direction)
{

	uint8_t bitToTest = 0;

	// Test input mode
	DGD_SetPinDirection(PORTA, 0, INPUT);
	bitToTest = 0;
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest));
	bitToTest = 1;
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest));
	printf("MODER set to input: %x\n", virtual_gpio_handle.portRegisters->MODER);

	// Test output mode
	DGD_SetPinDirection(PORTA, 0, OUTPUT);
	bitToTest = 0;
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest));
	bitToTest = 1;
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest));
	printf("MODER set to output: %x\n", virtual_gpio_handle.portRegisters->MODER);
}
