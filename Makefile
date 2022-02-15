sketch      := nerdlight-firmware.ino
CORE        := esp8266:esp8266
CHIP		:= esp8266
boardconfig := "${CORE}:nodemcu"

ESPTOOL 	:= esptool.py
ARDUINO_CLI ?= arduino-cli
MKSPIFFS    ?= ~/Library/Arduino15/packages/esp8266/tools/mkspiffs/2.5.0-4-b40a506/mkspiffs
BC          ?= bc

DEVICE :=/dev/cu.usbserial-0001
BUILD_SPIFFS_START_HEX := 0x200000

.PHONY: build
build:
	$(ARDUINO_CLI) compile --fqbn $(boardconfig) $(sketch)

.PHONY: flash
flash:
	$(ARDUINO_CLI) upload -p ${DEVICE} --fqbn ${boardconfig} ${sketch} 

.PHONY: filesystem.bin
.ONESHELL:
filesystem.bin:
	# Tested with NodeMCU
	$(MKSPIFFS) -c data/ -p 256 -b 8192 -s 2072576 $@

.PHONY: flash-fs
.ONESHELL:
flash-fs: filesystem.bin
	$(ESPTOOL) --chip ${CHIP} \
	  --port ${DEVICE} \
	  --baud 460800 \
	  --before default_reset \
	  --after hard_reset \
	  write_flash ${BUILD_SPIFFS_START_HEX} filesystem.bin


.PHONY: clean
clean:
	rm -rf build
	rm -f filesystem.bin