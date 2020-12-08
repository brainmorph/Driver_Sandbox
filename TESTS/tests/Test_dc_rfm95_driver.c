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
	printf("Test register before: 0x%x \r\n", testRegister);
	DRD_ReadRegister(testRegister);
	
	TEST_ASSERT_EQUAL(0, CHECK_BIT(th.virtualRegister, 7));  // Check that 7th bit is set to 0
	printf("DRD_ReadRegister after: 0x%x \r\n", th.virtualRegister);
}
