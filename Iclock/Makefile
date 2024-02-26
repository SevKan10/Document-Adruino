NANO_BOARD = arduino:avr:nano:cpu=atmega328old 
ESP8266 = esp8266:esp8266:generic
UNO_BOARD = arduino:avr:uno
ATMEGA8  = MiniCore:avr:8
BOARD =  $(ESP8266)

PORT = com28
OUTPUT_DIR =./
BOARDS_TXT= *.hex
.PHONY: default 

default: all 

list:
	arduino-cli board listall
compile:
	arduino-cli -v compile --output-dir ${OUTPUT_DIR} --fqbn  ${BOARD} ./
upload:
	arduino-cli upload -v -p ${PORT} --fqbn ${BOARD} ./
clean:
	rm -rf *.elf  *.eep  *.map
ifneq (,$(wildcard $(BOARDS_TXT)))
	clean
endif

all:
	$(MAKE) compile
	$(MAKE) upload
	




