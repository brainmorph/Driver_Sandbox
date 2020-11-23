#include "unity.h"
#include "unity_fixture.h"



TEST_GROUP_RUNNER(dc_gpio_driver)
{
	RUN_TEST_CASE(dc_gpio_driver, PositiveNumbers);
	RUN_TEST_CASE(dc_gpio_driver, InitializeGPIOAPort);
}
