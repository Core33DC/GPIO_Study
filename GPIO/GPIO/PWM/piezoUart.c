/*
 * piezoUart.c
 *
 * Created: 2022-06-23 오전 11:29:40
 *  Author: pknu
 */ 


//####  Pulse Width Modulation, Universal Asynchronous Receiver/Transmitter ####
//####		 PWM으로 PIEZO 울리기, 그리고 UART통신으로 키보드로 연주		####


#define F_CPU 7372800UL
#include <avr/io.h>  //AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h> //AVR 인터럽트에 대한 헤더파일
#include <util/delay.h>  //delay 함수사용을 위한 헤더파일

//피아노 음계에 해당하는 PWM 주파수
unsigned int DoReMi[9] = {0, 523, 587, 659, 698, 783, 880, 987, 1046}; //도 레 미 파 솔 라 시 도
//unsigned char text[8] = { "도", "레", "미", "파", "솔", "라", "시", "도"}
//volatile unsigned char sound_flag = 1;
//volatile unsigned char TX_flag = 0;
//volatile char TX_data = 0; //스위치 전송 값 저장 변수

unsigned char getch()
{
	unsigned char data;
	while ((UCSR0A & 0x80) == 0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

int main(void)
{
	int input = 0;
	
	DDRB = 0x80;
	//DDRE = 0xfe;	//Rx(입력 0), Tx(출력 1), SW0 ~ 3 입력
	UCSR0A = 0x00;
	UCSR0B = 0x18;	//Rx, Tx enable
	UCSR0C = 0x06;	//비동기 방식, No Parity bit, 1 Stop bit
	UBRR0H = 0x00;
	UBRR0L = 3;		//115200 bps
	
	TCCR1A = 0x00;	//WGM3(1:0) = "00"
	TCCR1B = 0x19;	//WGM3(3:2) = "11" ,  CS3(2:0) = "001"  1분주 사용
	TCCR1C = 0x00;	//WGM3(3:0) = "1110", Fast PWM, 모드 14
	
	TCNT1 = 0x0000;	 //타이머3 카운터 초기화
	
	EICRB = 0xff;	//인터럽트 4, 5, 6, 7을 상승엣지에서 동작하도록 설정
	EIMSK = 0xf0;	//인터럽트 4, 5, 6, 7을 허용
	EIFR = 0xf0;	//인터럽트 4, 5, 6, 7 플래그를 클리어


	while (1)
	{
		input = getch() - '0';
		if(input)
		{
			TCCR1A |= 0x0a;
			ICR1 = 7372800 / DoReMi[input];
			OCR1C = ICR1 / 2;
			_delay_ms(750);
			TCCR1A = 0x00;
			input = 0;
		}
	}
}