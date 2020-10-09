/* 
* display.cpp
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
* Created: 10/1/2020 12:25:54 AM
* Author: Jarrod Coffin
*/


#include "Header/display.h"

uint8_t dispNum[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};


void initDisp(){
	// 7 Seg select pins
	DDRD |= Seg_ONE | Seg_TEN | Seg_HUNDRED | Seg_THOU | COLON;
}

void setDisp(uint8_t thouData, uint8_t hunData, uint8_t tenData, uint8_t oneData){
	
	sendData(oneData);
	Seg_ONE_ON;
	_delay_us(100);
	clearDisp();
	
	sendData(tenData);
	Seg_TEN_ON;
	_delay_us(100);
	clearDisp();
	
	sendData(hunData);
	Seg_HUNDRED_ON;
	_delay_us(100);
	clearDisp();
	
	sendData(thouData);
	Seg_THOU_ON;
	_delay_us(100);
	clearDisp();
	

}

void clearDisp(){
	Seg_Clear;
}
