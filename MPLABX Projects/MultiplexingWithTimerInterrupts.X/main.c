#include <xc.h>

#define _XTAL_FREQ 20000000

#define SEGMENT_ON 0
#define SEGMENT_OFF 1

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

unsigned char numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned char counter = 0;
char i, j;
unsigned char mode = 0;

void __interrupt() interruptISR();

void main(void) {
    INTCONbits.GIE = 1;         // Global Interrupt Enable Bit
    INTCONbits.PEIE = 1;        // Peripheral Interrupt Enable Bit
    
    /*   TIMER 0 BITS CONFIGURATION   */
    INTCONbits.TMR0IE = 1;      // TMRO Interrupt Enable Bit
    OPTION_REG = 0x07;          // ==> 0b00000111 prescalar is 256
    TMR0 = 59;                  // 10ms delay
    
    TRISD = 0x00;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    
    while (1) {
        i = counter / 10;
        j = counter % 10;
        ++counter;
        if (counter > 99) counter = 0;
        __delay_ms(500);
    }

    return;
}

void __interrupt() interruptISR() {
    if (INTCONbits.TMR0IF == 1) {
        if (mode == 0) {
            PORTCbits.RC6 = SEGMENT_ON;
            PORTCbits.RC7 = SEGMENT_OFF;
            PORTD = numbers[j];
        } else {
            PORTCbits.RC6 = SEGMENT_OFF;
            PORTCbits.RC7 = SEGMENT_ON;
            PORTD = numbers[i];
        }
        mode = ~mode;
        
        INTCONbits.TMR0IF = 0;
    }
}
