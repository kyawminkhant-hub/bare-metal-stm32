CURRENT_DIR := $(shell pwd)
ROOT_DIR := $(abspath $(CURRENT_DIR)/../../../)

.PHONY: all build flash clean

all: flash

flash:
	$(MAKE) -C $(ROOT_DIR) APP_DIR=$(CURRENT_DIR)

build:
	$(MAKE) -C $(ROOT_DIR) APP_DIR=$(CURRENT_DIR) build

clean:
	$(MAKE) -C $(ROOT_DIR) APP_DIR=$(CURRENT_DIR) clean


