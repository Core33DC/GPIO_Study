/*
 * StepMotor.c
 *
 * Created: 2022-06-23 오후 3:06:34
 *  Author: pknu
 */ 


//#### 1상 여자 방식으로 스텝 모터 돌리기 ####

//## 현재 1상 방식으로 사용. 반시계 방향으로 돌게 끔
//## 2상 여자 방식일 때는 펄스당 7.5도
//## 1-2상 여자 방식일 때 펄스당 3.75도 회전

#define F_CPU 7372800UL
#include <avr/io.h>		//AVR 입출력에 대한 헤더파일
#include <util/delay.h>	//delay 함수사용을 위한 헤더파일

int main(void)
{
	DDRB = 0x20;	//MOTOR1_EN을 출력 포트로 설정
	DDRD = 0xf0;	//STEP 0 ~ 3 을 출력 포트로 설정
	
	PORTB &= ~0x20;	//M1 Disable, DC 모터 정지
	
	while(1) // 반시계 방향으로 돔. 시계 방향으로 돌리고 싶으면 0x80, 0x40, 0x20, 0x10 순으로 배치
	{
		PORTD = 0x10;
		_delay_ms(5); //1 step
		
		PORTD = 0x20;
		_delay_ms(5); //2 step
		
		PORTD = 0x40;
		_delay_ms(5); //3 step
		
		PORTD = 0x80;
		_delay_ms(5); //4 step
		
	}
}