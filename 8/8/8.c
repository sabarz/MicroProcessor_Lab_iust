// Saba Razi
// 99521316

#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>

#define KEYPAD_ROW1 PORTD.0
#define KEYPAD_ROW2 PORTD.1
#define KEYPAD_ROW3 PORTD.2
#define KEYPAD_ROW4 PORTD.3
#define KEYPAD_COL1 PIND.4
#define KEYPAD_COL2 PIND.5
#define KEYPAD_COL3 PIND.6
#define KEYPAD_COL4 PIND.7

#define KEYPAD_NUM0 0
#define KEYPAD_NUM1 1
#define KEYPAD_NUM2 2
#define KEYPAD_NUM3 3
#define KEYPAD_NUM4 4
#define KEYPAD_NUM5 5
#define KEYPAD_NUM6 6
#define KEYPAD_NUM7 7
#define KEYPAD_NUM8 8
#define KEYPAD_NUM9 9
#define KEYPAD_DIV  10
#define KEYPAD_MUL  11
#define KEYPAD_ADD  12
#define KEYPAD_SUB  13
#define KEYPAD_EQ   14
#define KEYPAD_CLR  15

float operands[2];
char operator;
int operandIndex = 0;
char output_text[5];

void main(void) {
    unsigned char key_result;
    DDRC = 0xFF;
    DDRD = 0x0F;
    PORTC = 0x00;

    lcd_init(16);
    lcd_clear();
    lcd_gotoxy(1, 0);
    lcd_puts("KEYPAD AND LCD");
    lcd_gotoxy(5, 1);
    lcd_puts("PROJECT");
    delay_ms(2000);
    lcd_clear();

    while (1) {
        key_result = keypadScan();
        
        if (key_result != 255) {
            while (keypadScan() != 255);
            delay_ms(20);
            
            if (key_result == KEYPAD_DIV) {
                lcd_putchar('/');
                operandIndex++;
                operator = '/';
            }
            else if (key_result == KEYPAD_MUL) {
                lcd_putchar('*');
                operandIndex++;
                operator = '*';
            }
            else if (key_result == KEYPAD_SUB) {
                lcd_putchar('-');
                operandIndex++;
                operator = '-';
            }
            else if (key_result == KEYPAD_ADD) {
                lcd_putchar('+');
                operandIndex++;
                operator = '+';
            }
            else if (key_result == KEYPAD_EQ) {
                lcd_putchar('=');
                
                if (operator == '/') operands[1] = operands[0] / operands[1];
                else if (operator == '*') operands[1] = operands[0] * operands[1];
                else if (operator == '-') operands[1] = operands[0] - operands[1];
                else if (operator == '+') operands[1] = operands[0] + operands[1];
                
                ftoa(operands[1], 2, output_text);
                lcd_puts(output_text);
            }
            else if (key_result == KEYPAD_CLR) {
                lcd_clear();
                lcd_gotoxy(0, 0);
                operands[1] = 0;
                operands[0] = 0;
                operator = '\0';
                operandIndex = 0;
            }
            else {
                lcd_putchar(key_result + 48);
                operands[operandIndex] *= 10;
                operands[operandIndex] += key_result;
            }
        }
    }
}

unsigned char keypadScan() {
    unsigned char result = 255;

    KEYPAD_ROW1 = 1;
    KEYPAD_ROW2 = 0;
    KEYPAD_ROW3 = 0;
    KEYPAD_ROW4 = 0;
    
    delay_ms(5);
    if (KEYPAD_COL1) result = KEYPAD_NUM7;
    else if (KEYPAD_COL2) result = KEYPAD_NUM8;
    else if (KEYPAD_COL3) result = KEYPAD_NUM9;
    else if (KEYPAD_COL4) result = KEYPAD_DIV;

    KEYPAD_ROW1 = 0;
    KEYPAD_ROW2 = 1;
    KEYPAD_ROW3 = 0;
    KEYPAD_ROW4 = 0;
    
    delay_ms(5);
    if (KEYPAD_COL1) result = KEYPAD_NUM4;
    else if (KEYPAD_COL2) result = KEYPAD_NUM5;
    else if (KEYPAD_COL3) result = KEYPAD_NUM6;
    else if (KEYPAD_COL4) result = KEYPAD_MUL;

    KEYPAD_ROW1 = 0;
    KEYPAD_ROW2 = 0;
    KEYPAD_ROW3 = 1;
    KEYPAD_ROW4 = 0;
    
    delay_ms(5);
    if (KEYPAD_COL1) result = KEYPAD_NUM1;
    else if (KEYPAD_COL2) result = KEYPAD_NUM2;
    else if (KEYPAD_COL3) result = KEYPAD_NUM3;
    else if (KEYPAD_COL4) result = KEYPAD_SUB;

    KEYPAD_ROW1 = 0;
    KEYPAD_ROW2 = 0;
    KEYPAD_ROW3 = 0;
    KEYPAD_ROW4 = 1;
    
    delay_ms(5);
    if (KEYPAD_COL1) result = KEYPAD_CLR;
    else if (KEYPAD_COL2) result = KEYPAD_NUM0;
    else if (KEYPAD_COL3) result = KEYPAD_EQ;
    else if (KEYPAD_COL4) result = KEYPAD_ADD;

    return result;
}
