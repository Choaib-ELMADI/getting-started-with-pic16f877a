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

unsigned char byte;

void lcd_initialize(void);
void lcd_data(unsigned char);
void lcd_string(const char *);
void lcd_command(unsigned char);

void writeByteToEE(unsigned char, const unsigned char);
void readByteFromEE(const unsigned char);

void main(void) {
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISD = 0x00;

    lcd_initialize();
    lcd_command(0x82);
    lcd_string("EEPROM DATA:");
    
    while (1) {
        writeByteToEE(2, 0x0A);
        readByteFromEE(0x0A);
        lcd_command(0xC8);
        lcd_data(byte + '0');
        __delay_ms(250);
        
        writeByteToEE(4, 0x0A);
        readByteFromEE(0x0A);
        lcd_command(0xC8);
        lcd_data(byte + '0');
        __delay_ms(250);
        
        writeByteToEE(6, 0x0A);
        readByteFromEE(0x0A);
        lcd_command(0xC8);
        lcd_data(byte + '0');
        __delay_ms(250);
        
        writeByteToEE(8, 0x0A);
        readByteFromEE(0x0A);
        lcd_command(0xC8);
        lcd_data(byte + '0');
        __delay_ms(250);
    }
    
    return;
}

void lcd_initialize(void) {
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0C);
    lcd_command(0x01);
}

void lcd_data(unsigned char data) {
    RS = 1;
    RW = 0;
    EN = 1;
    PORTD = data;
    __delay_ms(2);
    EN = 0;
}

void lcd_string(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

void lcd_command(unsigned char cmd) {
    RS = 0;
    RW = 0;
    EN = 1;
    PORTD = cmd;
    __delay_ms(2);
    EN = 0;
}

void writeByteToEE(unsigned char data, const unsigned char address) {
    EEADR = address;
    EEDATA = data;
    EECON1bits.EEPGD = 0;       // Access Data Memory
    EECON1bits.WREN = 1;        // Enable Writing
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;          // Initiate the Write Cycle
    while (PIR2bits.EEIF == 0); // Wait tell Write is Done
    PIR2bits.EEIF = 0;          // Reset Flag
}

void readByteFromEE(const unsigned char address) {
    EEADR = address;
    EECON1bits.EEPGD = 0;       // Access Data Memory
    EECON1bits.RD = 1;          // Initiate the Read Cycle
    byte = EEDATA;              // Read the Data
}
