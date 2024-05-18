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
void __interrupt() timerISR(void);

void main(void) {
    INTCONbits.GIE = 1;         // Global Interrupt Enable Bit
    INTCONbits.PEIE = 1;        // Peripheral Interrupt Enable Bit
    
    /*   TIMER 0 BITS CONFIGURATION   */
    // INTCONbits.TMR0IE = 1;      // TMRO Interrupt Enable Bit
    // OPTION_REG = 0x07;          // ==> 0b00000111 prescalar is 256
    // TMR0 = 59;                  // 10ms delay
    
    /*   TIMER 1 BITS CONFIGURATION   */
    PIE1bits.TMR1IE = 1;        // TMR1 Interrupt Enable Bit
    T1CONbits.TMR1ON = 1;       // Turn ON TMR1
    T1CONbits.T1CKPS0 = 1;      // Prescalar 1st Bit is 1
    T1CONbits.T1CKPS1 = 1;      // Prescalar 2nd Bit is 1, ==> Values of 1:8 (for every 8 clock cycles, the timer will increment by one count.)
    T1CONbits.TMR1CS = 0;       // Clock Source Select Bit, ==> Clock Intern
    TMR1H = 0x3D;
    TMR1L = 0x0A;               // 100ms delay
    
    TRISCbits.TRISC0 = 0;
    PORTCbits.RC0 = 0;
    
    while (1) {
        if (counter == 10) {
            PORTCbits.RC0 = ~PORTCbits.RC0;
            counter = 0;
        }
    }

    return;
}

void __interrupt() timerISR(void) {
    /*   TIMER 0   */
    if (INTCONbits.TMR0IF == 1) {
        ++counter;
        INTCONbits.TMR0IF = 0;
        TMR0 = 59;
    }
    
    /*   TIMER 1   */
    if (PIR1bits.TMR1IF == 1) {
        ++counter;
        PIR1bits.TMR1IF = 0;
        TMR1H = 0x3D;
        TMR1L = 0x0A;
    }
}
