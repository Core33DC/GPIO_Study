/*
 * fnd.c
 *
 * Created: 2022-06-17 오후 4:21:32
 *  Author: pknu
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRD = 0x00;  //포트 D 입력으로 설정
	DDRA = 0xFF;
	
	while(1){
		//PORTA = 0x3f;  //0b 0011 1111
		//_delay_ms(1000);
		//PORTA = 0x06;
		//_delay_ms(1000);
		//PORTA = 0x5b;
		//_delay_ms(1000);
		//PORTA = 0x4f;
		//_delay_ms(1000);
		//PORTA = 0x66;
		//_delay_ms(1000);
		//PORTA = 0x6d;
		//_delay_ms(1000);
		//PORTA = 0x7d;
		//_delay_ms(1000);
		//PORTA = 0x27;
		//_delay_ms(1000);
		//PORTA = 0x7f;
		//_delay_ms(1000);
		//PORTA = 0x6f;
		//_delay_ms(1000);
		
		if(PIND == 0x01)  //0
		{
			PORTA = 0x3f;
			_delay_ms(300);
			PORTA = 0x00;
		}
		
		if(PIND == 0x02)  //1
		{
			PORTA = 0x06;
			_delay_ms(300);
			PORTA = 0x00;
		}
		
		if(PIND == 0x04)  //2
		{
			PORTA = 0x5b;
			_delay_ms(300);
			PORTA = 0x00;
		}
		
		if(PIND == 0x08)  //3
		{
			PORTA = 0x4f;
			_delay_ms(300);
			PORTA = 0x00;
		}
		
		if(PIND == 0x10)  //4
		{
			PORTA = 0x66;
			_delay_ms(300);
			PORTA = 0x00;
		}
		
		if(PIND == 0x20)  //5
		{
			PORTA = 0x6d;
			_delay_ms(300);
			PORTA = 0x00;
		}
		
		if(PIND == 0x40) //6
		{
			PORTA = 0x7d;
			_delay_ms(300);
			PORTA = 0x00;
		}
		
		if(PIND == 0x80) //7
		{
			PORTA = 0x27;
			_delay_ms(300);
			PORTA = 0x00;
		}
	}
	
	return 0;
}