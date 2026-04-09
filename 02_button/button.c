#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

int main(void) {
    DDRB |= (1 << PB5);
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    while (1) {
        if(!(PIND & (1 << PD2))){
           PORTB |= (1 << PB5); 
        }else{
            PORTB &= ~(1 << PB5);
        }
    }
}