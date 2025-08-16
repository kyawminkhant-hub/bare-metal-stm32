CURRENT_DIR := $(shell pwd)
ROOT_DIR := $(abspath $(CURRENT_DIR)/../../../)

FLAGS := -nostdlib

.PHONY: all build flash clean

all: flash

flash:
	$(MAKE) -C $(ROOT_DIR) APP_DIR=$(CURRENT_DIR) L=$(FLAGS)

build:
	$(MAKE) -C $(ROOT_DIR) APP_DIR=$(CURRENT_DIR) L=$(FLAGS) build

clean:
	$(MAKE) -C $(ROOT_DIR) APP_DIR=$(CURRENT_DIR) clean


