/*
 * Clock_Code.cpp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.

 * Created: 10/1/2020 1:28:43 PM
 * Author : Jarrod Coffin
 */ 

#include <avr/io.h>
#include "Includes/Header/display.h"
#include "Includes/Header/millis.h"
#include "Includes/Header/Functions.h"
#include "Includes/Header/_74HC595.h"

int main(void)
{
	RTC_Init();
	millisInit();
	switch_init();
	init_74hc595();
	initDisp();
	blinkCOLON(OFF);
	
	uint8_t lastminutes = ~minutes;
	uint8_t lasthours = ~hours;
	uint8_t lastseconds = ~seconds;
	uint8_t dispSeconds = 0;
	uint16_t secondTimer = 0;
	uint16_t dispSecondTime = 5000;
	
    while (1) 
    {
		uint8_t press_top = switch_read(switch_top);
		uint8_t press_bottom = switch_read(switch_bottom);
		
		switch(press_top){
			
			case SINGLE:
				PORTD ^= COLON;
			break;
			
			case HOLD:
				set_time();
			break;
		
		}
		
		switch(press_bottom){
			
			case SINGLE:
				PORTD ^= COLON;
			break;
			
			case HOLD:
				dispSeconds = 1;
				secondTimer = millis;
				
			break;			
		
		}
		
		while(dispSeconds){
			if (millis - secondTimer > dispSecondTime) dispSeconds = 0;
			if (seconds != lastseconds){
				lastseconds = seconds;
				convertNum(seconds, dispSecond);
			}
			setDisp(CLEAR,CLEAR,dispSecond[1],dispSecond[0]);
		}
		
		
		if (minutes != lastminutes || hours != lasthours){
			
			lastminutes = minutes;
			lasthours = hours;
			convertNum(minutes, dispMinutes);
			convertNum(hours, dispHours);

		}
		
		if(hours < 10)setDisp(CLEAR,dispNum[dispHours[0]],dispNum[dispMinutes[1]],dispNum[dispMinutes[0]]);
		else setDisp(dispNum[dispHours[1]],dispNum[dispHours[0]],dispNum[dispMinutes[1]],dispNum[dispMinutes[0]]);
    
	}
}

