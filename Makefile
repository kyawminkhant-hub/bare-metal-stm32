APP_DIR	?= # default empty 

ROOT_DIR := /media/kmk/DATA/Ubuntu/Firmware-Foundation/Bare-metal-series-STM32/workspace/bare-metal-stm32

INCLUDE_DIR := $(ROOT_DIR)/include
DRIVERS_DIR := $(ROOT_DIR)/drivers
BOARDS_DIR := $(ROOT_DIR)/boards
LIB_DIR := $(ROOT_DIR)/lib
BUILD_DIR := $(ROOT_DIR)/build
CMSIS_CORE_DIR := $(INCLUDE_DIR)/CMSIS/Include
CMSIS_DEVICE_DIR := $(INCLUDE_DIR)/CMSIS/Device/ST/STM32F4xx/Include
DRIVERS_INC_DIR := $(INCLUDE_DIR)/drivers
BIN_DIR := $(BUILD_DIR)/bin

SRC := $(shell find $(APP_DIR) $(BUILD_DIR) $(DRIVERS_DIR) -iname "*.c")
OBJ := $(patsubst %.c, %.o, $(SRC))
CMSIS := $(CMSIS_CORE_DIR) $(CMSIS_DEVICE_DIR)
INCLUDE := $(addprefix -I, $(CMSIS) $(DRIVERS_INC_DIR) $(BOARDS_DIR) $(BUILD_DIR))
CONFIG := $(BUILD_DIR)/config.h
LD := $(BUILD_DIR)/stm32_ls.ld
TARGET := $(BIN_DIR)/final.elf
MAP := $(BIN_DIR)/final.map

CC := arm-none-eabi-gcc 
MCU := cortex-m4
CFLAGS := -mcpu=$(MCU) -mthumb -std=gnu11 -O0 -g
LDFLAGS := -T $(LD) --specs=nano.specs --specs=nosys.specs -Wl,-Map=$(MAP)

C ?= # placeholder for additional compiler flags
L ?= # placeholder for additional linker flags

.PHONY: all build flash clean

# Check that APP_DIR is non-empty
ifeq ($(strip $(APP_DIR)),)
$(error ERROR: APP_DIR not set. Run make from an application or example subdirectory!)
endif

# Build
all: flash

build: $(TARGET)

$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) $(L) $(LDFLAGS) $^ -o $@ 

$(CONFIG): $(APP_DIR)/prj.conf
	python3 conf_def.py $< $@

%.o: %.c $(CONFIG)
	$(CC) -c $(CFLAGS) $(C) $(INCLUDE) $< -o $@

flash: build
	openocd -f /usr/share/openocd/scripts/board/st_nucleo_f4.cfg

clean: 
	rm -f $(OBJ) $(CONFIG) $(BIN_DIR)/*
