#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include "timer.h"
#include "pwm.h"
#include "notes.h"




double Happy_birthday_notes[] ={A4_NOTE, A4_NOTE+.1, B4_NOTE, B4_NOTE, A4_NOTE, D5_NOTE, C5_S_NOTE,
	A4_NOTE, A4_NOTE+.1, B4_NOTE, B4_NOTE, A4_NOTE, E5_NOTE , D5_NOTE,
	A4_NOTE, A4_NOTE+.1, A4_NOTE, F5_S_NOTE, D5_NOTE, C5_S_NOTE, B4_NOTE,
	G5_NOTE, G5_NOTE, F5_S_NOTE, D5_NOTE, E5_NOTE, D5_NOTE,
	A4_NOTE, A4_NOTE+.1, B4_NOTE, A4_NOTE, D5_NOTE, C5_S_NOTE,
	A4_NOTE, A4_NOTE+.1, B4_NOTE, A4_NOTE, E5_NOTE, D5_NOTE,
	A4_NOTE, A4_NOTE+.1, A4_NOTE, F5_S_NOTE, D5_NOTE, C5_S_NOTE, B4_NOTE,
	G5_NOTE, G5_NOTE+.1, F5_S_NOTE, D5_NOTE, E5_NOTE, D5_NOTE
};
unsigned short sound_counter =0;

void noise()
{
	double tone = Happy_birthday_notes[sound_counter++%52];
	set_PWM(tone);
	
	displaying(tone);
	
}

enum displays {init, wait, left, right, up, down } display;
char customChar[8] = {
	0b00001,
	0b00011,
	0b00111,
	0b01111,
	0b00111,
	0b00011,
	0b00001,
	0b00000
};
void displaying(double tone)
{
	
	LCD_ClearScreen();
	//unsigned long tone= tone;
	if(
	tone== A0_NOTE   || tone== A1_NOTE   || tone== A2_NOTE   ||
	tone== A3_NOTE   || tone== A4_NOTE   || tone== A5_NOTE   ||
	tone== A6_NOTE   || tone== A7_NOTE   || tone== A8_NOTE   ||
	tone== A0_S_NOTE || tone== A1_S_NOTE || tone== A2_S_NOTE ||
	tone== A3_S_NOTE || tone== A4_S_NOTE || tone== A5_S_NOTE ||
	tone== A6_S_NOTE || tone== A7_S_NOTE || tone== A8_S_NOTE  )
	{
		LCD_Cursor(1);
		LCD_WriteData(0x00);
		LCD_Cursor(2);
		LCD_WriteData(0x05);
		
		PORTB = 1;
	}
	
	else if (
	tone== B0_NOTE   || tone== B1_NOTE   || tone== B2_NOTE   ||
	tone== B3_NOTE   || tone== B4_NOTE   || tone== B5_NOTE   ||
	tone== B6_NOTE   || tone== B7_NOTE   || tone== B8_NOTE    )
	{
		LCD_Cursor(1);
		LCD_WriteData('B');
		PORTB = 2;
	}
	else if (
	tone== C0_NOTE   || tone== C1_NOTE   || tone== C2_NOTE   ||
	tone== C3_NOTE   || tone== C4_NOTE   || tone== C5_NOTE   ||
	tone== C6_NOTE   || tone== C7_NOTE   || tone== C8_NOTE   ||
	tone== C0_S_NOTE || tone== C1_S_NOTE || tone== C2_S_NOTE ||
	tone== C3_S_NOTE || tone== C4_S_NOTE || tone== C5_S_NOTE ||
	tone== C6_S_NOTE || tone== C7_S_NOTE || tone== C8_S_NOTE	)
	{
		LCD_Cursor(1);
		LCD_WriteData('C');
		PORTB = 3;
	}
	else if (
	tone== D0_NOTE   || tone== D1_NOTE   || tone== D2_NOTE   ||
	tone== D3_NOTE   || tone== D4_NOTE   || tone== D5_NOTE   ||
	tone== D6_NOTE   || tone== D7_NOTE   || tone== D8_NOTE   ||
	tone== D0_S_NOTE || tone== D1_S_NOTE || tone== D2_S_NOTE ||
	tone== D3_S_NOTE || tone== D4_S_NOTE || tone== D5_S_NOTE ||
	tone== D6_S_NOTE || tone== D7_S_NOTE || tone== D8_S_NOTE   )
	{
		LCD_Cursor(1);
		LCD_WriteData('D');
		PORTB = 4;
	}
	else if (
	tone== E0_NOTE   || tone== E1_NOTE   || tone== E2_NOTE   ||
	tone== E3_NOTE   || tone== E4_NOTE   || tone== E5_NOTE   ||
	tone== E6_NOTE   || tone== E7_NOTE   || tone== E8_NOTE    )
	{
		LCD_Cursor(1);
		LCD_WriteData('E');
		PORTB = 5;
	}
	else if (
	tone== F0_NOTE   || tone== F1_NOTE   || tone== F2_NOTE   ||
	tone== F3_NOTE   || tone== F4_NOTE   || tone== F5_NOTE   ||
	tone== F6_NOTE   || tone== F7_NOTE   || tone== F8_NOTE   ||
	tone== F0_S_NOTE || tone== F1_S_NOTE || tone== F2_S_NOTE ||
	tone== F3_S_NOTE || tone== F4_S_NOTE || tone== F5_S_NOTE ||
	tone== F6_S_NOTE || tone== F7_S_NOTE || tone== F8_S_NOTE)
	{
		LCD_Cursor(1);
		LCD_WriteData('F');
		PORTB = 6;
	}
	else if (
	tone== G0_NOTE   || tone== G1_NOTE   || tone== G2_NOTE   ||
	tone== G3_NOTE   || tone== G4_NOTE   || tone== G5_NOTE   ||
	tone== G6_NOTE   || tone== G7_NOTE   || tone== G8_NOTE   ||
	tone== G0_S_NOTE || tone== G1_S_NOTE || tone== G2_S_NOTE ||
	tone== G3_S_NOTE || tone== G4_S_NOTE || tone== G5_S_NOTE ||
	tone== G6_S_NOTE || tone== G7_S_NOTE || tone== G8_S_NOTE  )
	{
		LCD_Cursor(1);
		LCD_WriteData('G');
		PORTB = 7;
	}
}

int main(void)
{
	DDRA = 0xF0; PORTA = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	TimerSet(100);
	TimerOn();
	unsigned char noise_counter =0;
	LCD_init();
	PWM_on();
	while(1)
	{

		if(noise_counter == 6)
		{
			noise();
			noise_counter =0;
		}
		//TODO:: Please write your application code
		while(!TimerFlag){}
		TimerFlag = 0;
		noise_counter++;
	}
}


