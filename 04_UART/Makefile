MCU    = atmega328p
AVRMCU = m328p
F_CPU  = 16000000UL
PORT   = COM5
CC     = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

.PHONY: all upload clean

all: main.hex

main.elf: main.c uart.c
	$(CC) $(CFLAGS) -o main.elf main.c uart.c

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom main.elf main.hex

upload: main.hex
	$(AVRDUDE) -D -p $(AVRMCU) -c arduino -P $(PORT) -b 115200 -U flash:w:main.hex

clean:
	del main.elf main.hex