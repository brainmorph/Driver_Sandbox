#include "unity.h"
#include "unity_fixture.h"



TEST_GROUP_RUNNER(dc_rfm95_driver)
{
	RUN_TEST_CASE(dc_rfm95_driver, DRD_ReadRegister);
	RUN_TEST_CASE(dc_rfm95_driver, DRD_WriteRegister);
}
