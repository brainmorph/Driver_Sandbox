#include "unity_fixture.h"
#include <stdio.h>

static void RunAllTests(void)
{
  RUN_TEST_GROUP(dc_gpio_driver);
  RUN_TEST_GROUP(dc_spi_driver);
  RUN_TEST_GROUP(dc_rfm95_driver);
}

int main(int argc, const char * argv[])
{
  printf("Running all tests...");
  return UnityMain(argc, argv, RunAllTests);
}
