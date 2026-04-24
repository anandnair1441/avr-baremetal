# AVR Bare Metal - ATmega328P

Learning bare metal embedded programming on Arduino Uno (ATmega328P) 
using avr-gcc, avrdude, and Make.
Bare metal embedded drivers for ATmega328P in pure C. No Arduino libraries.

## Toolchain
- avr-gcc
- avrdude  
- GNU Make
- PuTTY-Serial Monitor

## Projects
| # | Peripheral | Key Concepts | Status |
|---|---|---|---|
| 01 | GPIO |  DDRx, PORTx, PINx, internal pull-up | Done |
| 02 | Timer1 CTC | ISR, prescaler, OCR1A, volatile | Done |
| 03 | UART | UBRR, 8N1, UDRE0, RXC0 | Done |
| 04 | I2C (TWI) |  START/STOP, ACK/NACK, TWSR codes | In progress |
| 05 | SPI | SPCR, SPDR, full duplex | Planned |



## How to Build
cd into any project folder, then:
make
make flash
