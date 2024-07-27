

#include <mega32.h>
#include <delay.h>

const unsigned char image_code[50]=
{
        0xff,
    0xff,
    0xff,
    0xff,
    0x80,
    0xb6,
    0xb6,
    0xb6,
    
    0xff,
    0xff,
    0xff,
    0xff,
    0xc1,
    0xdd,
    0xdd,
    0xc1,
    
    
    0xff,
    0xff,
    0xff,
    0xff,
    0x80,
    0xf7,
    0xf7,
    0xf0,
    
    0xff,
    0xff,
    0xff,
    0xff,
    0x80,
    0xff,
    0xff,
    0xff
    
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,  
    0xFF,  
    0xFF,   
    0xFF,    
    0xFF,    
    0xFF,    
};

void main(void)
{


DDRA=(0<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);


while (1)
      {
      unsigned int i, j = 18;
      for (; j < 18 + 35; j++) {
            int repeat = 0;
            for (; repeat < 5; repeat++) {
                unsigned long scan = 1<<8;
                for (i = 0; i < 7; i++) { 
                    PORTB = scan & 0xff;
                    PORTA = image_code[(j + i) % 35];
                    scan >>= 1;                           
                    delay_ms(2);
                }
            }      
      }
      
      }
}
