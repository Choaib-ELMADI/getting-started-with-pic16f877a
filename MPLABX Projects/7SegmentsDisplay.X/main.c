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

unsigned char numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int i = 0;


void main(void) {
    TRISB = 0x00;
    
    while (1) {
        for (i=0; i<10; ++i) {
            PORTB = numbers[i];
            __delay_ms(500);
        }
    }
    
    return;
}
