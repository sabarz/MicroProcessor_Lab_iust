// saba razi
// 99521316

#include <mega32.h>
#include <alcd.h>
#include <delay.h>

unsigned char convertIntToChar(int x) {
    return x + '0';
}

void displayValueOnLCD(int value, int column) {
    unsigned int row = 1;
    unsigned char tens = convertIntToChar(value / 10);
    unsigned char ones = convertIntToChar(value % 10);
    lcd_gotoxy(column, row);
    lcd_putchar(tens);
    lcd_gotoxy(column + 1, row);
    lcd_putchar(ones);
}

unsigned int readADC(unsigned char adc_input) {
    ADMUX = adc_input | (1<<REFS0); 
    delay_us(10);
    ADCSRA |= (1 << ADSC);
    while ((ADCSRA & (1 << ADIF)) == 0);
    ADCSRA |= (1 << ADIF);
    return ADCW;
}

void main(void) {
    int temperature;
    
    PORTA=0x00;
    DDRA=0x00;
    PORTB=0x00;
    DDRB=0x00;
    PORTC=0x00;
    DDRC=0x00;
    PORTD=0x00;
    DDRD=0x00;
    
    ADMUX |= (1<<MUX0);
    ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
    SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
    
    lcd_init(16);
    
    lcd_gotoxy(3, 0);
    lcd_puts("LM35 Sensor");
    
    lcd_gotoxy(2, 1);
    lcd_puts("Temp :");
    
    lcd_gotoxy(12, 1);
    lcd_putchar(223);
    
    lcd_gotoxy(13, 1);
    lcd_puts("C");
    
    while (1) {
        temperature = readADC(0);
        temperature = temperature * 0.48898;
        displayValueOnLCD(temperature, 9);
        delay_ms(100);
    }
}
