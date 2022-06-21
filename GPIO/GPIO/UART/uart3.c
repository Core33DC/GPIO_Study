/*
 * uart3.c
 *
 * Created: 2022-06-21 오전 11:32:04
 *  Author: pknu
 */ 


// #### UART(유알트)로 PC에서 FND 점멸시키기 ####


#define F_CPU 7432800UL
#include <avr/io.h>  //항상 기본임. AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>	// AVR 인터럽트에 대한 헤더 파일

volatile unsigned char TX_flag = 0;
volatile char TX_data = 0;	//스위치 전송 값 저장 변수

//7-Segment에 표시할 글자의 입력 데이터를 저장
unsigned char FND_DATA_TBL[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f,
	0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
	
void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0); //전송준비가 될때까지 대기
	UDR0 = data;	//데이터를 UDR0에 쓰면 전송된다
	UCSR0A |= 0x20;  //while문 안에 UCSROA & 0x20 == 0 하고 UCSROA |= 0x20 을 합쳐서 
}					 //while(!(UCSROA & (1<<UDRE0))) 으로 바꿀 수도 있다.

//위에 꺼 하고 동일한 메소드 코드
//void putch(unsigned char data)
//{
	//while(!(UCSR0A & (1<<UDRE0)));
	//UDR0 = data;
//}

unsigned char getch(void)
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);	//데이타를 받을때까지 대기
	data=UDR0;	//수신된 데이터는 UDR0에 저장되어 있다.
	UCSR0A |= 0x80;
	return data;	//읽어온 문자를 반환한다.
}

int main(void)
{
	unsigned char RX_data = 0;
	DDRE = 0x0e; //Rx(입력 0), Tx(출력 1)
	DDRA = 0xff; //포트A를 출력포트로 설정한다.
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;	//Rx, Tx enable
	UCSR0C = 0x06;	//비동기 방식, No parity bit, 1 Stop bit
	
	UBRR0H = 0x00;
	UBRR0L = 3;	//115200 bps
	
	while (1)
	{
		RX_data = getch();	//PC로 부터 입력받은 데이터를 변수 RX_data에 저장
		if ((RX_data >= 0x30) && (RX_data <= 0x39))	//아스키코드 '0'은 0x30이다. 그러므로 0x39는 9임.
		{
			PORTA = FND_DATA_TBL[RX_data - 0x30];	//포트 A에 입력된 값의 FND Table 값을 출력한다.
		}
	}
}
