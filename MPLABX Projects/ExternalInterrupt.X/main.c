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

void interrupt external();

void main(void) {
    INTCONbits.GIE = 1;         // Global Interrupt Enable Bit
    INTCONbits.PEIE  = 1;       // Peripheral Interrupt Enable Bit
    INTCONbits.INTE = 1;        // RB0 Interrupt Enable Bit
    OPTION_REGbits.INTEDG = 1;  // Interrupt Edge Select Bit (from LOW to HIGH)
    
    TRISD0 = 0;
    
    while (1) {}

    return;
}

void interrupt external() {
    if (INTCONbits.INTF == 1) {
        PORTDbits.RD0 = ~PORTDbits.RD0;
        INTCONbits.INTF == 0;
    }
}
