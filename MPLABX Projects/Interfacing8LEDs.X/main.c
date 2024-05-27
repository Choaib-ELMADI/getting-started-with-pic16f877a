#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void main(void) {
    TRISCbits.TRISC0 = 1;
    TRISB = 0x00;
    PORTB = 0b01010101;
    
    while (1) {
        if (PORTCbits.RC0 == 1) {
            PORTB = ~PORTB;
            __delay_ms(500);
        }
    }

    return;
}
