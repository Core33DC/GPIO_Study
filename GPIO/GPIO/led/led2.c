/*
 * led2.c
 *
 * Created: 2022-06-17 오후 1:54:30
 *  Author: pknu
 */ 
#define  F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char LED_Data = 0x00;
	DDRA = 0x0F;
		
	while (1)
	{
		//PORTA = 0x01;
		//_delay_ms(1500);
		//PORTA = 0x02;
		//_delay_ms(1500);
		//PORTA = 0x04;
		//_delay_ms(1500);
		//PORTA = 0x08;
		//_delay_ms(1500);
		//LED_Data = 0x0F;
		//
		//for (i=0; i<8; i++)
		//{
			//PORTA = LED_Data;
			//LED_Data <<= 1;
			//_delay_ms(1000);
		//}
		
		PORTA = LED_Data;
		LED_Data++;
		
		if(LED_Data > 0x0F)
			LED_Data = 0;
			_delay_ms(1000);
				
	}
	
	return 0;
}