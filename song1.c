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
unsigned short i =0;
void noise()
{
		set_PWM(Happy_birthday_notes[i++%52]);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
		
		TimerSet(500);
		TimerOn();

	PWM_on();
    while(1)
    {
		
		noise();
        //TODO:: Please write your application code 
			while(!TimerFlag){}
			TimerFlag = 0;
    }
}


