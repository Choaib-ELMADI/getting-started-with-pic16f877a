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

#define RS PORTCbits.RC5
#define RW PORTCbits.RC6
#define EN PORTCbits.RC7

unsigned int valeurADC;
float tension;
unsigned char colorIndex;
const char* colors[4] = {"White", "Rose ", "Blue ", "Black"};
int numbers[4] = {0, 0, 0, 0};

void ADC_Init(void);
void lcd_initialize(void);
void lcd_data(unsigned char);
void lcd_string(const char *);
void lcd_command(unsigned char);
void __interrupt() InterruptRoutine(void);

void main(void) {
    OPTION_REG = 0x40;  // 0b01000000
    INTCON = 0xD0;      // 0b11010000
    ADCON0 = 0xC1;      // 0b11000001
    ADCON1 = 0x8E;      // 0b10001110
    PIE1bits.ADIE = 1;
    TRISBbits.TRISB1 = 1;
    
    TRISD = 0x00;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    
    lcd_initialize();
    ADC_Init();
    
    while (1) {
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE);
        
        if (PORTBbits.RB1 == 1) {
            __delay_ms(50);
            if (PORTBbits.RB1 == 1) {
                lcd_command(0x01);        
                numbers[colorIndex] = numbers[colorIndex] + 1;
                if (numbers[colorIndex] > 100) numbers[colorIndex] = 0;
            }
        }
        
        lcd_command(0x80);
        lcd_string("Color: ");
        lcd_string(colors[colorIndex]);
        lcd_command(0xC0);
        lcd_string("Number: ");
        int a = numbers[colorIndex] / 10;
        int b = numbers[colorIndex] % 10;
        lcd_data(a + '0');
        lcd_data(b + '0');
        
        __delay_ms(50);
    }

    return;
}

void ADC_Init(void) {
    ADCON0 = 0b10000001;
    ADCON1 = 0b10001110;
}

void lcd_initialize() {
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

void __interrupt() InterruptRoutine(void) {
    if (PIR1bits.ADIF == 1) {
        valeurADC = (ADRESH << 8) + ADRESL;
        tension = (5.0 / 1023.0) * valeurADC;
        if (tension >= 0 && tension <= 1.25) colorIndex = 0;
        else if (tension > 1.25 && tension <= 2.5) colorIndex = 1;
        else if (tension > 2.5 && tension  <= 3.75) colorIndex = 2;
        else colorIndex = 3;
        PIR1bits.ADIF = 0;
    }
    
    /* if (INTF == 1) {
        lcd_command(0x01);        
        numbers[colorIndex] = numbers[colorIndex] + 1;
        INTF = 0;
    } */
}
