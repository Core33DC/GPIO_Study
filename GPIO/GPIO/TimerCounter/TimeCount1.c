/*
 * TimeCount1.c
 *
 * Created: 2022-06-21 오후 4:01:26
 *  Author: pknu
 */ 


// #### 타이머로 0.5초마다 LED 점멸 ####


#define F_CPU 7432800UL
#include <avr/io.h>	//AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>	//AVR 인터럽트에 대한 헤더 파일

volatile unsigned char LED_Data = 0x01;
unsigned char timer2Cnt = 0, Shift_Flag = 0;

SIGNAL(TIMER2_OVF_vect);	//Timer2 Overflow0 ISP

int main(void)
{
	DDRC = 0x0f; //포트C를 출력포트로 설정!! 4bit는 0x0f, 8bit를 원하면 0xff로 설정한다.
	
	TCCR2 = 0x05; //프리스케일러 1024로 설정
	// 256-72=184 -> 0.1초마다 한번씩 인터럽트 발생
	TCNT0 = 184;
	
	TIMSK = 0x40;
	TIFR |= 1 << TOV2;
	sei();
	
	while (1)
	{
		PORTC = LED_Data;	//포트 C로 변수 LED_Data에 있는 데이터 출력
	}
	return 0;
}

//타이머 오버플로우 인터럽트
SIGNAL(TIMER2_OVF_vect)
{
	cli();
	TCNT2 = 184;	// 256 - 72 = 184 -> 0.01초 마다 한번씩 인터럽트 발생
	timer2Cnt++;	//timer2Cnt 변수를 1 증가
	
	// 0.01s * 50 = 0.5s, 0.5초를 얻기 위한 카운트 횟수
	if (timer2Cnt == 50)
	{
		if(Shift_Flag == 0)
		{
			//LED0 ~ LED3을 이동
			LED_Data <<= 1;	//LED_Data 변수를 좌측으로 쉬프트
			if(LED_Data == 0x08) //LED3으로 이동하면!! //8bit까지 쓰고싶으면 0x80으로 바꿔주깅
				Shift_Flag = 1;	 //우측으로 쉬프트하도록 설정
		}
		else
		{
			//LED3 ~ LED0으로 이동
			LED_Data >>= 1;	 //LED_Data 변수를 우측으로 쉬프트
			if(LED_Data == 0x01)  //LED0으로 이동하면
				Shift_Flag = 0;	 //좌측으로 쉬프트하도록 설정
		}
		timer2Cnt = 0;
	}
	sei();
}