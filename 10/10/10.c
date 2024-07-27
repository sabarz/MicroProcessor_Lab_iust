// Saba Razi
// 99521316

#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>

signed char a = 0;

interrupt [EXT_INT0] void ext_int0_isr(void) {
	if (PORTC.3 == 0) {
		a += 1;
	}
	else {
		a += 10;
	}
}

interrupt [EXT_INT1] void ext_int1_isr(void) {
	if (PORTC.3 == 0) {
		a -= 1;
	}
	else {
		a -= 10;
	}
}

interrupt [EXT_INT2] void ext_int2_isr(void) {
	PORTC = PORTC ^ (1<<3);
}

void main(void) {
	char *str = 0;
	
	PORTC = 0x00;
	DDRC = 0x08;

	GICR |= 0xE0;
    MCUCR = 0x0A;
    MCUCSR = 0x00;
    GIFR = 0xE0;

    lcd_init(16);
    #asm("sei")

    while (1) {
        lcd_gotoxy(0, 0);
        itoa(a, str);
        lcd_puts(str);
        lcd_putchar(' ');
        lcd_putchar(' ');
        delay_ms(50);
    }
}
