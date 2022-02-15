sketch      := nerdlight-firmware.ino
CORE        := {{core}}
CHIP		:= {{chip}}
boardconfig := {{boardconfig}}

ESPTOOL 	:= esptool.py
ARDUINO_CLI ?= arduino-cli
MKSPIFFS    ?= {{mkspiffs_bin}}
BC          ?= bc

DEVICE := {{device_port}}
BUILD_SPIFFS_START_HEX := {{spiffs_start_hex}}

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