/*
 * lcdTest2.c
 *
 * Created: 2022-06-20 오후 4:54:59
 *  Author: pknu
 */ 


// #### 구구단 ####


#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

int main(void)
{
	DDRA = 0xff;
	DDRG = 0xff;
	Byte *str1;
		
	Lcd_Init();
	Lcd_Clear();
	
	while(1)
	{
		for(int i = 2; i<=9; i++){
			for(int j = 1; j<=9; j++){
				Lcd_Pos(0, 0);
				sprintf(str1, "%d * %d = %d", i, j, i*j);
				Lcd_STR(str1);
				_delay_ms(1000);
			}
		}
	}
	
	
	return 0;
}