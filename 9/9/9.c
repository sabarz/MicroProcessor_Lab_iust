// Saba Razi
// 99521316

#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>

#define CR 0x0D
#define LF 0x0A

void usart_send_string(char *str);

void main(void) {
	unsigned char a;
	unsigned char counter;
    UCSRA = 0x00;
    UCSRB = 0x18;
    UCSRC = 0x86;
    UBRRH = 0x00;
    UBRRL = 0x33;
    
    lcd_init(16);

    while (1) {
        a = getchar();
        putchar(a);
        lcd_putchar(a);
        
        if (a == 'C') {
            lcd_clear();
            putchar(CR);
            putchar(LF);
        }   
                
        else if(a == 'M') {
            putchar(CR);
            putchar(LF);
            lcd_clear();
            lcd_gotoxy(0, 0);
            lcd_puts("Saba Razi");
        }
        
        else if (a == 'N') {
            putchar(CR);
            putchar(LF);
            usart_send_string("Saba Razi");
            putchar(CR);
            putchar(LF);
        }
        
        else if (a == 'c') {
            for (counter = 0; counter < 24; counter++) {
                putchar(CR);
                putchar(LF);
            }
        }

    }
}

void usart_send_string(char *str) {
    unsigned char i;
    for(i = 0; str[i]; i++)
        putchar(str[i]);
}
