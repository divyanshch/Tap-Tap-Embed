#include "hardware/io.h"
#include "hardware/timer.h"
#include "hardware/keypad.h"
#include "software/notes.h"
#include "software/songs.h"
//globals

unsigned char finished =0;
unsigned char highscore_displayed =0;
unsigned char prev_score =0;
uint8_t ByteOfData ;
unsigned char prev_x =0;
unsigned char score =0;
unsigned short sound_counter =0;
unsigned char x = 0;
double tone=0;
unsigned char replay =0;
unsigned char A_pressed = 0;
unsigned char B_pressed = 0;
unsigned char C_pressed = 0;
unsigned char D_pressed = 0;
unsigned char E_pressed = 0;
unsigned char F_pressed = 0;
unsigned char G_pressed = 0;
unsigned char pressed   = 0;
unsigned char song_picked = 0;
unsigned char pause = 0;
unsigned char cont = 0;
unsigned char reset = 1;
unsigned char noise_counter =0;
enum restarts{init_paused, wait_paused} restart;
enum options{init_menu, wait_menu, choice_menu} option;
///////////////////////////////////////////////////////////

//plays the music
void noise(unsigned char input)
{
	if(input ==1)//happy birthday
	{
		
		unsigned short position = sound_counter++%52;
		if(replay <1)
		{
			tone = Happy_birthday_notes[position];
			set_PWM(tone);
			if(position==51)
			{
				replay++;
				
			}
		}
		else
		{
			tone =0;
			set_PWM(tone);
		}
	}
	else if (input ==2)//simpsons
	{
		unsigned short position = sound_counter++%42;
		if(replay <1)
		{
			tone = Simpsons_theme_notes[position];
			set_PWM(tone);
			if(position==41)
			{
				replay++;
			}
		}
		else
		{
			tone =0;
			set_PWM(tone);
		}
	}

}
//displays the custom characters
void displaying(double tone)
{
	A_pressed = 0;
	B_pressed = 0;
	C_pressed = 0;
	D_pressed = 0;
	E_pressed = 0;
	F_pressed = 0;
	G_pressed = 0;
	LCD_ClearScreen();
	if(
	tone== A0_NOTE   || tone== A1_NOTE   || tone== A2_NOTE   ||
	tone== A3_NOTE   || tone== A4_NOTE   || tone== A5_NOTE   ||
	tone== A6_NOTE   || tone== A7_NOTE   || tone== A8_NOTE   ||
	tone== A0_S_NOTE || tone== A1_S_NOTE || tone== A2_S_NOTE ||
	tone== A3_S_NOTE || tone== A4_S_NOTE || tone== A5_S_NOTE ||
	tone== A6_S_NOTE || tone== A7_S_NOTE || tone== A8_S_NOTE  )
	{
		LCD_Cursor(1);
		LCD_WriteData(0x00);//left arrow
		LCD_Cursor(2);
		LCD_WriteData(0x05);
		A_pressed = 1;
	}
	
	else if (
	tone== B0_NOTE   || tone== B1_NOTE   || tone== B2_NOTE   ||
	tone== B3_NOTE   || tone== B4_NOTE   || tone== B5_NOTE   ||
	tone== B6_NOTE   || tone== B7_NOTE   || tone== B8_NOTE    )
	{
		LCD_Cursor(1);
		LCD_WriteData(0x05);
		LCD_Cursor(2);
		LCD_WriteData(0x01);//right arrow
		B_pressed = 1;
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
		LCD_WriteData(0x04);
		LCD_Cursor(17);
		LCD_WriteData(0x02);//down
		C_pressed = 1;
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
		LCD_WriteData(0x03);//up
		LCD_Cursor(17);
		LCD_WriteData(0x04);
		D_pressed = 1;
	}
	else if (
	tone== E0_NOTE   || tone== E1_NOTE   || tone== E2_NOTE   ||
	tone== E3_NOTE   || tone== E4_NOTE   || tone== E5_NOTE   ||
	tone== E6_NOTE   || tone== E7_NOTE   || tone== E8_NOTE    )
	{
		LCD_Cursor(1);
		LCD_WriteData(0x00);//left arrow
		LCD_Cursor(2);
		LCD_WriteData(0x05);
		E_pressed = 1;
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
		LCD_WriteData(0x05);
		LCD_Cursor(2);
		LCD_WriteData(0x01);//right arrow
		F_pressed = 1;
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
		LCD_WriteData(0x04);
		LCD_Cursor(17);
		LCD_WriteData(0x02);//down
		G_pressed = 1;
	}
}
//menu for the paused
void paused()
{
	switch(restart)
	{
		case init_paused:
		set_PWM(0);
		LCD_DisplayString(1,"     Paused     Cont. B  Reset C");
		restart=wait_paused;
		break;
		case wait_paused:
		x=GetKeypadKey();
		if(x=='B')//continue
		{
			reset=0;
			pause=0;
		}
		else if(x=='C')
		{
			reset =1;
			pause = 0;
			option = init_menu;
		}
		break;
	}
	
}
//menu initializes everything
void menu()
{
	switch (option)
	{
		
		case init_menu:
		LCD_DisplayString(1,  "     Welcome      'A' to start");
		option = wait_menu;
		break;
		case wait_menu:
		if(x=='A')
		{
			LCD_DisplayString(1,"1:Happy Birthday2:Simpson Theme");
			ByteOfData = eeprom_read_byte (( uint8_t *) 1) ;
			prev_x=0;
			score = 0;
			//happy birthday//////////////////////////////
			if(ByteOfData == 255)//initiallizes the eeprom
			{
				ByteOfData=0;
				eeprom_update_byte (( uint8_t *) 1, ByteOfData );
			}
			ByteOfData = eeprom_read_byte (( uint8_t *) 1) ;
			//simpsons////////////////////////////////////
			ByteOfData = eeprom_read_byte (( uint8_t *) 2) ;
			
			if(ByteOfData == 255)//initiallizes the eeprom
			{
				ByteOfData=0;
				eeprom_update_byte (( uint8_t *) 2, ByteOfData );
			}
			ByteOfData = eeprom_read_byte (( uint8_t *) 2) ;
			/////////////////////////////////////////////////
			option = choice_menu;
		}
		break;
		case choice_menu:
		if(x=='1')
		{
			song_picked =1;
			reset =0;
			noise_counter=7;
		}
		else if(x=='2')
		{
			song_picked = 2;
			reset =0;
			noise_counter=7;
		}
		break;
	}
	
}
//displays the higher scores
void finished_display_score()
{
	unsigned char num =0;
	highscore_displayed =1;
	if(song_picked==1)
	{
		ByteOfData = eeprom_read_byte (( uint8_t *) 1) ;
		if(score>ByteOfData)
		{
			ByteOfData=score;
			eeprom_update_byte (( uint8_t *) 1 , ByteOfData );
		}
		score = ByteOfData;
	}
	if(song_picked==2)
	{
		ByteOfData = eeprom_read_byte (( uint8_t *) 2) ;
		if(score>ByteOfData)
		{
			ByteOfData=score;
			eeprom_update_byte (( uint8_t *) 2 , ByteOfData );
		}
		score = ByteOfData;
	}
	num=0;
	while(score>=10)
	{
		score = score -10;
		num++;
	}
	
	
	LCD_ClearScreen();
	LCD_DisplayString(1,"High Score: ");
	if(num!=0)
	{
		LCD_WriteData(num+'0');
	}
	LCD_WriteData(score+'0');
	score = prev_score;
}
//checks if the key pressed matches the custom key
void check_input_with_tone()
{
	prev_x = x;
	if(x=='A' && !finished && (A_pressed||B_pressed||C_pressed||D_pressed||E_pressed||F_pressed||G_pressed))
	{
		restart=init_paused;
		pause = 1;
	}

	if(x=='A' && finished)
	{
		finished_display_score();
	}

	if(x=='C' && finished && highscore_displayed)
	{
		highscore_displayed =0;
		finished =0;
		reset =1;
		pause = 0;
		option = init_menu;
	}
	
	if(A_pressed)
	{
		if(x=='4'){score++;PORTB=1;}
	}
	else if(B_pressed)
	{
		if(x=='6'){score++;PORTB=1;}
	}
	else if(C_pressed)
	{
		if(x=='8'){score++;PORTB=1;}
	}
	else if(D_pressed)
	{
		if(x=='2'){score++;PORTB=1;}
	}
	else if(E_pressed)
	{
		if(x=='4'){score++;PORTB=1;}
	}
	else if(F_pressed)
	{
		if(x=='6'){score++;PORTB=1;}
	}
	else if(G_pressed)
	{
		if(x=='8'){score++;PORTB=1;}
	}
}
//displays the scores
void note_score_handler()
{
	finished =1;
	prev_score = score;
	A_pressed = 0;
	B_pressed = 0;
	C_pressed = 0;
	D_pressed = 0;
	E_pressed = 0;
	F_pressed = 0;
	G_pressed = 0;
	pressed =0;
	unsigned char num =0;
	while(score>=10)
	{
		score = score -10;
		num++;
	}
	
	LCD_ClearScreen();
	LCD_DisplayString(1,"Your Score: ");
	if(num!=0)
	{
		LCD_WriteData(num+'0');
	}
	LCD_WriteData(score+'0');
	score = prev_score;
}
//checks which song is picked
void song_is_picked()
{
	if(noise_counter == 7)
	{
		noise(song_picked);
		noise_counter =0;
		if(replay!=1)
		{
			displaying(tone);
		}
		else if (score!=prev_score || score ==0)
		{
			note_score_handler();
		}
	}
	pressed =0;
	PORTB=0;
	if(x!=prev_x)
	{
		check_input_with_tone();
	}
}
