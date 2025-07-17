ROOT_DIR      := /media/kmk/DATA/Ubuntu/Firmware-Foundation/Bare-metal-series-STM32/workspace/bare-metal-stm32
APP_DIR       := $(ROOT_DIR)/examples/Serial/
INCLUDE_DIR   := $(ROOT_DIR)/include
DRIVERS_DIR   := $(ROOT_DIR)/drivers
BUILD_DIR     := $(ROOT_DIR)/build
BIN_DIR       := $(BUILD_DIR)/bin

SRC	      := $(shell find $(APP_DIR) $(BUILD_DIR) $(DRIVERS_DIR) -iname "*.c")
OBJ           := $(patsubst %.c, %.o, $(SRC))
LD            := $(BUILD_DIR)/stm32_ls.ld 
TARGET        := $(BIN_DIR)/final.elf
MAP           := $(BIN_DIR)/final.map

CC            := arm-none-eabi-gcc
MCU           := cortex-m4
CFLAGS        := -c -mcpu=$(MCU) $(addprefix -I, $(INCLUDE_DIR)) -mthumb -std=gnu11 
LDFLAGS       := -nostdlib -T $(LD) -Wl,-Map=$(MAP)

.PHONY: all build flash clean

# Build
all: flash

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ 

flash: build
	openocd -f /usr/share/openocd/scripts/board/st_nucleo_f4.cfg

clean: 
	rm -f $(OBJ) $(BIN_DIR)/*
