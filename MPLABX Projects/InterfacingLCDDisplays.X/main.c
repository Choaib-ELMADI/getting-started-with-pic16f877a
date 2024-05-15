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
    TRISD = 0x00;
    lcd_initialize();
    
    while (1) {
        lcd_command(0x83); // 1st Row, 3rd Column
        lcd_string("HELLO FROM", 10);
        lcd_command(0xC2); // 2nd Row, 2nd Column
        lcd_string("PIC 16F877A", 11);
    }

    return;
}

void lcd_initialize() {
    lcd_command(0x38); // Setup 16X2 LCD Model
    lcd_command(0x06); // Auto Increment Cursor to Next Element
    lcd_command(0x0C); // LCD ON, Cursor OFF
    lcd_command(0x01); // Clear Screen
}

void lcd_data(unsigned char data) {
    PORTD = data;
    RS = 1;     // Data Register
    RW = 0;     // Write
    EN = 1;     // Enabled
    __delay_ms(5);
    EN = 0;     // Disabled
}

void lcd_string(const unsigned char *str, unsigned char len) {
    unsigned char i;
    for (i=0; i<len; ++i) {
        lcd_data(str[i]);
    }
}

void lcd_command(unsigned char cmd) {
    PORTD = cmd;
    RS = 0;     // Instruction Register
    RW = 0;     // Write
    EN = 1;     // Enabled
    __delay_ms(5);
    EN = 0;     // Disabled
}
