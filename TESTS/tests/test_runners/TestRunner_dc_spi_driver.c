#include "unity.h"
#include "unity_fixture.h"



TEST_GROUP_RUNNER(dc_spi_driver)
{
	RUN_TEST_CASE(dc_spi_driver, DSD_InitSPI); /* MUST get called after SetBit and ClearBit are tested */
}
