#include "uart.h"

void uart_init(void){
    UBRR0H = 0;
    UBRR0L = 103;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void uart_send_byte(uint8_t data){
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

void uart_send_string(char *str){
    while(*str != '\0'){
        uart_send_byte(*str);
        str++;
    }
}

uint8_t uart_receive_byte(void){
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

uint8_t uart_data_available(void){
    return (UCSR0A & (1<<RXC0)) ? 1 : 0;
}