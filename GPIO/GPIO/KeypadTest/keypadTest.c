/*
 * keypadTest.c
 *
 * Created: 2022-06-23 오후 4:43:18
 *  Author: pknu
 */ 


#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>


void init_keypad()
{
	DDRA = 0xF8; //0b 1111 1000. 포트 A의 상위 4비트는 출력(Row), 하위 4비트는 입력(Col)
	PORTA = 0x07; //0b 0000 0111
}

unsigned char keyscan()
{
	PORTA = 0x08; //0b 0000 1000
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '1';
	else if((PINA & 0x07) == 0x02) return '2';
	else if((PINA & 0x07) == 0x04) return '3';
	_delay_ms(10);
	
	PORTA = 0x10;		// 0x10
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '4';
	else if((PINA & 0x07) == 0x02) return '5';
	else if((PINA & 0x07) == 0x04) return '6';
	_delay_ms(10);
	
	PORTA = 0x20;		// 0x20
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '7';
	else if((PINA & 0x07) == 0x02) return '8';
	else if((PINA & 0x07) == 0x04) return '9';
	_delay_ms(10);
	
	PORTA = 0x40;		// 0x40
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '*';
	else if((PINA & 0x07) == 0x02) return '0';
	else if((PINA & 0x07) == 0x04) return '#';
	_delay_ms(10);
	
	return 0;
}
int main()
{
	DDRC = 0xFF;
	init_keypad();
	
	while(1){
		unsigned char key = keyscan();
		if(key == '1') PORTC = 0x01;
		if(key == '2') PORTC = 0x02;
		if(key == '3') PORTC = 0x04;
		if(key == '4') PORTC = 0x05;
		if(key == '5') PORTC = 0x06;
		if(key == '6') PORTC = 0x07;
		if(key == '7') PORTC = 0x08;
		if(key == '8') PORTC = 0x09;
		if(key == '9') PORTC = 0x0a;
		if(key == '*') PORTC = 0x10;
		if(key == '0') PORTC = 0xd0;
		if(key == '#') PORTC = 0xff;
	}
	return 0;
}