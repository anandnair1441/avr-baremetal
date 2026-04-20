#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

volatile uint16_t tick_count = 0;    //shared between ISR and main().forces the compiler to re-read it from RAM every time instead of 
                                    //caching it in a CPU register. Without volatile the while loop never sees the ISR's updates.

ISR(TIMER1_COMPA_vect) {           //special function the CPU jumps to automatically when Timer1 matches OCR1A
    tick_count++;
}

void timer1_init(void) {
    TCCR1A = 0x00;                                 //clears WGM1x and COM1x bits
    TCCR1B |= (1<<WGM12)|(1<<CS11)|(1<<CS10);     //WGM12=1 enables CTC mode CS11=1, CS10=1 select prescaler 64.
    OCR1A = 249;                                 //resets and fires ISR when this value
    TIMSK1 |= (1<<OCIE1A);                      //enables the compare match interrupt.
    sei();                                     //enables global interrupts
}

int main(void) {
    DDRB |= (1<<PB5);
    timer1_init();

    while(1) {
        if(tick_count >= 500) {
            tick_count = 0;
            PORTB ^= (1<<PB5);
        }
    }
}