/*
 * led1.c
 *
 * Created: 2022-06-17 오전 11:46:37
 *  Author: pknu
 */

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	//DDRA = 0xFF; //portA를 출력으로 설정 0b 1111 1111
	//DDRB = 0xFF;
	//DDRC = 0xFF;
	//DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	//DDRG = 0xFF;	
	while (1)
	{
		PORTE = 0x00; // PORTA의 각 비트에 5V 출력 0 0000
		_delay_ms(1000);
		PORTE = 0xFF;
		_delay_ms(1000);
	}
	
	return 0;
} 
