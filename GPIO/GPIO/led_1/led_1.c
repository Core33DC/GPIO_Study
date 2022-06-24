/*
 * CFile1.c
 *
 * Created: 2022-06-23 오전 10:43:03
 *  Author: pknu
 */ 


//#### LED 0,1 이 켜지고 LED 2,3 순차적으로 점등 ####


#define F_CPU 7432800UL
#include <avr/io.h>  //AVR 입출력에 대한 헤더 파일
#include <util/delay.h>  //delay 함수사용을 위한 헤더 파일

int main(void)
{
	while (1)
	{
		DDRC = 0x03;	//LED 0, 1 출력모드, LED 2, 3은 입력모드로 설정
		PORTC = 0x0f;	//LED 0 ~ 3 모두 1로 출력
		_delay_ms(500);	//*ms 시간 지연
		
		PORTC = 0x00;	//LED 0 ~ 3 모두 0으로 출력
		_delay_ms(500);	//*ms 시간 지연
		
		DDRC = 0x0c;	//LED 0, 1 입력모드, LED 2, 3은 출력모드로 설정
		PORTC = 0x0f;	//LED 0 ~ 3 모두 1로 출력
		_delay_ms(500);	//*ms 시간 지연
		
		PORTC = 0x00;	//LED 0 ~ 3 모두 0으로 출력
		_delay_ms(500);	//*ms 시간 지연
	}
}