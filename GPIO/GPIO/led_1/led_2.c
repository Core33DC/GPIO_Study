/*
 * led_2.c
 *
 * Created: 2022-06-23 오후 2:12:47
 *  Author: pknu
 */ 


//#### LED 불이 순차적으로(2진수) 점멸 ####


#define F_CPU 7372800UL
#include <avr/io.h>		//AVR 입출력에 대한 헤더파일
#include <util/delay.h>	//delay 함수사용을 위한 헤더파일

int main(void)
{
	unsigned char LED_Data = 0x00;
	DDRC = 0x0f;		//포트C를 출력포트로 설정
	
	while(1)
	{
		PORTC = LED_Data;	//포트C로 변수 LED_Data에 있는 데이터 출력
		LED_Data++;		//LED_Data값을 1씩 증가
		
		//LED_Data값이 0x0F보다 크면 0으로 초기화
		if(LED_Data > 0x0f)
			LED_Data = 0;
			
		_delay_ms(1000);	// ms 단위의 딜레이 함수
	}
}