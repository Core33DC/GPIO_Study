/*
 * TimeCount16_1.c
 *
 * Created: 2022-06-22 오후 2:15:14
 *  Author: pknu
 */ 


//####			 16 비트	       ####
//#### 타이머를 이용한 디지털 시계 ####


#define F_CPU 7372800UL
#include <avr/io.h>  // AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>  // AVR 인터럽트에 대한 헤더파일

volatile unsigned char LED_Data = 0x00;

int main(void)
{
	DDRC = 0x0f;      //포트C 출력. //0000 1111
	
	TCCR3A = 0x00;  //
	TCCR3B = (1 << CS32) | (1 << CS30 );  //0x05;      // 0000 0101 0 -> 0000 0100 | 0000 0001 ,1024
	
	TCNT3 = 58336; //인터럽트 시작점 65536 - 7200 -> 7200은 분주가 1024니깐 7372800 / 1024 = 7200
	ETIMSK = (1 << TOIE3);   //0x04; 0000 0100
	ETIFR = (1 << TOV3); //0x04;
	
	sei();
	
	while (1)
	{
		PORTC = LED_Data; //포트C로 변수 LED_Data에 있는 데이터 출력
	}
	return 0;
}

SIGNAL(TIMER3_OVF_vect)
{
	cli();
	
	//65536 - 7200 = 58336 -> 1초마다 한번씩 인터럽트 발생함.
	TCNT3 = 58336;
	LED_Data++;		//LED_Data 변수 1 증가
	
	if (LED_Data > 0x0f)  //0000 1111 -> 15
		LED_Data = 0;
	sei();
}