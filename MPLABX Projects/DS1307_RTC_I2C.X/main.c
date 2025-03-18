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

#define DS1307_ADDRESS 0xD0

#define second 0x00
#define minute 0x01
#define hour   0x02
#define day    0x03
#define date   0x04
#define month  0x05
#define year   0x06
#define ctrl   0x07

unsigned char _sec, _min, _hour, _day, _date, _month, _year, _conf;

void lcd_init();
void lcd_data(unsigned char data);
void lcd_word(const unsigned char *str, unsigned char len);
void lcd_command(unsigned char cmd);

char decimal_to_bcd(unsigned char decimal);
void bcd_to_ascii(unsigned char bcd);

void DS1307_write(char _sec, char _min, char _hour, char _day, char _date, char _month, char _year);
void DS1307_read(char slave_address, char register_address);

void main(void) {
    TRISC = 0xFF;
    
    SSPADD = 49;
    SSPCON = 0x28;
    
    TRISD = 0x00;
    PORTD = 0x00;
    TRISB = 0x00;
    PORTB = 0x00;
    
    lcd_init();
    
    lcd_command(0x80);
    lcd_word("CLOCK:", 6);
    lcd_command(0xC0);
    lcd_word("DATE:", 5);
    DS1307_write(0, 0, 11, 2, 18, 3, 25);
    __delay_ms(300);
    
    while (1) {
        __delay_ms(20);
        DS1307_read(DS1307_ADDRESS, 0);
        
        lcd_command(0x88);
        bcd_to_ascii(_hour);
        lcd_data(':');
        bcd_to_ascii(_min);
        lcd_data(':');
        bcd_to_ascii(_sec);
        
        lcd_command(0xC8);
        bcd_to_ascii(_date);
        lcd_data('/');
        bcd_to_ascii(_month);
        lcd_data('/');
        bcd_to_ascii(_year);
    }

    return;
}

void lcd_init() {
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
void lcd_word(const unsigned char *str, unsigned char len) {
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

char decimal_to_bcd(unsigned char decimal) {
    unsigned char msb, lsb, hex;
    msb = decimal / 10;
    lsb = decimal % 10;
    hex = ((msb << 4) + lsb);
    return hex;
}
void bcd_to_ascii(unsigned char bcd) {
    unsigned char value;
    
    value = bcd;
    value = (value & 0xF0) >> 4;
    value = value | 0x30;
    lcd_data(value);
    
    value = bcd;
    value = (value & 0x0F);
    value = value | 0x30;
    lcd_data(value);
}

void DS1307_write(char _sec, char _min, char _hour, char _day, char _date, char _month, char _year) {
    /* START BIT */
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN);
    PIR1bits.SSPIF = 0;
    
    /* SLAVE ADDRESS BITS */
    SSPBUF = DS1307_ADDRESS;
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    if (SSPCON2bits.ACKSTAT) {
        SSPCON2bits.PEN = 1;
        while (SSPCON2bits.PEN);
        return;
    }
    
    /* REGISTER TO WRITE TO */
    SSPBUF = second;
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    if (SSPCON2bits.ACKSTAT) {
        SSPCON2bits.PEN = 1;
        while (SSPCON2bits.PEN);
        return;
    }
    
    SSPBUF = decimal_to_bcd(_sec);
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    
    SSPBUF = decimal_to_bcd(_min);
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    
    SSPBUF = decimal_to_bcd(_hour);
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    
    SSPBUF = decimal_to_bcd(_day);
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    
    SSPBUF = decimal_to_bcd(_date);
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    
    SSPBUF = decimal_to_bcd(_month);
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    
    SSPBUF = decimal_to_bcd(_year);
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    
    SSPBUF = 0x00;
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    
    /* STOP BIT */
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN);
    PIR1bits.SSPIF = 0;
}
void DS1307_read(char slave_address, char register_address) {
    /* START BIT */
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN);
    PIR1bits.SSPIF = 0;
    
    /* SLAVE ADDRESS BITS */
    SSPBUF = slave_address;
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    if (SSPCON2bits.ACKSTAT) {
        SSPCON2bits.PEN = 1;
        while (SSPCON2bits.PEN);
        return;
    }
    
    /* REGISTER TO READ FROM */
    SSPBUF = register_address;
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    if (SSPCON2bits.ACKSTAT) {
        SSPCON2bits.PEN = 1;
        while (SSPCON2bits.PEN);
        return;
    }
    
    /* REPEATED START BIT */
    SSPCON2bits.RSEN = 1;
    while (SSPCON2bits.RSEN);
    PIR1bits.SSPIF = 0;
    
    /* SLAVE ADDRESS BITS */
    SSPBUF = slave_address + 1;
    while (!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    if (SSPCON2bits.ACKSTAT) {
        SSPCON2bits.PEN = 1;
        while (SSPCON2bits.PEN);
        return;
    }
    
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    _sec = SSPBUF;
    
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    _min = SSPBUF;
    
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    _hour = SSPBUF;
    
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    _day = SSPBUF;
    
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    _date = SSPBUF;
    
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    _month = SSPBUF;
    
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    _year = SSPBUF;
    
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    _conf = SSPBUF;
    
    SSPCON2bits.ACKDT = 1;
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN);
}
