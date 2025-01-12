// Saba Razi
// 99521316

#include <mega32.h>
#include <alcd.h>
#include <delay.h>

unsigned int my_hour = 23;
unsigned int my_minute = 58;
unsigned int my_second = 0;
unsigned int my_ms = 0;

unsigned char int_to_char_custom(unsigned int x) {
    return x + '0';
}

void display_on_lcd(int value, int column) {
    unsigned int row = 1;
    unsigned char tens = int_to_char_custom(value / 10);
    unsigned char ones = int_to_char_custom(value % 10);
    lcd_gotoxy(column, row);
    lcd_putchar(tens);
    lcd_gotoxy(column + 1, row);
    lcd_putchar(ones);
}

interrupt [TIM1_COMPA] void timer1_compa_isr_custom(void) {
    my_ms += 1;

    if (my_ms == 10) {
        my_ms = 0;
        my_second += 1;

        if (my_second == 60) {
            my_second = 0;
            my_minute += 1;

            if (my_minute == 60) {
                my_minute = 0;
                my_hour += 1;

                if (my_hour == 24) {
                    my_hour = 0;
                }
            }
        }
    }
}

void main(void) {
    PORTA=0x00;
    DDRA=0x00;
    PORTB=0x00;
    DDRB=0x00;
    PORTC=0x00;
    DDRC=0x00;
    PORTD=0x00;
    DDRD=0x00;

    TCCR1A = 0x00;
    TCCR1B = 0x0C;
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    ICR1H = 0x00;
    ICR1L = 0x00;
    OCR1AH = 0x0C;
    OCR1AL = 0x35;
    OCR1BH = 0x00;
    OCR1BL = 0x00;
    TIMSK = 0x12;

    lcd_init(16);
    lcd_gotoxy(4, 0);
    lcd_puts("LCD Clock");

    #asm("sei")

    while (1) {
        display_on_lcd(my_hour, 3);
        lcd_gotoxy(5, 1);
        lcd_puts(":");

        display_on_lcd(my_minute, 6);
        lcd_gotoxy(8, 1);
        lcd_puts(":");

        display_on_lcd(my_second, 9);
        lcd_gotoxy(11, 1);
        lcd_puts(":");

        lcd_gotoxy(12, 1);
        lcd_putchar(int_to_char_custom(my_ms));
    }
}
