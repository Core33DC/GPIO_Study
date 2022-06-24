/*
 * piezoUart1.c
 *
 * Created: 2022-06-23 오전 11:57:32
 *  Author: pknu
 */ 


//####  Pulse Width Modulation, Universal Asynchronous Receiver/Transmitter ####
//####	버튼으로 스위치 입력 값 보내기 UART통신으로 음계이름 나오게 하기	####
//####		 PWM으로 PIEZO 울리기		####


#define F_CPU 7372800UL
#include <avr/io.h>  //AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h> //AVR 인터럽트에 대한 헤더파일
#include <util/delay.h>  //delay 함수사용을 위한 헤더파일

//피아노 음계에 해당하는 PWM 주파수
unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046}; //도 레 미 파 솔 라 시 도
unsigned char text[8] = { "도", "레", "미", "파", "솔", "라", "시", "높은 도"}
volatile unsigned char sound_flag = 1;
volatile unsigned char TX_flag = 0;
volatile char TX_data = 0; //스위치 전송 값 저장 변수

void putch(unsigned char data)
{
	while ((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

int main(void)
{
	unsigned char i = 0;
	
	
	sei(); //인터럽트를 허용

	while (text[i]!='\0')
	{
	}
	
	return 0;
}



SIGNAL(INT0_vect)	//인터럽트 서비스 루틴
{
	cli();		//전체 인터럽트를 금지
	TX_data = "도";	//문자 1을 저장
	TX_flag = 1;
	sei();		//전체 인터럽트를 허용
}

SIGNAL(INT1_vect)	//인터럽트 서비스 루틴
{
	cli();		//전체 인터럽트를 금지
	TX_data = "레";	//문자 0을 저장
	TX_flag = 1;
	sei();		//전체 인터럽트를 허용
}

SIGNAL(INT2_vect)	//인터럽트 서비스 루틴
{
	cli();		//전체 인터럽트를 금지
	TX_data = "미";	//문자 1을 저장
	TX_flag = 1;
	sei();		//전체 인터럽트를 허용
}

SIGNAL(INT3_vect)	//인터럽트 서비스 루틴
{
	cli();		//전체 인터럽트를 금지
	TX_data = "파";	//문자 2를 저장
	TX_flag = 1;
	sei();		//전체 인터럽트를 허용
}

SIGNAL(INT4_vect)	//인터럽트 서비스 루틴
{
	cli();		//전체 인터럽트를 금지
	TX_data = "솔";	//문자 0을 저장
	TX_flag = 1;
	sei();		//전체 인터럽트를 허용
}

SIGNAL(INT5_vect)	//인터럽트 서비스 루틴
{
	cli();		//전체 인터럽트를 금지
	TX_data = "라";	//문자 1을 저장
	TX_flag = 1;
	sei();		//전체 인터럽트를 허용
}

SIGNAL(INT6_vect)	//인터럽트 서비스 루틴
{
	cli();		//전체 인터럽트를 금지
	TX_data = "시";	//문자 2를 저장
	TX_flag = 1;
	sei();		//전체 인터럽트를 허용
}

SIGNAL(INT7_vect)	//인터럽트 서비스 루틴
{
	cli();		//전체 인터럽트를 금지
	TX_data = "높은 도";	//문자 3을 저장
	TX_flag = 1;
	sei();		//전체 인터럽트를 허용
}