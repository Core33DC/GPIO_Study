/*
 * StepMotor1.c
 *
 * Created: 2022-06-23 오후 3:23:30
 *  Author: pknu
 */ 


//#### 2상 여자 방식으로 스텝 모터 돌리기 ####

//## 2상 여자 방식으로 1바퀴 돌고 1초 정지 시키는 것을 무한 반복
//## 1, 2상 여자 방식일 때 펄스당 7.5도,
//## 1-2상 여자 방식일 때 펄스당 3.75도


#define F_CPU 7372800UL
#include <avr/io.h>		//AVR 입출력에 대한 헤더파일
#include <util/delay.h> //delay 함수사용을 위한 헤더파일

int main(void)
{
	unsigned char i;
	
	DDRB = 0x20;
	DDRD = 0xf0;
	
	PORTB &= ~0x20;
	
	while (1)
	{
		for (i=0; i<12; i++)				//2상 여자 방식이므로 7.5도씩 회전
		{
			PORTD = 0x30;					//시계 방향일 경우 PORTD에 0x30 -> 0x90 -> 0xC0 -> 0x60 
			_delay_ms(10);	//1 step		//이러한 명령이 총 360 / 7.5 = 48, 즉 48개의 펄스가 입력되어야 함.
			
			PORTD = 0x90;					//한 주기가 4개의 명령으로 이루어 지므로 0x30 -> 0x90 -> 0xc0 -> 0x60
			_delay_ms(10);	//2 step		//12주기의 명령이 PORTD로 입력되어야 스텝 모터는 1회전 함.
			
			PORTD = 0xc0;
			_delay_ms(10);
			
			PORTD = 0x60;
			_delay_ms(10);
		}
		_delay_ms(1000);
	}
}