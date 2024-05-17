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

unsigned int counter = 0;
void __interrupt() timer0ISR(void);

void main(void) {
    INTCONbits.GIE = 1;         // Global Interrupt Enable Bit
    INTCONbits.PEIE = 1;        // Peripheral Interrupt Enable Bit
    INTCONbits.TMR0IE = 1;      // TMRO Interrupt Enable Bit
    
    OPTION_REG = 0x07;          // ==> 0b00000111 prescalar is 256
    TMR0 = 59;                  // 10ms delay
    
    TRISCbits.TRISC0 = 0;
    PORTCbits.RC0 = 0;
    
    while (1) {
        if (counter == 25) {
            PORTCbits.RC0 = ~PORTCbits.RC0;
            counter = 0;
        }
    }

    return;
}

void __interrupt() timer0ISR(void) {
    if (INTCONbits.TMR0IF == 1) {
        ++counter;
        INTCONbits.TMR0IF = 0;
        TMR0 = 59;
    }
}
