/*
 * fndled1.c
 *
 * Created: 2022-06-24 오전 10:57:27
 *  Author: pknu
 */ 


//#### 스위치의 입력값에 따라 FND LED값 변경하기 ####
//## 스위치의 입력값에 따라 FND에 출력되는 숫자를 1, 2를 더하거나 빼보도록 함
//## 포트를 출력으로 선언, 이 포트를 FND 모듈의 신호선 포트에 연결


#define F_CPU 7372800UL
#include <avr/io.h>		//AVR 입출력에 대한 헤더파일
#include <util/delay.h>	//delay 함수사용을 위한 헤더파일

int Count_TR(unsigned char flag);

int main(void)
{
	//7-Segment에 표시할 글자의 입력 데이터를 저장
	unsigned char FND_DATA_TBL[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f,
								  0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
	
	unsigned char cnt = 0;	//FND Table 카운터 변수
	unsigned char Switch_flag = 0;	//스위치 값 저장 변수
	
	DDRA = 0xff;	//포트 A를 출력포트로 설정
	DDRE = 0x00;	//포트 E를 입력포트로 설정
	
	while (1) {
		// 입력핀이 포트 E의 상위 비트이므로 우측으로 4비트 쉬프트
		Switch_flag = PINE >> 4;
		while(PINE >> 4 != 0x00); // 스위치를 눌렀을 경우 땔 때까지 대기
		
		if(Switch_flag != 0)// 스위치가 눌렀을 경우에 만 실행
			// 스위치 버튼에 따라 변수 cnt 값을 증가 또는 감소
			cnt += Count_TR(Switch_flag);
		
		// 변수 cnt 값의 범위를 0 ~ 15로 설정
		if(cnt < 0)
			cnt = 0;
		else if(cnt > 15)
			cnt = 15;
		
		PORTA = FND_DATA_TBL[cnt]; // 포트 A에 FND Table 값을 출력
		_delay_ms(100); // 100ms 시간 지연
	}
}

int Count_TR(unsigned char flag) {
	int count = 0;
	switch (flag) {
		case 0x01: // SW0을 눌렀을때
		count = 1;
		break;
		case 0x02: // SW1을 눌렀을때
		count = 2;
		break;
		case 0x04: // SW2을 눌렀을때
		count = -1;
		break;
		case 0x08: // SW3을 눌렀을때
		count = -2;
		break;
	}
	return count;
}

