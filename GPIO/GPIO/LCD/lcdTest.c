/*
 * lcdTest.c
 *
 * Created: 2022-06-20 오후 2:55:13
 *  Author: pknu
 */ 


#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h" 

int main(void)
{
	Byte *str1 = " LCD TEST ";	  //str1, 2 앞뒤로 공백을 줘야함. 선미에 공백을 안주면 앞에 글자가 잘린 후에 나옴.
	Byte *str2 = " Atmega 128 ";  //str1, 2 후미에 공백을 안 주면 뒤에 글자가 똑같이 하나 더 나옴.
	DDRA = 0xff;
	DDRG = 0x0f;
	
	Lcd_Init();
	Lcd_Clear();
	
	while (1)   //while문에 넣으면 계속 반복.
	{
				
		Lcd_Pos(0, 0);
		Lcd_STR(str1);
		Lcd_Pos(1, 0);
		Lcd_STR(str2);
	}
	return 0;
}