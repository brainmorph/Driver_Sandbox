CFLAGS=-std=c99
CFLAGS += -Wall
#CFLAGS += -Wextra
#CFLAGS += -Wpointer-arith
#CFLAGS += -Wcast-align
#CFLAGS += -Wwrite-strings
#CFLAGS += -Wswitch-default
#CFLAGS += -Wunreachable-code
#CFLAGS += -Winit-self
#CFLAGS += -Wmissing-field-initializers
#CFLAGS += -Wno-unknown-pragmas
#CFLAGS += -Wstrict-prototypes
#CFLAGS += -Wundef
#CFLAGS += -Wold-style-definition
#CFLAGS += -Wfatal-errors
#######################################################



INC_H_DIR = ../Inc
INC_ALL = $(INC_H_DIR)

INC_DIR = $(addprefix -I, $(INC_ALL))

# Processor specific header files are... complicated.  Add all header files in the CMSIS sub-dirs
INC_CMSIS := $(addprefix -I,$(shell find ../Drivers/CMSIS/ -type d -print))

SRC_DIR = ../Src
BLD_DIR = bld
TST_DIR = tests
UNITY_DIR = unity

UNITY_INC = -Iunity/src \
			-Iunity/extras/fixture/src \
			-Iunity/extras/memory/src


#Add locations of each source file that needs to be built
LIST_IMPORTANT_FILES = $(TST_DIR)/Test_dc_gpio_driver.c \
						$(TST_DIR)/Test_dc_spi_driver.c \
						$(TST_DIR)/test_runners/all_tests.c \
						$(TST_DIR)/test_runners/TestRunner_dc_gpio_driver.c \
						$(TST_DIR)/test_runners/TestRunner_dc_spi_driver.c \
						$(UNITY_DIR)/extras/fixture/src/unity_fixture.c \
						$(SRC_DIR)/dc_gpio_driver.c \
						$(SRC_DIR)/dc_spi_driver.c \
						$(UNITY_DIR)/src/unity.c \



MACRO_DEFINE_LIST = UNIT_TEST
MACRO_DEFINE = $(addprefix -D , $(MACRO_DEFINE_LIST))

help:
	echo $(LIST_IMPORTANT_FILES)
	echo $(LIST_IMPORTANT_FILES:.c=.o)
#$(BLD_DIR)/%.o: $(LIST_IMPORTANT_FILES)*c


%.o: %.c
	gcc $(CFLAGS) $(INC_DIR) $(INC_CMSIS) $(UNITY_INC) $(MACRO_DEFINE) -c $< -o $(BLD_DIR)/$(notdir $@)

program: $(LIST_IMPORTANT_FILES:.c=.o) last_step
	./all_tests.exe


last_step:
	gcc $(CFLAGS) $(BLD_DIR)/* -o all_tests.exe

# $(BLD_DIR)/dc_hal_spiTest.o: $(TST_DIR)/dc_hal_spiTest.c
# 	gcc $(CFLAGS) -I$(INC_DIR) $(UNITY_INC) -c $(TST_DIR)/dc_hal_spiTest.c -o $(BLD_DIR)/dc_hal_spiTest.o
# 	@echo ">>>woot $@ is done"
	
# $(BLD_DIR)/all_tests.o: $(TST_DIR)/test_runners/all_tests.c
# 	gcc $(CFLAGS) -I$(INC_DIR) $(UNITY_INC) -c $(TST_DIR)/test_runners/all_tests.c -o $(BLD_DIR)/all_tests.o
# 	@echo ">>>woot $@ is done"
	
# $(BLD_DIR)/dc_hal_spiTestRunner.o: $(TST_DIR)/test_runners/dc_hal_spiTestRunner.c
# 	gcc $(CFLAGS) -I$(INC_DIR) $(UNITY_INC) -c $(TST_DIR)/test_runners/dc_hal_spiTestRunner.c -o $(BLD_DIR)/dc_hal_spiTestRunner.o
# 	@echo ">>>woot $@ is done"
	
# $(BLD_DIR)/unity_fixture.o: $(UNITY_DIR)/extras/fixture/src/unity_fixture.c
# 	gcc $(CFLAGS) -I$(INC_DIR) $(UNITY_INC) -c $(UNITY_DIR)/extras/fixture/src/unity_fixture.c -o $(BLD_DIR)/unity_fixture.o
# 	@echo ">>>woot $@ is done"
	
# $(BLD_DIR)/dc_hal_spi.o: $(SRC_DIR)/dc_hal_spi.c
# 	gcc $(CFLAGS) -I$(INC_DIR) $(UNITY_INC) -c $(SRC_DIR)/dc_hal_spi.c -o $(BLD_DIR)/dc_hal_spi.o
# 	@echo ">>>woot $@ is done"

# $(BLD_DIR)/unity.o: $(UNITY_DIR)/src/unity.c
# 	gcc $(CFLAGS) -I$(INC_DIR) $(UNITY_INC) -c $(UNITY_DIR)/src/unity.c -o $(BLD_DIR)/unity.o
# 	@echo ">>>woot $@ is done"



	
# program: $(BLD_DIR)/dc_hal_spiTest.o $(BLD_DIR)/all_tests.o $(BLD_DIR)/dc_hal_spiTestRunner.o $(BLD_DIR)/unity_fixture.o $(BLD_DIR)/dc_hal_spi.o $(BLD_DIR)/unity.o
# 	gcc $(CFLAGS) $(BLD_DIR)/* -o all_tests.exe
# 	@echo ">>>woot $@ is done"
	
clean:
	rm -f bld/*.o
	rm -f all_tests.exe