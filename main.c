#include <xc.h>

#define _XTAL_FREQ 20000000

#define Incr PORTDbits.RD0
#define Decr PORTDbits.RD1
#define Reset PORTDbits.RD2

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

unsigned char counter = 0;
unsigned char step;
unsigned char delay;

void main(void) {
    TRISD = 0x77;
    TRISB = 0x00;
    TRISC = 0xFF;
    
    while (1) {
        step = (PORTD >> 4) & 0b00000111;
        
        if (Incr) counter += step;
        if (Decr) counter -= step;
        if (Reset) counter = 0;
        PORTB = counter;
        
        delay = PORTC;
        for (unsigned char i = 0; i < delay; ++i) {
            __delay_ms(10);
        }
    }
    
    return;
}