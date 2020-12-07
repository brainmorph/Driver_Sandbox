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

#Applicaion level header files
INC_H_DIR = ../Inc

#Add header files from sub-directories
INC_HAL_DIR = $(shell find ../Drivers/STM32F4xx_HAL_Driver/ -type d -print)
INC_CMSIS := $(shell find ../Drivers/CMSIS/ -type d -print)

#Combine list of all header files
INC_ALL = $(INC_H_DIR) $(INC_HAL_DIR) $(INC_CMSIS)
INC = $(addprefix -I, $(INC_ALL))

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
						$(TST_DIR)/Test_dc_rfm95_driver.c \
						$(TST_DIR)/test_runners/all_tests.c \
						$(TST_DIR)/test_runners/TestRunner_dc_gpio_driver.c \
						$(TST_DIR)/test_runners/TestRunner_dc_spi_driver.c \
						$(TST_DIR)/test_runners/TestRunner_dc_rfm95_driver.c \
						$(UNITY_DIR)/extras/fixture/src/unity_fixture.c \
						$(SRC_DIR)/dc_gpio_driver.c \
						$(SRC_DIR)/dc_spi_driver.c \
						$(SRC_DIR)/dc_rfm95_driver.c \
						$(UNITY_DIR)/src/unity.c \



MACRO_DEFINE_LIST = UNIT_TEST
MACRO_DEFINE = $(addprefix -D , $(MACRO_DEFINE_LIST))

help:
	echo $(LIST_IMPORTANT_FILES)
	echo $(LIST_IMPORTANT_FILES:.c=.o)
#$(BLD_DIR)/%.o: $(LIST_IMPORTANT_FILES)*c


%.o: %.c
	gcc $(CFLAGS) $(INC) $(UNITY_INC) $(MACRO_DEFINE) -c $< -o $(BLD_DIR)/$(notdir $@)


#Auto-execute program after compiling
program: $(LIST_IMPORTANT_FILES:.c=.o) all_tests.exe
	./all_tests.exe


all_tests.exe: $(LIST_IMPORTANT_FILES:.c=.o)
	gcc $(CFLAGS) $(BLD_DIR)/* -o all_tests.exe
	
clean:
	rm -f bld/*.o
	rm -f all_tests.exe