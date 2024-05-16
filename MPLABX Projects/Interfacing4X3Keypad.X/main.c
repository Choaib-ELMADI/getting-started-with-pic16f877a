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

#define C1 PORTBbits.RB2
#define C2 PORTBbits.RB1
#define C3 PORTBbits.RB0
#define R1 PORTBbits.RB4
#define R2 PORTBbits.RB5
#define R3 PORTBbits.RB6
#define R4 PORTBbits.RB7

#define RS PORTCbits.RC5
#define RW PORTCbits.RC6
#define EN PORTCbits.RC7

void lcd_initialize();
void lcd_data(unsigned char);
void lcd_string(const unsigned char *, unsigned char);
void lcd_command(unsigned char);
void keypad();
void check_active_row();

void main(void) {
    TRISB = 0xF0; // Rows Inputs, Columns Outputs
    
    TRISC5 = 0;
    TRISC6 = 0;
    TRISC7 = 0;
    
    TRISD = 0x00;
    
    lcd_initialize();
    
    lcd_command(0x83);
    lcd_string("4X3 KEYPAD:", 11);
    lcd_command(0xC0);
    
    while (1) {
        keypad();
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
    EN = 1;     // Enabled
    RS = 1;     // Data Register
    RW = 0;     // Write
    PORTD = data;
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
    EN = 1;     // Enabled
    RS = 0;     // Instruction Register
    RW = 0;     // Write
    PORTD = cmd;
    __delay_ms(5);
    EN = 0;     // Disabled
}

void keypad() {
    C1 = 1; C2 = 0; C3 = 0;
    check_active_row("147*");
    
    C1 = 0; C2 = 1; C3 = 0;
    check_active_row("2580");
    
    C1 = 0; C2 = 0; C3 = 1;
    check_active_row("369#");
}

void check_active_row(const unsigned char *str) {
    if (R1) {
        lcd_data(str[0]);
        while (R1) {}
    }
    else if (R2) {
        lcd_data(str[1]);
        while (R2) {}
    }
    else if (R3) {
        lcd_data(str[2]);
        while (R3) {}
    }
    else if (R4) {
        lcd_data(str[3]);
        while (R4) {}
    }
}
