/*
 * TimeCount16_3.c
 *
 * Created: 2022-06-22 오후 6:40:25
 *  Author: pknu
 */ 


//####				 16 비트			      ####
//#### 타이머를 이용한 스위치 누른시간 구하기 ####


#define F_CPU 7372800UL
#include <avr/io.h>  // AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>  // AVR 인터럽트에 대한 헤더파일

//7-Segment에 표시할 글자의 입력 데이터를 저장
unsigned char FND_DATA_TBL[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f,
							  0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
							  
volatile unsigned char time_s = 0; //초를 세는 변수 선언
volatile unsigned char FND_flag = 0, edge_flag = 0;

int main(void)
{
	DDRA = 0xff;	//포트 A는 출력포트 1111 1111
	DDRE = 0x00;	//포트 E는 입력포트 0000 0000
	
	TCCR3A = 0x00;
	TCCR3B = 0x45;  //프리스케일러 1024, 상승(양)에지 캡처 트리거 설정
	ETIMSK = 0x20;	//입력캡쳐 인터럽트3 활성화
	ETIFR |= 1 << ICF3;
	
	sei();
	PORTA = FND_DATA_TBL[0];	//포트A에 FND Table의 값을 출력
	while (1)
	{
		if(FND_flag)
		{
			if(time_s > 15)		//최대 1.5초까지 표시(F)
				time_s = 15;
				
			PORTA = FND_DATA_TBL[time_s];	//포트A에 FND Table 값 출력
			FND_flag = 0;
		}
	}
	return 0;
}

SIGNAL(TIMER3_CAPT_vect)
{
	cli();
	
	unsigned int count_check;
	
	//스위치가 눌릴 시간 측정을 위해
	//상승에지에서 하강에지까지의 시간을 계산
	
	if(edge_flag == 0) //상승 에지(스위치를 누르면)
	{	//프리스케일러 1024, 하강(음)에지 캡처 드리거 설정
		TCCR3B = 0x05;
		TCNT3 = 0;	//TCNT3 레지스터를 0으로 초기화
		ICR3 = 0;	//ICR 레지스터를 0으로 초기화
		edge_flag = 1;
	}
	else //하강 에지(스위치를 떼면)
	{	//프리스케일러 1024, 상승(양)에지 캡처 트리거 설정
		TCCR3B = 0x45;
		count_check = ICR3;
		
		// 7372800 / 1024 = 7200 Hz, 1초동안 TCNT의 값은 7200
		time_s = count_check/720;	//누를 시간을 0.1초 단위로 변경
		
		//측정 시간 FND로 출력 0 ~ 1.5초 까지 측정 가능
		FND_flag = 1;
		edge_flag = 0;
	}
	sei();
}