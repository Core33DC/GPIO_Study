/*
 * uart4.c
 *
 * Created: 2022-06-21 오후 12:25:10
 *  Author: pknu
 */ 


#define F_CPU 7432800UL
#include <avr/io.h>  //항상 기본임. AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h>

volatile unsigned char TX_flag = 0;
volatile char TX_data = 0;

unsigned char FND_DATA_TBL[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f,
0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;  //while문 안에 UCSROA & 0x20 == 0 하고 UCSROA |= 0x20 을 합쳐서 while(!(UCSROA & (1<<UDRE0))) 으로 바꿀 수도 있다.
}

//위에 꺼 하고 동일한 메소드 코드
//void putch(unsigned char data)
//{
//while(!(UCSR0A & (1<<UDRE0)));
//UDR0 = data;
//}

//void puts_USART0(char *str)
//{
//while (*str != 0)
//{
//putch(*str);
//str++;
//}
//}

unsigned char getch(void)
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);
	data=UDR0;
	UCSR0A |= 0x80;
	return data;
}

int main(void)
{
	unsigned char RX_data = 0;
	DDRE = 0x0e; //Rx(입력 0), Tx(출력 1)
	DDRA = 0xff; //포트A를 출력포트로 설정한다.
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	while (1)
	{
		RX_data = getch();
		if ((RX_data >= 0x30) && (RX_data <= 0x39))
		{
			PORTA = FND_DATA_TBL[RX_data - 0x30];
		}
	}
}