/*
 * TimeCount3.c
 *
 * Created: 2022-06-21 오후 4:40:20
 *  Author: pknu
 */ 


// #### 타이머를 이용한 디지털 시계(1) ####
// #### 타이머와 인터럽트로 FND 점멸(1) ####


#define F_CPU 7432800UL
#include <avr/io.h>  //AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>  //AVR 인터럽트에 대한 헤더 파일

//7-Segment에 표시할 글자의 입력 데이터를 저장
unsigned char FND_DATA_TBL[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f,
							  0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
							  
volatile unsigned char time_s = 0;	//초를 세는 변수
unsigned char timer0Cnt = 0;

int main(void)
{
	DDRA = 0xff;	//포트 A는 출력포트
	
	TCCR0 = 0x07;	//프리스케일러 1024
	OCR0 = 72;	//0.1초마다 한번씩 인터럽트 발생
	TIMSK = 0x02;	//출력비교 인터럽트 활성화
	TIFR |= 1 << OCF0;
	
	sei();
	
	while (1)
	{
		PORTA = FND_DATA_TBL[time_s];	//포트A에 FND Table 값을 출력
	}
	return 0;
}

SIGNAL(TIMER0_COMP_vect)
{
	cli();
	OCR0 += 72;		//0.01초 후에 인터럽트 발생
	timer0Cnt++;	//timer0Cnt 변수 1 증가
	
	//0.01s * 100 = 1s
	if(timer0Cnt == 100)	//1초를 얻기 위한 카운트 횟수
	{
		if(time_s >= 16)
			time_s = 0;		//time_s 변수는 16까지만 증가
		else
			time_s++;
			timer0Cnt = 0;	//16이 되면 0으로 초기화
	}
	sei();
}