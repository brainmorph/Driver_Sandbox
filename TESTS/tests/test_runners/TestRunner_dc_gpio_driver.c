#include "unity.h"
#include "unity_fixture.h"



TEST_GROUP_RUNNER(dc_gpio_driver)
{
	RUN_TEST_CASE(dc_gpio_driver, InitializeGPIOAPort);
	RUN_TEST_CASE(dc_gpio_driver, SetBit);
	RUN_TEST_CASE(dc_gpio_driver, ClearBit); /* This test runner MUST get called after the SetBit test runner */
}
