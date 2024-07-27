/******************************************************************************
 *
 * Module: main application
 *
 * File Name: main.c
 *
 * Description: Source file for the application
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/

#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */

uint16 distance = 0;
int main(){

	/*enable global interrupt flag*/
	SREG |= (1 << 7);

	/*Initialize LCD and ULTRASENSOR*/
	LCD_init();
	Ultrasonic_init();

	LCD_displayString("Distance =    ");

	for(;;){

		/*read the distance*/
		distance = Ultrasonic_readDistance();

		/*Display the distance*/
		LCD_moveCursor(0, 11);
		LCD_intgerToString(distance);

		/*Units correction*/
		if(distance<10){
			LCD_moveCursor(0, 12);
			LCD_displayString(" cm   ");
		}
		/*Tenth correction*/
		else if(distance<100){
			LCD_moveCursor(0, 13);
			LCD_displayString(" cm  ");
		}
		else{
			LCD_displayString("cm");
		}
	}
}
