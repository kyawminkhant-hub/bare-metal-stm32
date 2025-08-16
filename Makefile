ROOT_DIR	:= path/to/bare-metal-stm32
APP_DIR		:= $(ROOT_DIR)/examples/Blinky
INCLUDE_DIR	:= $(ROOT_DIR)/include
DRIVERS_DIR	:= $(ROOT_DIR)/drivers
LIB_DIR		:= $(ROOT_DIR)/lib
BUILD_DIR	:= $(ROOT_DIR)/build
BIN_DIR		:= $(BUILD_DIR)/bin

SRC	        := $(shell find $(APP_DIR) $(BUILD_DIR) $(DRIVERS_DIR) -iname "*.c")
OBJ		:= $(patsubst %.c, %.o, $(SRC))
INCLUDE		:= $(addprefix -I, $(INCLUDE_DIR))
LD		:= $(BUILD_DIR)/stm32_ls.ld
TARGET		:= $(BIN_DIR)/final.elf
MAP		:= $(BIN_DIR)/final.map

CC		:= arm-none-eabi-gcc 
MCU		:= cortex-m4
CFLAGS		:= -mcpu=$(MCU) -mthumb -std=gnu11
LDFLAGS		:= -T $(LD) --specs=nano.specs --specs=nosys.specs -Wl,-Map=$(MAP)
STDLIB		:= -nostdlib

.PHONY: all build flash clean

# Build
all: flash

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(STDLIB) $^ -o $@ 

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

flash: build
	openocd -f /usr/share/openocd/scripts/board/st_nucleo_f4.cfg

clean: 
	rm -f $(OBJ) $(BIN_DIR)/*
