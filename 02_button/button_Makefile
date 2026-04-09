MCU    = atmega328p
AVRMCU = m328p
F_CPU  = 16000000UL
PORT   = COM5
BAUD   = 115200
SRC    = button.c
TARGET = button
CC     = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

.PHONY: all upload clean

all: $(TARGET).hex

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: $(TARGET).hex
	$(AVRDUDE) -D -p $(AVRMCU) -c arduino -P $(PORT) -b $(BAUD) -U flash:w:$<

clean:
	del $(TARGET).elf $(TARGET).hex