/*
 * led_3.c
 *
 * Created: 2022-06-23 오후 5:36:02
 *  Author: pknu
 */ 


//#### LED 불이 순차적으로 왔다갔다 점멸 ####


#define F_CPU 7372800UL
#include <avr/io.h>		//AVR 입출력에 대한 헤더파일
#include <util/delay.h>	//delay 함수사용을 위한 헤더파일

int main(void)
{
	unsigned char LED_Data = 0x01, i;
	DDRC = 0x0f;		//포트C를 출력포트로 설정
	
	while(1)
	{
		LED_Data = 0x01;	//변수 LED_Data에 초기값 0x01로 저장
		
		//LED 0 ~ 3으로 이동
		for (i=0; i<4; i++)
		{
			PORTC = LED_Data;	//포트C로 변수 LED_Data에 있는 데이터 출력
			LED_Data <<= 1;
			_delay_ms(1000);
		}
		//LED 3 ~ 0으로 이동
		for (i=0; i<4; i++)
		{
			PORTC = LED_Data;	//포트C로 변수 LED_Data에 있는 데이터 출력
			LED_Data >>= 1;
			_delay_ms(1000);
		}
	}
}