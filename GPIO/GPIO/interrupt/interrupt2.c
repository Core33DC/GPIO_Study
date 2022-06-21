/*
 * interrupt2.c
 *
 * Created: 2022-06-20 오전 10:42:04
 *  Author: pknu
 */

// #### 인터럽트로 LED 점멸 ####
 
#define F_CPU 74328090UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_STOP = 0;

int main(void)
{
	unsigned char LED_Data = 0x01;
	DDRC = 0x0f;  //포트C를 출력포트로 설정
	DDRE = 0x00;  //포트E를 입력포트로 설정 
	EICRB = 0x03; //인터럽트 4를 상승엣지에서 동작하도록 설정
	EIMSK = 0x10; //인터럽트 4를 허용
	EIFR = 0x10;  //인터럽트 4 플래그를 클리어
	sei();
	
	while (1)
	{
		PORTC = LED_Data;
		if(Time_STOP == 0)
		{
			if(LED_Data == 0x08)
				LED_Data = 0x01;  //LED_Data 값이 0x08이면 LED_Data 값을 0x01로 함
			else
				LED_Data <<= 1;  //LED_Data 값을 왼쪽으로 쉬프트
		}
		_delay_ms(100);
	}
}


SIGNAL (INT4_vect)  //인터럽트 서비스 루틴
{
	cli();	// !!전체 인터럽트를 금지!!
	if(Time_STOP == 0) //Time_STOP이 0인 경우
	{				   
		Time_STOP = 1; //Time_STOP에 1을 입력
	}
	else  //Time_STOP 1인 경우
	{
		Time_STOP = 0; //Time_STOP 0을 입력
	}
	sei();  //전체 인터럽트를 허용
}