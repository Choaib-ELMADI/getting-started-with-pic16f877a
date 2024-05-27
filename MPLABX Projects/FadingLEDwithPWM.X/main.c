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

unsigned int i;

void setPwmDutyCycle(unsigned int);

void main(void) {
    T2CON = 0x04;
    CCP1CON = 0x0C;
    PR2 = 0xFF;
            
    while (1) {
        for (i=0; i<=1023; ++i) {
            setPwmDutyCycle(i);
            __delay_ms(2);
        }
        
        __delay_ms(500);
        
        for (i=1023; i>=0; --i) {
            setPwmDutyCycle(i);
            __delay_ms(2);
        }
    }

    return;
}

void setPwmDutyCycle(unsigned int dutyCycle) {
    CCPR1L = (dutyCycle >> 2);
    CCP1CON = (CCP1CON & 0xCF);
    CCP1CON = (CCP1CON | (0x30 & (dutyCycle << 4)));
}
