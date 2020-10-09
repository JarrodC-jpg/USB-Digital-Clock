/* 
* _74HC595.cpp
*
* This file is part of Clock_Code.
*
* CLock_Code is free software: you can redistribute it and/or modify
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
* Created: 10/1/2020 12:29:20 AM
* Author: Jarrod Coffin
*/


#include "Header/_74HC595.h"


void init_74hc595(){
	// 74hc595 pin setup
	DDRC |= SHCP_PIN | STCP_PIN | DATA_PIN;
	DDRD |= OUT_PIN;
	PORTC |= SHCP_PIN | STCP_PIN;
	PORTD &= ~(OUT_PIN);
}

void sendData(uint8_t data){
	
	for (int i = 0; i < 8; i++) {
		
		if ((data >> i) & 0x01) DATA_PIN_SET;
		else DATA_PIN_CLEAR;
		
		PORTC &= ~SHCP_PIN;
		PORTC |= SHCP_PIN;
	}
	
	PORTC &= ~STCP_PIN;
	PORTC |= STCP_PIN;
	
}
