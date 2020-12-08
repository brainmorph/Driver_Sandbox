/***************************************************************************************************
*     Include Files
***************************************************************************************************/
#include "dc_rfm95_driver.h"
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
static TestHandle th;



TEST_GROUP(dc_rfm95_driver);

TEST_SETUP(dc_rfm95_driver) // This runs before every test
{
	//printf("Setting up test...\n");
	th.virtualRegister = 0x0;

	//Inject test harness into driver
	UT_SetActiveTestHandle(&th);
}

TEST_TEAR_DOWN(dc_rfm95_driver)
{
	//printf("Tearing down test...\n");
}

TEST(dc_rfm95_driver, DRD_ReadRegister)
{
	uint8_t testRegister = 0x9D;
	printf("RFM95 read command before: 0x%x \r\n", testRegister);
	DRD_ReadRegister(testRegister);
	
	// Check that 7th bit is set to 0
	TEST_ASSERT_EQUAL(0, CHECK_BIT(th.virtualRegister, 7));
	printf("RFM95 read command after: 0x%x \r\n", th.virtualRegister);

	//Check that the lower 7 bits are unchanged
	printf("0x%x  0x%x \r\n", testRegister, th.virtualRegister);
	printf("0x%x  0x%x \r\n", testRegister & 0x7F, th.virtualRegister & 0x7F);
	TEST_ASSERT_EQUAL(0x7F & testRegister, 0x7F & th.virtualRegister);
}

TEST(dc_rfm95_driver, DRD_WriteRegister)
{
	uint8_t testRegister = 0x9D;
	printf("RFM95 write command before: 0x%x \r\n", testRegister);
	DRD_WriteRegister(testRegister);

	// Check that 7th bit is set to 1
	TEST_ASSERT_EQUAL(1, CHECK_BIT(th.virtualRegister, 7));
	printf("RFM95 write command after: 0x%x \r\n", th.virtualRegister);

	//Check that the lower 7 bits are unchanged
	printf("0x%x  0x%x \r\n", testRegister, th.virtualRegister);
	printf("0x%x  0x%x \r\n", testRegister & 0x7F, th.virtualRegister & 0x7F);
	TEST_ASSERT_EQUAL(0x7F & testRegister, 0x7F & th.virtualRegister);
}
