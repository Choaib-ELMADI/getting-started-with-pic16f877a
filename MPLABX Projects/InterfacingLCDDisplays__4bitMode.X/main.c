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

#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define EN PORTCbits.RC2

void lcd_initialize();
void lcd_data(unsigned char);
void lcd_string(const unsigned char *, unsigned char);
void lcd_command(unsigned char);

void main(void) {
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    
    TRISD4 = 0;
    TRISD5 = 0;
    TRISD6 = 0;
    TRISD7 = 0;
    
    lcd_initialize();
    
    while (1) {
        lcd_command(0x82); // 1st Row, 2nd Column
        lcd_string("HI, IT'S ME", 11);
        lcd_command(0xC1); // 2nd Row, 1st Column
        lcd_string("CHOAIB ELMADI", 13);
    }

    return;
}

void lcd_initialize() {
    lcd_command(0x02); // Return Cursor to Home Position
    lcd_command(0x28); // 4bit Mode 16X2 LCD Model
    lcd_command(0x06); // Auto Increment Cursor to Next Element
    lcd_command(0x0C); // LCD ON, Cursor OFF
    lcd_command(0x01); // Clear Screen
}

void lcd_data(unsigned char data) {
    EN = 1;     // Enabled
    RS = 1;     // Data Register
    RW = 0;     // Write
    PORTD = (data & 0xF0);
    __delay_ms(2);
    EN = 0;     // Disabled
    PORTD = ((data << 4) & 0xF0);
    EN = 1;
    RS = 1;
    RW = 0;
     __delay_ms(2);
    EN = 0;
}

void lcd_string(const unsigned char *str, unsigned char len) {
    unsigned char i;
    for (i=0; i<len; ++i) {
        lcd_data(str[i]);
    }
}

void lcd_command(unsigned char cmd) {
    EN = 1;     // Enabled
    RS = 0;     // Instruction Register
    RW = 0;     // Write
    PORTD = (cmd & 0xF0);
    __delay_ms(2);
    EN = 0;     // Disabled
    PORTD = ((cmd << 4) & 0xF0);
    EN = 1;
    RS = 0;
    RW = 0;
     __delay_ms(2);
    EN = 0;
}
