// Saba Razi
// 99521316
#include <mega32.h>
#include <delay.h>

unsigned char Lines = 72;
const unsigned char image_code[Lines] = {
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    
    0xFF,    //    0007        # # # # # # # # 
    0xF6,    //    0001        # # # # . # # . 
    0xF6,    //    0002        # # # # . # # . 
    0xF6,    //    0003        # # # # . # # . 
    0xF6,    //    0004        # # # # . # # . 
    0x80,    //    0005        # . . . . . . . 
    0xFF,    //    0006        # # # # # # # # 
    
    0xFF,    //    0007        # # # # # # # # 
    0xB6,    //    0008        # . # # . # # . 
    0xB6,    //    0009        # . # # . # # . 
    0xB6,    //    000A        # . # # . # # . 
    0xB6,    //    000B        # . # # . # # . 
    0x80,    //    000C        # . . . . . . . 
    0xFF,    //    000D        # # # # # # # # 
    
    0xFF,    //    000E        # # # # # # # # 
    0xE3,    //    000F        # # # . . . # # 
    0xDD,    //    0010        # # . # # # . # 
    0xBE,    //    0011        # . # # # # # . 
    0x80,    //    0012        # . . . . . . . 
    0xFF,    //    0013        # # # # # # # # 
    
    0xFF,    //    0014        # # # # # # # # 
    0xBE,    //    0015        # . # # # # # . 
    0xBE,    //    0016        # . # # # # # . 
    0xBE,    //    0017        # . # # # # # . 
    0xBE,    //    0018        # . # # # # # . 
    0xC1,    //    0019        # # . . . . . # 
    0xFF,    //    001A        # # # # # # # # 
    
    0xFF,    //    001B        # # # # # # # # 
    0xC9,    //    001C        # # . . # . . # 
    0xB6,    //    001D        # . # # . # # . 
    0xBE,    //    001E        # . # # # # # . 
    0x80,    //    001F        # . . . . . . . 
    0xFF,    //    0020        # # # # # # # # 
    
    0xFF,    //    0021        # # # # # # # # 
    0x9F,    //    0022        # . . # # # # # 
    0xE7,    //    0023        # # # . . # # # 
    0xE9,    //    0024        # # # . # . . # 
    0xEE,    //    0025        # # # . # # # . 
    0xE9,    //    0026        # # # . # . . # 
    0xE7,    //    0027        # # # . . # # # 
    0x9F,    //    0028        # . . # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //    0029        # # # # # # # # 
    0xFF,    //	0029		# # # # # # # # 
	0xFF,	//	0029		# # # # # # # # 
	0xFF,	//	0029		# # # # # # # #  
};



void main(void) {
    unsigned char hold, Col, Refresh, Index, S;
    unsigned char first = 8;
    
    DDRC = 0xFF;
    PORTC = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;
    DDRB = 0xFF;
    PORTB = 0x00;
             
    while (1) {
        for (S = first; S < Lines - first + 1; S++) {
            for (Refresh = 0; Refresh < 4; Refresh++) {
                hold = 0b00000001;
                for (Col = 0; Col < 8; Col++) {
                    Index = S - Col;
                    
                    PORTD = hold;
                    PORTC = image_code[Index + 8];
                    delay_ms(2);
                    PORTD = 0x00;
                    
                    PORTB = hold;
                    PORTC = image_code[Index];
                    delay_ms(2);
                    PORTB = 0x00;
                    
                    hold = hold << 1;
                }
            }
        }
    };
}