/*
 * led_6.c
 *
 * Created: 2022-06-24 오전 10:48:07
 *  Author: pknu
 */ 


//#### GPIO를 이용하여 FND LED 켜기 ####
//## FND(Flexible Numeric Display : 7-Segment LED)를 이용하여 숫자를 표시
//## 일정시간마다 클럭에 의해 FND에 숫자와 문자가 디스플레이


#define F_CPU 7372800UL
#include <avr/io.h>		//AVR 입출력에 대한 헤더파일
#include <util/delay.h>	//delay 함수사용을 위한 헤더파일

int main(void)
{
	//7-Segment에 표시할 글자의 입력 데이터를 저장
	unsigned char FND_DATA_TBL[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f,
	0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
	
	unsigned char cnt = 0;
	DDRA = 0xff;
	
	while (1)
	{
		PORTA = FND_DATA_TBL[cnt];
		cnt++;
		if(cnt > 17)
			cnt = 0;
		_delay_ms(500);
	}
	return 0;
}
						  