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

#define ROUGE_H PORTCbits.RC7
#define JAUNE_H PORTCbits.RC6
#define VERT_H PORTCbits.RC5

#define ROUGE_V PORTBbits.RB5
#define JAUNE_V PORTBbits.RB6
#define VERT_V PORTBbits.RB7

void main(void) {
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    
    ROUGE_H = 0; JAUNE_H = 0; VERT_H = 0;
    ROUGE_V = 0; JAUNE_V = 0; VERT_V = 0;
    
    while (1) {
        ROUGE_H = 1;
        ROUGE_V = 1;
        __delay_ms(100);
        ROUGE_V = 0;
        VERT_V = 1;
        __delay_ms(400);
        VERT_V = 0;
        JAUNE_V = 1;
        __delay_ms(100);
        JAUNE_V = 0;
        __delay_ms(100);
        ROUGE_H = 0;
        
        ROUGE_V = 1;
        VERT_H = 1;
        __delay_ms(400);
        VERT_H = 0;
        JAUNE_H = 1;
        __delay_ms(100);
        JAUNE_H = 0;
        ROUGE_V = 0;
    }

    return;
}
