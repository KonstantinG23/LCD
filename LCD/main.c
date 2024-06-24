/*
 * LCD.c
 *
 * Created: 17.06.2024 10:32:58
 * Author : User
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define e1 PORTD |= 0b00001000; // установка линии Е в 1
#define e0 PORTD &= 0b11110111; // установка линии Е в 0
#define rs1 PORTD |= 0b00000100; // установка линии Е в 1
#define rs0 PORTD &= 0b11111011; // установка линии Е в 0

void Port_Init(void)
{
	PORTD = 0x00;
	DDRD = 0xFF;
	
}

void sendhalfbyte(unsigned char c)
{
	c<<=4;
	e1;
	_delay_us(50);
	PORTD &= 00001111;
	PORTD |= c;
	e0;
	_delay_us(50);
}

void sendbyte(unsigned char c, unsigned char mode)
{
	if (mode==0) {rs0}
	else {rs1}
	unsigned char hc = 0;
	hc = c >> 4;
	sendhalfbyte(hc); sendhalfbyte(c);	
}

void setpos(unsigned char x, unsigned char y)
{
	char adress;
	adress = (0x40*y + x)|0b00000001;
	sendbyte(adress, 0);
}

void sendchar(unsigned char c)
{
	sendbyte(c, 1);
}

void LCD_Init(void)
{
	_delay_ms(15);
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000, 0);
	_delay_ms(1);
	sendbyte(0b00101100, 0);
	_delay_ms(1);
	sendbyte(0b00100110, 0);
	_delay_ms(1);
}

void clearlcd()
{
	sendbyte(0b00000001, 0);
	_delay_us(1500);
}

int main(void)
{
	
    Port_Init();
	LCD_Init();
	//clearlcd();
	setpos(0, 0);
	sendchar('n');
	sendchar('m');
    while (1) 
    {
		
    }
}

