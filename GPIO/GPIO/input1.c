/*
 * input1.c
 *
 * Created: 2022-06-17 오후 3:20:36
 *  Author: pknu
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRD = 0x00;   //포트 D 입력으로 설정
	DDRA = 0xFF;   //포트 A 출력으로 설정 " 'F' 'F' " 10의 자리 F를 16진수로 나눠서 생각하고 1의 F는 16진수로 나눠서 생각해야 함 !! 0000 0000 ~ 1111 1111 
	while (1)
	{
		if(PIND == 0x01)
		{
			PORTA = 0x03;
			_delay_ms(300);
			PORTA = 0x00;
		}
	}
	return 0;
}
