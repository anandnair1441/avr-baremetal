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
| # | Peripheral | Key Concepts |
|---|---|---|
| 01 | GPIO |  DDRx, PORTx, PINx, internal pull-up |
| 02 | Timer1 CTC | ISR, prescaler, OCR1A, volatile |
| 03 | UART | UBRR, 8N1, UDRE0, RXC0 |
| 04 | I2C (TWI) |  START/STOP, ACK/NACK, TWSR codes |
| 05 | SPI | SPCR, SPDR, full duplex |



## How to Build
cd into any project folder, then:
make
make flash
