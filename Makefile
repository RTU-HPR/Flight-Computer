HOME = /home/$(USER)
PICO_SDK_PATH = $(HOME)/.pico-sdk

.PHONY: build upload

default: build upload

build:
	cmake -B build/ -S . -DPICO_SDK_PATH=$(PICO_SDK_PATH)/sdk/2.1.1 -G Ninja
	$(PICO_SDK_PATH)/ninja/v1.12.1/ninja -C build/

upload:
	$(PICO_SDK_PATH)/picotool/2.1.1/picotool/picotool load build/src/FlightComputer.elf -xf