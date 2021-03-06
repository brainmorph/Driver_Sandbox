#include "unity.h"
#include "unity_fixture.h"



TEST_GROUP_RUNNER(dc_gpio_driver)
{
	RUN_TEST_CASE(dc_gpio_driver, SetBit);
	RUN_TEST_CASE(dc_gpio_driver, ClearBit); /* This test runner MUST get called after the SetBit test runner */

	RUN_TEST_CASE(dc_gpio_driver, DGD_InitPort); /* MUST get called after SetBit and ClearBit are tested */

	RUN_TEST_CASE(dc_gpio_driver, DGD_Select_Port_BaseAddress);

	RUN_TEST_CASE(dc_gpio_driver, DGD_SetPinDirection);
	RUN_TEST_CASE(dc_gpio_driver, DGD_WritePin);
	RUN_TEST_CASE(dc_gpio_driver, DGD_ReadPin);

	RUN_TEST_CASE(dc_gpio_driver, DGD_SetPinAlternateFunction);
}
