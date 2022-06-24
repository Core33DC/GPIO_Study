/*
 * _03_switch.c
 *
 * Created: 2022-06-24 오전 10:31:51
 *  Author: pknu
 */ 


//#### GPIO를 이용하여 스위치 입력 받기 ####
//## 스위치 모듈의 스위치를 누르면 해당되는 LED 모듈의 LED가 점등되도록 함
//## 스위치를 누르면 '1' 신호가 나오고, 놓으면 '0' 신호가 나옴.
//## LED 점멸시간 변경

#define F_CPU 7372800UL
#include <avr/io.h>		//AVR 입출력에 대한 헤더파일
#include <util/delay.h>	//delay 함수사용을 위한 헤더파일

int main(void)
{
	unsigned char Switch_flag = 0;
	unsigned char Switch_flag_pre = 0x01;
	
	DDRC = 0x0f;	//포트C 는 출력포트 0000 1111
	DDRE = 0x00;	//포트E 는 입력포트 0000 0000
	
	PORTC = 0x00;	//LED 0 ~ 3 을 OFF
		
	while (1)
	{
		//포트 E로 입력받은 값을 변수 Switch_flag에 저장
		//입력핀이 포트 E의 상위 비트이므로 우측으로 4비트 쉬프트
		Switch_flag = PINE >> 4;
		
		//SW 0 ~ 3 스위치 중 하나만 눌렸을 때
		if ((Switch_flag == 0x01) || (Switch_flag == 0x02) || (Switch_flag == 0x04) || (Switch_flag == 0x08))
		{
			//눌린 상태 Switch_flag 값을 변수 Switch_flag_pre에 저장
			Switch_flag_pre = Switch_flag;
		}
		
		//PORTC(LED가 연결된 포트)의 하위 4비트를 반전
		PORTC ^= 0x0f;
		
		if(Switch_flag_pre == 0x01) //SW0을 눌렀을때
			_delay_ms(250);		//250ms 시간지연
		else if(Switch_flag_pre == 0x02) //SW1을 눌렀을때
			_delay_ms(500);		//500ms 시간지연
		else if(Switch_flag_pre == 0x04) //SW2을 눌렀을때
			_delay_ms(750);		//750ms 시간지연
		else if(Switch_flag_pre == 0x08) //SW3을 눌렀을때
			_delay_ms(1000);	//1000ms 시간지연
	}
}