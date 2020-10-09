/* 
* millis.cpp
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
* along with Clock_Code.  If not, see <https://www.gnu.org/licenses/>.
*
* Created: 10/1/2020 12:11:51 AM
* Author: Jarrod Coffin
*/


#include "Header/millis.h"


volatile uint16_t millis = 0;
volatile uint16_t secs = 0;

void millisInit(){
	cli();
	    
	//Timer Setup
	//CTC Mode: WGM12 = 1, WGM10:WGM11:WGM13 = 0
	//OCR1A = 7999
	    
	OCR1A = 7999;
	TCCR1B |= (1 << WGM12) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
	
	sei();	
}



ISR(TIMER1_COMPA_vect){
	volatile uint8_t tSREG = SREG;
	
	millis++;
	
	SREG = tSREG;
}

void RTC_Init(){ // Call before millis
	cli();
	
	ASSR = (1<<AS2);
	TCCR2A = 0x00;
	TCCR2B = DIV_128;
	TIMSK2 |= (1 << TOIE2);
}

ISR(TIMER2_OVF_vect){
	volatile uint8_t tSREG = SREG;
	
	secs++;
	
	S_M_H_Count();
	
	SREG = tSREG;
}