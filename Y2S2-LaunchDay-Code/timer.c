#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

static volatile uint32_t timerTicks = 0;

void TIM0_init(void) {
    /*
    Initializes Timer0 to generate an interrupt every 1ms
    Sets up CTC mode
    Enables the Timer Compare Match A interrupt and global interrupts
	Set Prescaler to 64 and OCR0A to 249
	tick_Hz = F_CPU / (prescaler * (ARR + 1))
			= 16,000,000 / (64 * (249 + 1))
			= 16,000,000 / 16,000
			= 1000 Hz
			= 1 tick every 1ms
    */
	TCNT0 = 0; //Sets tick counter to 0
    TCCR0A = (1 << WGM01); //Sets CTC mode
    TCCR0B = (1 << CS01) | (1 << CS00);  //Sets prescaler to 64
    OCR0A = 249; //Sets ARR to 249
    TIMSK0 = (1 << OCIE0A); //Enables Timer Compare Match A interrupt
    sei(); //Begins global interrupts
}

ISR(TIMER0_COMPA_vect) {
    timerTicks++;
}

uint32_t timestamp(void) {
    /*
    Stops interupts, copies the current tick count, then restarts interupts
    This is to ensure that the tick count is not updated while we are copying it
    */
    cli();
    uint32_t ticksCopy = timerTicks;
    sei();
    return ticksCopy;
}
