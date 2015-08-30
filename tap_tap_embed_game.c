#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "hardware/io.h"
#include "hardware/timer.h"
#include "hardware/pwm.h"
#include "hardware/keypad.h"
#include "software/notes.h"
#include "song_helpers.h"
//global

int main(void)
{
	DDRA = 0xF0; PORTA = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xF0; PORTD = 0x0F;

	TimerSet(100);
	TimerOn();
	
	LCD_init();
	PWM_on();
	option = init_menu;
	restart = init_paused;

	while(1)
	{
		x = GetKeypadKey();
		if(reset)//if reset then displays menu also when initialized displays menu
		{
			menu();
			replay=0;
			sound_counter=0;
		}
		else if((song_picked==1 || song_picked==2) && !pause) // plays osng if not finished or paused
		{
			song_is_picked();
			noise_counter++;
		}
		else if(pause) // if paused takes you to menu to reset or continue 
		{
			paused();
		}
		//TODO:: Please write your application code
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}


