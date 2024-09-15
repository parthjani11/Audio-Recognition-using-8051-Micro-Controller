#include<reg51.h>
#define lcd P3

sbit SOUND = P1^0;

sbit rs = P2^0; //register select
sbit rw = P2^1; //RW
sbit en = P2^2; //enable

unsigned int count = 0; // Global counter variable

void lcd_init();
void cmd(unsigned char);
void dat(unsigned char);
void delay();
void lcd_string(char *s);

void main()
{
    lcd_init();
    while(1)
    {
        if(SOUND == 0)
        {
            cmd(0xc0); // Move to the second line
            lcd_string("                "); // Clear the line
            count = 0; // Reset count when no sound
        }
        else
        {
            
					
					count++; // Increment count on sound detection
            cmd(0xc0); // Move to the second line
            lcd_string("Count: "); // Display label
            cmd(0xc7); // Move cursor to the count position
            dat((count/100) + '0'); // Display hundreds digit
            dat(((count/10) % 10) + '0'); // Display tens digit
            dat((count % 10) + '0'); // Display ones digit
            delay();
        }
    }
}

void lcd_init()
{
    cmd(0x38);
    cmd(0x0e);
    cmd(0x06);
    cmd(0x01);
    cmd(0x80);
}

void cmd(unsigned char a)
{
    lcd = a;
    rs = 0;
    rw = 0;
    en = 1;
    delay();
    en = 0;
}

void dat(unsigned char b)
{
    lcd = b;
    rs = 1;
    rw = 0;
    en = 1;
    delay();
    en = 0;
}

void lcd_string(char *s)
{
    while(*s)
    {
       dat(*s++);
     }
}

void delay()
{
    unsigned int i;
    for(i = 0; i < 20000; i++);
}
