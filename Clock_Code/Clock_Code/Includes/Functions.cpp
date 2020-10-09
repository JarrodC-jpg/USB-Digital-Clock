/* 
* Functions.cpp
*
* This file is part of Clock_Code.
*
* Clock_Code is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Clock_Code is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Clock_Code.  If not, see <https://www.gnu.org/licenses/>.*
*
* Created: 10/1/2020 1:50:40 AM
* Author: Jarrod Coffin
*/


#include "Header/Functions.h"

uint16_t seconds = 0;
uint16_t minutes = 0;
uint16_t hours	 = 12;
uint16_t days	 = 0;

uint8_t dispMinutes[2] = {0,0};
uint8_t dispHours[2]   = {0,0};
uint8_t dispSecond[2]  = {0,0};
	
uint8_t debounce = 5;
uint16_t long_press_time = 400;


switch_struct switch_top = {
	
	PORTE_ADDR, // Port selection
	SWITCH_TOP_PIN,
	!PRESSED,
	!PRESSED,
	SINGLE,
	0,
	0,
	
};

switch_struct switch_bottom = {

	PORTE_ADDR, // Port selection
	SWITCH_BOTTOM_PIN,
	!PRESSED,
	!PRESSED,
	SINGLE,
	0,
	0,

};
		
void convertNum(uint16_t cNum, uint8_t *dispArr) {
	
	uint8_t count = 0;
	uint16_t num_buff = cNum;
	
	while (num_buff != 0) {
		num_buff /= 10;
		++count;
	}
	
	if (!cNum) {
		
		for (int i = 0; i < 2; i++){			
			dispArr[i] = 0;		
		}
		
	} else {	
			
		for (int i = 0; i < count; i++) {		
			dispArr[i] = (int)(cNum/pow(10,i)) % 10;			
		}
			
		if (count < 2) {	
			for (int i = count; i < 2; i++) {
				dispArr[i] = 0;			
			}
		}	
	}
}

void S_M_H_Count() {
	seconds = secs;
	if (seconds > 59) {
		
		seconds = 0;
		secs = 0;
		minutes++;
		
		if (minutes > 59) {
		
			minutes = 0;
			hours++;
		
			if (hours > 12) {
		
				hours = 1;
		
			}
		}
	}
}

void set_time(){
	uint8_t Exit = 0;
	uint8_t tempMin = minutes;
	uint8_t tempHour = hours;
	uint8_t tempDispH[2];
	uint8_t tempDispM[2];
	
	convertNum(tempMin, tempDispM);
	convertNum(tempHour, tempDispH);
	
	while(!Exit){
		
		blinkCOLON(ON);
		uint8_t T_SW = switch_read(switch_top);
		uint8_t B_SW = switch_read(switch_bottom);
		
		if(tempHour < 10) setDisp(CLEAR,dispNum[tempDispH[0]],dispNum[tempDispM[1]],dispNum[tempDispM[0]]);
		else setDisp(dispNum[tempDispH[1]],dispNum[tempDispH[0]],dispNum[tempDispM[1]],dispNum[tempDispM[0]]);
		
		switch (T_SW)
		{
			case SINGLE:
				tempHour++;
				if (tempHour > 12) tempHour = 1;
				convertNum(tempHour, tempDispH);
				break;
				
			case HOLD:
				blinkCOLON(OFF);
				minutes = tempMin;
				hours = tempHour;
				seconds = 0;
				secs = 0;
				Exit = 1;
				break;
				
		}
		
		switch (B_SW)
		{
			case SINGLE:
					tempMin++;
					if (tempMin > 59) tempMin = 0;
					convertNum(tempMin, tempDispM);
					
				break;
			case HOLD:
				blinkCOLON(OFF);
				Exit = 1;
				break;
		}
	}
}

uint8_t switch_read(switch_struct &sw) {
	uint8_t press = 0;
	sw.state = _SFR_IO8(sw.port_addr + PIN_OFFSET) & (1 << sw.pin);
	switch_bottom.state = _SFR_IO8(switch_bottom.port_addr + PIN_OFFSET) & (1 << switch_bottom.pin);

	if (sw.state != sw.prev_state) {
		sw.read_time = millis;
		sw.prev_state = sw.state;
		if (sw.read_time - sw.last_read_time > debounce && sw.state && !sw.long_press)
		{
			sw.last_read_time = sw.read_time;
			press = SINGLE;
		}
		sw.long_press = 0;
	} else if (!sw.state && millis - sw.read_time > long_press_time && !sw.long_press) {
		sw.long_press = 1;
		press = HOLD;
	} 
	
	return press;
	
}

void switch_init() {
	
	_SFR_IO8(switch_top.port_addr + DDR_OFFSET) &= ~(1 << switch_top.pin);
	_SFR_IO8(switch_bottom.port_addr + DDR_OFFSET) &= ~(1 << switch_bottom.pin); 
	
}

void blinkCOLON(int blink){
	
	static long unsigned int prevTime = 0;
	
	if (millis - prevTime > 250 && blink){
		
		prevTime = millis;
		PORTD ^= COLON;	
		
	} else if (!blink) {
		
		PORTD |= COLON;
		
	} 
	
}