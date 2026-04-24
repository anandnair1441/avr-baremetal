# Bare Metal UART Driver - ATmega328P

A complete UART driver written in pure C for the ATmega328P microcontroller (Arduino Uno), with **no Arduino libraries**. Every peripheral is configured directly through hardware registers using the ATmega328P datasheet.

---

## What This Is

This project implements a UART serial communication driver from scratch by directly manipulating the ATmega328P's USART0 peripheral registers. No 'Serial.h', no 'Wire.h', no Arduino framework - just C and the datasheet.

---

## Driver API

'''c
void    uart_init(void);                  // initialise USART0 at 9600 baud, 8N1
void    uart_send_byte(uint8_t data);     // transmit one byte
void    uart_send_string(char *str);      // transmit null-terminated string
void    uart_send_number(uint16_t num);   // transmit decimal number as ASCII
uint8_t uart_receive_byte(void);          // blocking receive - waits for byte
uint8_t uart_data_available(void);        // non-blocking check - 1 if byte waiting
'''

---

### Baud Rate - UBRR0H and UBRR0L

The USART baud rate is controlled by a 16-bit register split across two 8-bit registers.

**Formula** (Asynchronous Normal Mode, datasheet Table 20-1):
'''
UBRR = (F_CPU / (16 × BAUD)) - 1
UBRR = (16000000 / (16 × 9600)) - 1
UBRR = 103
'''

**Register write:**
'''c
UBRR0H = 0;    // high byte of 103 = 0
UBRR0L = 103;  // low byte of 103
'''

---

### Enable TX and RX - UCSR0B (0xC1)

| Bit | Name | Value | Reason |
|---|---|---|---|
| 4 | RXEN0 | 1 | Enable receiver hardware |
| 3 | TXEN0 | 1 | Enable transmitter hardware |
| others | - | 0 | Reset default, not needed |

'''c
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
'''

Without setting these bits the USART hardware is powered but inactive

---

### Frame Format - UCSR0C (0xC2)

**8N1 format:** 8 data bits, No parity, 1 stop bit.

| Bit | Name | Value | Reason |
|---|---|---|---|
| 2 | UCSZ01 | 1 | 8 data bits (part 1) |
| 1 | UCSZ00 | 1 | 8 data bits (part 2) |
| 3 | USBS0 | 0 | 1 stop bit (reset default) |
| 6,7 | UMSEL | 0 | Asynchronous mode (reset default) |
| 4,5 | UPM | 0 | No parity (reset default) |

'''c
UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
'''

Note: reset value of UCSR0C is '0x06' (UCSZ01=1, UCSZ00=1 at power on),  This line confirms it explicitly.

---

### Transmit Flow - UCSR0A UDRE0 flag (bit 5)

The USART has a one-byte transmit buffer. Writing a new byte before the previous one has shifted out corrupts the transmission.

**UDRE0 = 1** means the transmit buffer is empty and ready for a new byte.

'''c
void uart_send_byte(uint8_t data) {
    while(!(UCSR0A & (1<<UDRE0)));  // wait until buffer empty
    UDR0 = data;                     // load byte - hardware transmits automatically
}
'''

UDRE0 is a **read-only** flag - hardware manages it. we only observe it, never write it.

---

### Receive Flow - UCSR0A RXC0 flag (bit 7)

**RXC0 = 1** means a complete frame has been received and is waiting in UDR0.

'''c
uint8_t uart_receive_byte(void) {
    while(!(UCSR0A & (1<<RXC0)));  // wait until byte arrives
    return UDR0;                    // reading UDR0 clears RXC0 automatically
}
'''

Reading UDR0 automatically clears RXC0 - hardware managed, no manual flag clearing needed.

---

**Verify output in PuTTY:**
- Connection type: Serial
- Port: COM5 (may differ check in device manager )
- Speed: 9600

---


## Key Concepts Demonstrated

**Register-level peripheral configuration** - no library abstractions, direct hardware access through memory-mapped registers.

**Datasheet navigation** - every register and bit value sourced from ATmega328P DS40002061B chapter 20, not from tutorials or examples.

**Polling-based communication** - UDRE0 and RXC0 flags polled before every transfer, ensuring no data corruption from buffer overflow.

**Hardware frame formatting** - USART configured for industry-standard 8N1 asynchronous serial communication.

**Separation of concerns** - driver split into '.h' (interface) and '.c' (implementation) with header guards preventing double inclusion.

---

## Limitations

- **Blocking I/O** - 'uart_send_byte' and 'uart_receive_byte' spin-wait with no timeout.
- **Fixed baud rate** - init hardcodes 9600.no dynamic UBRR calculation.
- **No error handling** - UCSR0A contains Frame Error (FE0), Data OverRun (DOR0), and Parity Error (UPE0) flags. This driver does not check them.

---

## Reference

- ATmega328P Datasheet: DS40002061B (Microchip Technology)
- Chapter 20: USART0 - registers UCSR0A, UCSR0B, UCSR0C, UBRR0H, UBRR0L, UDR0
- Arduino Uno R3 Product Reference Manual: SKU A000066

---


This driver was written as part of a bare metal embedded systems learning path.

Next: I2C driver (TWI peripheral, chapter 22)