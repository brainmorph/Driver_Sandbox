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
	virtual_gpio_handle.portClock = &virtual_register;

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


TEST(dc_gpio_driver, DGD_InitPort)
{
	printf("AHB1ENR = %x \n", *virtual_gpio_handle.portClock);

	// Check RCC AHB1ENR for PORTA
	TEST_ASSERT_EQUAL(0, CHECK_BIT(*virtual_gpio_handle.portClock, 0));
	DGD_InitPort(PORTA);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(*virtual_gpio_handle.portClock, 0));

	printf("AHB1ENR = %x \n", *virtual_gpio_handle.portClock);

	// Check RCC AHB1ENR for PORTB
	TEST_ASSERT_EQUAL(0, CHECK_BIT(*virtual_gpio_handle.portClock, 1));
	DGD_InitPort(PORTB);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(*virtual_gpio_handle.portClock, 1));

	printf("AHB1ENR = %x \n", *virtual_gpio_handle.portClock);
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

TEST(dc_gpio_driver, DGD_SetPinDirection)
{
	uint8_t bitToTest = 0;

	// Test input mode
	bitToTest = 0;
	DGD_SetPinDirection(PORTA, bitToTest, INPUT);
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest * 2));
	bitToTest = 1;
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest * 2 + 1));
	printf("MODER set to input: 0x%x\n", virtual_gpio_handle.portRegisters->MODER);

	// Test output mode
	bitToTest = 0;
	DGD_SetPinDirection(PORTA, bitToTest, OUTPUT);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest * 2));
	bitToTest = 1;
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest * 2 + 1));
	printf("MODER set to output: 0x%x\n", virtual_gpio_handle.portRegisters->MODER);

	DGD_SetPinDirection(PORTB, 5, OUTPUT);
	bitToTest = 5;
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest * 2));
	bitToTest = 1;
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_gpio_handle.portRegisters->MODER, bitToTest * 2 + 1));
	printf("MODER set to output: 0x%x\n", virtual_gpio_handle.portRegisters->MODER);

}

TEST(dc_gpio_driver, DGD_WritePin)
{
	uint8_t bitToTest = 0;

	/* DGD_WritePin uses the BSRR register which is Write Only but I can still make sure the correct pin is being written to
	 * even though technically the real BSRR register can't be read back.  I'm using a virtual register here.
	 * BSRR register is funky... read documentation.  You need to offset bit pin by 16 when checking if the CLEAR bit
	 * functionality of BSRR register was used.*/
	bitToTest = 0;
	DGD_WritePin(PORTA, bitToTest, LOW);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_gpio_handle.portRegisters->BSRR, bitToTest + 16)); // offset by 16 to check CLEAR bits
	DGD_WritePin(PORTA, bitToTest, HIGH);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_gpio_handle.portRegisters->BSRR, bitToTest)); // no need for offset when checking SET bits

	bitToTest = 5;
	DGD_WritePin(PORTA, bitToTest, LOW);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_gpio_handle.portRegisters->BSRR, bitToTest + 16)); // offset by 16 to check CLEAR bits
	DGD_WritePin(PORTA, bitToTest, HIGH);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_gpio_handle.portRegisters->BSRR, bitToTest)); // no need for offset when checking SET bits

	// Check for failure when not using DGD_WritePin
	virtual_gpio_handle.portRegisters->BSRR = 0x0; // reset BSRR register
	bitToTest = 0;
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_gpio_handle.portRegisters->BSRR, bitToTest + 16));
	DGD_WritePin(PORTA, bitToTest, LOW);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_gpio_handle.portRegisters->BSRR, bitToTest + 16));
}

TEST(dc_gpio_driver, DGD_ReadPin)
{
	uint8_t bitToTest;

	bitToTest = 0;
	TEST_ASSERT_EQUAL(0, CHECK_BIT(virtual_gpio_handle.portRegisters->IDR, bitToTest));
	TEST_ASSERT_EQUAL(0, DGD_ReadPin(PORTA, bitToTest)); // ensure ReadPin works
	// force IDR bit to a certain state even though IDR register is technically Read Only
	DGD_SetBit(&virtual_gpio_handle.portRegisters->IDR, bitToTest);
	TEST_ASSERT_EQUAL(1, CHECK_BIT(virtual_gpio_handle.portRegisters->IDR, bitToTest)); // ensure bit is set properly
	TEST_ASSERT_EQUAL(1, DGD_ReadPin(PORTA, bitToTest)); // ensure ReadPin works

}
