/*
 * lab2.c
 *
 * Created: 10/2/2017 1:42:47 PM
 * Author : Julian Weisbord
This code will cause a TekBot connected to the AVR board to
move forward and when it touches an obstacle, it will reverse
and turn away from the obstacle and resume forward motion.

PORT MAP
Port B, Pin 4 -> Output -> Right Motor Enable
Port B, Pin 5 -> Output -> Right Motor Direction
Port B, Pin 7 -> Output -> Left Motor Enable
Port B, Pin 6 -> Output -> Left Motor Direction
Port D, Pin 1 -> Input -> Left Whisker
Port D, Pin 0 -> Input -> Right Whisker
*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Globals
#define DISABLE_MOTORS 0b11110000
#define MV_FORWARD 0b01100000
#define MV_BACKWARD 0b00000000
#define MV_LEFT 0b00100000
#define MV_RIGHT 0b01000000
#define LEFT_WHS_DTCT 0b11111101 // Active Low
#define RIGHT_WHS_DTCT 0b11111110 // Active Low

int main(void)
{
	DDRB = 0b11110000; // Set PORTB pin 4-7 as output
	DDRD = 0b00000000; // Set PORTD pin 1 and 0 as input
	PORTB = DISABLE_MOTORS; // Initially disable both motors

	while (1 > 0){
		
		PORTB = MV_FORWARD;

		if((PIND == 11111100) || (PIND == LEFT_WHS_DTCT)){  // Left or both whiskers detected something
			PORTB = MV_BACKWARD;
			_delay_ms(2000);
			PORTB = MV_RIGHT;  // Turn Right
			_delay_ms(1000);
		}

		else if(PIND == RIGHT_WHS_DTCT){  // Right whisker detected something
			PORTB = MV_BACKWARD;
			_delay_ms(1500);
			PORTB = MV_LEFT;  // Turn left
			_delay_ms(1000);
		}
	}
}