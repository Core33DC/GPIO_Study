/*
 * TimeCount16_2.c
 *
 * Created: 2022-06-22 오후 5:59:17
 *  Author: pknu
 */ 


//####       16 비트        ####
//#### 타이머로 LED 점멸(2) ####


#define F_CPU 7372800UL
#include <avr/io.h>  // AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>  // AVR 인터럽트에 대한 헤더파일

//7-Segment에 표시할 글자의 입력 데이터를 저장
unsigned char FND_DATA_TBL[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f,
							  0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
							  
volatile unsigned char time_s = 0; //초를 세는 변수 선언

int main(void)
{
	DDRA = 0xff;	//포트A 출력포트. 1111 1111
	
	TCCR1A = 0x00;  
	TCCR1B = 0x05;  //프리스케일러 1024
	
	OCR1A = 7200;  // 7372800 / 1024 = 7200  //1초마다 한번씩 인터럽트 발생
	TIMSK = 0x10;
	TIFR |= 1 << OCF1A;
	
	sei();
	while (1)
	{
		PORTA = FND_DATA_TBL[time_s];  //포트A에 FND Table 값을 출력
	}
	return 0;
}

SIGNAL(TIMER1_COMPA_vect)
{
	cli();
	
	OCR1A += 7200;	//1초 후에 인터럽트 발생
	if(time_s >= 17)	//time_s 변수는 17까지만 증가
		time_s = 0;	 //17되면 0으로 초기화
	else
		time_s++;	
		
	sei();
}