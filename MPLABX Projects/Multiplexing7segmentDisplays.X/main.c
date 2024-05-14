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
int num = 56;
int i, j;

void main(void) {
    TRISC = 0x00;
    TRISB = 0x00;
    i = 56 % 10;
    j = 56 / 10;
    
    while (1) {
        PORTCbits.RC0 = SEGMENT_ON;
        PORTCbits.RC1 = SEGMENT_OFF;
        PORTB = numbers[i];
        __delay_ms(10);
        PORTCbits.RC0 = SEGMENT_OFF;
        PORTCbits.RC1 = SEGMENT_ON;
        PORTB = numbers[j];
        __delay_ms(10);
    }
    
    return;
}
