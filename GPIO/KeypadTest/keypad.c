/*
 * KeypadTest.c
 *
 * Created: 2022-06-23 오후 4:06:03
 * Author : pknu
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	unsigned char key;
    
	DDRA = 0xF8;	// 0b 1111 0000. 포트 A의 상위 4비트는 출력(Row), 하위 4비트는 입력(Col)
	DDRC = 0xFF;
	
    while (1) 
    {
		key = keyScan();
		if(key == '1')
			PORTC = 0x01;
    }
	
	return 0;
}

unsigned char keyScan()
{	
	PORTA = 0xFB;	// 0b 1111 0FFF.
	if(PINA == 0xFE) return '1';
	else if(PINA == 0xFD) return '2';
	else if(PINA == 0xFB) return '3';
	_delay_ms(10);
	
	PORTA = 0xEF;	// 0b 1110 FFFF.
	if(PINA == 0xFE) return '4';
	else if(PINA == 0xFD) return '5';
	else if(PINA == 0xFB) return '6';
	_delay_ms(10);
	
	PORTA = 0xDF;	// 0b 1101 FFFF.
	if(PINA == 0xFE) return '7';
	else if(PINA == 0xFD) return '8';
	else if(PINA == 0xFB) return '9';
	_delay_ms(10);
	
	PORTA = 0xBF;	// 0b 1011 FFFF.
	if(PINA == 0xFE) return '*';
	else if(PINA == 0xFD) return '0';
	else if(PINA == 0xFB) return '#';
	_delay_ms(10);
}