#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF


void main(void) {
    TRISB = 0x00;
    while (1) {
        PORTB = 0xFF;
        __delay_ms(1000);
        PORTB = 0x00;
        __delay_ms(1000);
    }
    
    return;
}
