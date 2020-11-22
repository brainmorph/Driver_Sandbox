#include "unity_fixture.h"
#include <stdio.h>

static void RunAllTests(void)
{
  RUN_TEST_GROUP(dc_gpio_driver);
}

int main(int argc, const char * argv[])
{
  printf("Testing...");
  return UnityMain(argc, argv, RunAllTests);
}
