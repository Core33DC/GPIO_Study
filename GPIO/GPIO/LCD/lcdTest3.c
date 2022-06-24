/*
 * lcdTest3.c
 *
 * Created: 2022-06-24 오후 3:19:42
 *  Author: pknu
 */ 

#include <avr/io.h> // AVR 입출력에 대한 헤더 파일
#include "lcd.h" // Text LCD를 사용하기 위한 헤더 파일
int main(void) {
	lcdInit(); // Text LCD를 초기화
	lcdGotoXY(0,0); // 현재 커서위치를 첫번째줄 첫번째칸으로 이동
	// 첫번째 매개변수는 행을, 두번째 매개변수는 열을 의미
	lcdDataWrite('H'); // 'H'를 출력
	lcdDataWrite('e'); // 'e'를 출력
	lcdDataWrite('l'); // 'l'를 출력
	lcdDataWrite('l'); // 'l'를 출력
	lcdDataWrite('o'); // 'o'를 출력
	lcdGotoXY(3,1); // 커서위치를 두번째 줄,네번째 칸으로 이동
	lcdPrintData("MCU World !!",12); // "MCU World !!" 문자열 출력
	while (1) {}
}
