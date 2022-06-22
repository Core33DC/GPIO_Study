/*
 * pwm.c
 *
 * Created: 2022-06-22 오후 4:25:06
 *  Author: pknu
 */ 


//#### Pulse Width Modulation ####
//#### PWM으로 LED 밝기 조절  ####


#define F_CPU 7372800UL
#include <avr/io.h>  //AVR 입출력에 대한 헤더 파일
#include <util/delay.h>  //delay 함수사용을 위한 헤더파일

int main(void)
{
	unsigned char Light = 0;
	
	DDRB = 0x10;  //
	
	TCCR0 = 0x76; //TCCR0이니 8비트. //PC PWM 모드, 1024분주 // 0111 0111 인데 256분주로 바꿔주려면 0111 0110이다. 즉 0x76;
	//위에 16진수로 쓰거나 아니면 아래 껄로 쓰거나 둘 중 하나
	//TCCR0 = |= (1 << WGM00) | (1 << COM01) | (1 << COM00) | (1 << CS02) | (1 << CS01);
	TCNT0 = 0x00;
	
	while (1)
	{
		for(Light = 0; Light < 255; Light++)
		{
			OCR0 = Light;
			_delay_ms(5);
		}
		for (Light = 255; 0 < Light; Light--)
		{
			OCR0 = Light;
			_delay_ms(5);
		}
	}
}