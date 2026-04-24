#include <avr/io.h>
#include "uart.h"

#define F_CPU 16000000UL

int main(void){
    uart_init();
    uart_send_string("hello hi how are you?\r\n");

    while(1){
        if(uart_data_available()){
            uint8_t byte = uart_receive_byte();
            uart_send_byte(byte);
        }
    }
}