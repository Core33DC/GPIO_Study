/*
 * interrupt3.c
 *
 * Created: 2022-06-20 오전 11:34:21
 *  Author: pknu
 */ 

// #### 인터럽트로 LED 껐다 켜기 ####

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char exchange = 0;

int main(void)
{
	DDRA = 0xff;  //포트A를 출력포트로 설정
	DDRE = 0x00;  //포트E를 입력포트로 설정
	EICRB = 1 << ISC41; //0x03; //인터럽트 4를 상승엣지에서 동작하도록 설정
	EIMSK = 1 << INT4;
	sei();
	
	while (1)
	{
		if(exchange)
		PORTA = 0xff;
		else
		PORTA = 0X00;
	}
	return 0;
}

//INT4
SIGNAL (INT4_vect)  //인터럽트 서비스 루틴
{
	exchange = ~exchange;
}