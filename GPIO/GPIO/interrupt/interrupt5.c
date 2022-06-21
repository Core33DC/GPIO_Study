/*
 * interrupt5.c
 *
 * Created: 2022-06-20 오후 12:27:27
 *  Author: pknu
 */ 


// #### 인터럽트로 FND 점멸 #### 1. FND 숫자가 초마다 증가하면서 켬.  2. 버튼을 누르면 FND가 멈추었다가 한번 더 누르면 다시 동작

#define F_CPU 7432800UL
#include <avr/io.h>	//AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>	//AVR 인터럽트에 대한 헤더파일
#include <util/delay.h>	//delay 함수사용을 위한 헤더파일

volatile unsigned char Time_STOP = 0;

int main()
{
	// 7-Segment에 표시할 글자의 입력 데이터를 저장
	unsigned char FND_DATA_TBL []={
		0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80 //0x80은 FND에서 .을 의미함.
	};
	unsigned char cnt = 0; //FND Table 카운터 변수
	DDRA = 0xff; //출력포트
	DDRE = 0x00; //입력포트
	EICRB = 0x0c; //인터럽트 5를 상승엣지에서 동작하도록 설정
	EIMSK = 0x20; //인터럽트 5 허용
	EIFR = 0x20; //인터럽트 5 플래그를 클리어
	sei(); //전체 인터럽트를 허용
	
	while (1)
	{
		PORTA = FND_DATA_TBL[cnt];  //포트A에 FND Table 값을 출력
		if(Time_STOP == 0)  //Time_STOP이 0인 경우
		{
			cnt++;  //FND Table 카운터 변수를 증가
			if (cnt>17) 
				cnt = 0; // 테이블 크기를 초과하는 경우 방지
			
		}
		_delay_ms(1000);
	}
}

SIGNAL(INT5_vect) //인터럽트 서비스 루틴
{
	cli(); //전체 인터럽트를 금지
	if(Time_STOP == 0) //Time_STOP이 0인경우
	{
		Time_STOP = 1; //Time_STOP에 1을 입력
	}
	else //Time_STOP이 1인경우
	{
		Time_STOP = 0;	//Time_STOP에 0을 입력
	}
	sei(); //전체 인터럽트를 허용
}