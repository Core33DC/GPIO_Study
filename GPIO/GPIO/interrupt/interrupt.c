/*
 * interrupt.c
 *
 * Created: 2022-06-20 오전 9:55:53
 *  Author: pknu
 */

// #### 이진법으로 LED 켜기 ####

#define F_CPU 74328090UL 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char count = 0;

SIGNAL (INT0_vect)
{
	count++;
	PORTA = count;
}

int main(void)
{
	DDRD = 0x00;
	DDRA = 0xff;
	EIMSK = 1 << INT0;  //0x01; //INT0 활성화
	EICRA = (1 << ISC01) | (1 << ISC00);  //EICRA = 0x03;  // 0b 0000 0000
	sei();
	
	while (1)
	{
		
	}
	
	return 0;

}