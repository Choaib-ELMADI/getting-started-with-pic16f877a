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

#define RS PORTBbits.RB0
#define RW PORTBbits.RB1
#define EN PORTBbits.RB2

unsigned int adc;
float convertedAdc, temperature;
unsigned int a, b, c, d, e, f;

void lcd_initialize(void);
void lcd_data(unsigned char);
void lcd_string(const unsigned char *, unsigned char);
void lcd_command(unsigned char);
void __interrupt() ADCConversion();

void main(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
    
    ADCON0 = 0x41;
    ADCON1 = 0x8E;
    
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    
    TRISD = 0x00;   
    lcd_initialize();
    
    lcd_command(0x82);
    lcd_string("Temperature: ", 13);
    
    while (1) {
        ADCON0 = ADCON0 | 0x04;             // Set the Go_nDONE Bit
        
        convertedAdc = adc / 2.046;         // 12.2514
        temperature = convertedAdc * 100;   // 1225.14
        a = (int)temperature % 10;          // 5
        b = (int)temperature / 10;          // 122
        c = b % 10;                         // 2
        d = b / 10;                         // 12
        e = d % 10;                         // 2
        f = d / 10;                         // 1
        
        lcd_command(0xC5);
        lcd_data(f + '0');                  // 12,25
        lcd_data(e + '0');
        lcd_data(',');
        lcd_data(c + '0');
        lcd_data(a + '0');
        lcd_data('C');
    }

    return;
}

void lcd_initialize(void) {
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

void __interrupt() ADCConversion() {
    if (PIR1bits.ADIF == 1) {
        adc = ((unsigned int)ADRESH << 8) + ADRESL;
        PIR1bits.ADIF = 0;
    }
}
