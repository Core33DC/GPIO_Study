/*
 * led_4.c
 *
 * Created: 2022-06-24 오전 10:21:39
 *  Author: pknu
 */ 


//#### GPIO를 이용하여 스위치 입력 받기 ####
//## 스위치 모듈의 스위치를 누르면 해당되는 LED 모듈의 LED가 점등되도록 함
//## 스위치를 누르면 '1' 신호가 나오고, 놓으면 '0' 신호가 나옴.

#define F_CPU 7372800UL
#include <avr/io.h>		//AVR 입출력에 대한 헤더파일
#include <util/delay.h>	//delay 함수사용을 위한 헤더파일

int main(void)
{
	DDRC = 0x0f;	//포트C 는 출력포트 0000 1111
	DDRE = 0x00;	//포트E 는 입력포트 0000 0000
	while (1)
	{
		PORTC = PINE >> 4; //포트E로 입력받은 값을 포트C로 출력.
		//입력핀이 포트 E의 상위 비트이므로 우측으로 4비트 쉬프트
		//위에서 아래로!!!!
	}
}