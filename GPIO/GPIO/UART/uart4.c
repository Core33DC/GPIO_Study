/*
 * uart4.c
 *
 * Created: 2022-06-21 오후 12:25:10
 *  Author: pknu
 */ 


// #### 하이퍼터미널로 구구단 만들기 ####


#include <avr/io.h>

void putch(unsigned char data){
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch(){
	unsigned char data;
	while((UCSR0A & 0x80) == 0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

void puts(char *str){
	int i = 0;
	
	while(str[i] != '\0'){
		putch(str[i++]);
	}
}

int main(){
	unsigned char text[] = "\r\nInput number to view the gugudan\r\n";
	unsigned char text2[] = "INPUT >> ";
	unsigned char gugu[50];
	
	DDRE = 0xfe;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	while(1){
		puts(text);
		puts(text2);

		char input = '\0';
		int inputi = 0;
		
		while(!(inputi >= 2 && inputi <= 9)){
			input = getch();
			inputi = input  - 0x30;
		}
		putch(input);
		
		for(int j = 1; j<=9; j++){
			sprintf(gugu, "\n%d * %d = %d", inputi, j, inputi*j);
			
			puts(gugu);
		}
	}
	
	return 0;
}