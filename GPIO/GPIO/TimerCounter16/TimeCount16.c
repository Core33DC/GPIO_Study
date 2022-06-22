/*
 * TimeCount16.c
 *
 * Created: 2022-06-22 오전 10:18:03
 *  Author: pknu
 */ 


//####					16 비트			        ####
//#### 프리스케일러를 변경하여 타이머로 LED점멸 ####


#define F_CPU 7372800UL 
#include <avr/io.h>  //AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>  //AVR 인터럽트에 대한 헤더 파일

volatile unsigned char LED_Data = 0x00;
unsigned char timer1Cnt = 0;

int main(void)
{
	DDRC = 0x0f;	//포트C를 출력포트로 설정. //0000 1111
	
	TCCR1A = 0x00;
	TCCR1B = (1 << CS12);	//0x01; 프리스케일러 1 이었지만 256분주로 바꿔준다.	//프리스케일러 1 -> 클럭소스 존재 //0000 0001  
	
	TCNT1 = 36786;		// 0 -> 7372800 / 256 = 28800임. 그래서 65536에서 28800을 빼면 36786임.
	TIMSK = (1 << TOIE1); //0x04; //0000 0100 
	TIFR = (1 << TOV1); //0x04;
	sei();
	
	while (1)
	{
		PORTC = LED_Data;  //포트C로 변수 LED_Data에 있는 데이터 출력
	}
	return 0;
}

SIGNAL(TIMER1_OVF_vect)
{
	cli();
	TCNT1 = 36786;
	timer1Cnt++;	//timer0Cnt 변수 1 증가
	
	// 1/28800s * 28800 = 1s, 1초를 얻기 위한 카운트 횟수
	//if (timer1Cnt == 28800)
	//{
		LED_Data++;		//LED_Data 변수 1 증가
		
		if(LED_Data > 0x0f)
			LED_Data = 0;
			
		timer1Cnt = 0;
	//}
	sei();
}