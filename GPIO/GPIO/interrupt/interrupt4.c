/*
 * interrupt4.c
 *
 * Created: 2022-06-20 오전 11:45:10
 *  Author: pknu
 */ 

// #### 인터럽트로 LED의 좌우 이동 방향 변경하기 ####

#define F_CPU 7432800UL
#include <avr/io.h>	//AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>	//AVR 인터럽트에 대한 헤더파일
#include <util/delay.h>	//delay 함수사용을 위한 헤더파일

volatile unsigned char Shift_flag = 1;

int main(void)
{
	unsigned char LED_Data = 0x01;
	
	DDRC = 0x0f;	//포트C를 출력포트로 설정
	DDRE = 0x00;	//포트E를 입력포트로 설정
	
	//인터럽트 5를 하강에지, 7을 상승에지에서 동작하도록 설정
	EICRB = 0xc8;
	
	EIMSK = 0xa0;	//인터럽트 5, 7을 허용
	EIFR = 0xa0;	//인터럽트 5, 7 플래그를 클리어
	
	sei();	//전체 인터럽트를 허용
	
	while (1)
	{
		//포트C로 변수 LED_Data에 있는 데이타를 출력
		PORTC = LED_Data;
		if(Shift_flag == 1)	//LED0 ~ LED3으로 이동  (0,1,2,3)
		{
			if(LED_Data == 0x08)
				LED_Data = 0x01;
			else //LED_Data 값을 왼쪽으로 쉬프트
				LED_Data <<= 1;
		}
		else if(Shift_flag == 2) //LED3 ~ LED0으로 이동 (3,2,1,0)
		{
			if (LED_Data == 0x01)
			{
				LED_Data = 0x08;
			} 
			else //LED_Data 값을 오른쪽으로 쉬프트
			{
				LED_Data >>= 1;
			}
		}
		_delay_ms(100);
	}
}

SIGNAL(INT5_vect)	//인터럽트 서비스 루틴
{
	cli(); //!!전체 인터럽트를 금지
	Shift_flag = 1; //Shift_flag에 1을 입력
	sei(); //!!전체 인터럽트를 허용
}

SIGNAL(INT7_vect)  //인터럽트 서비스 루틴
{
	cli(); //!!전체 인터럽트를 금지
	Shift_flag = 2; //Shift_flag에 2를 입력
	sei(); //!!전체 인터럽트를 허용
}