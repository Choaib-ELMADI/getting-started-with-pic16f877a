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
    TRISB0 = 0;
    TRISB7 = 1;
    
    while (1) {
        PORTBbits.RB0 = PORTBbits.RB7;
    }

    return;
}
