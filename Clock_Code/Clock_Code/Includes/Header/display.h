/* 
* display.h
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


#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define F_CPU 8000000UL

#include <avr/io.h>
#include "util/delay.h"
#include "_74HC595.h"

// 7 Seg Select
#define Seg_ONE		(1<<1)
#define Seg_TEN		(1<<2)
#define Seg_HUNDRED (1<<3)
#define Seg_THOU	(1<<4)
#define COLON		(3<<5)
#define COLON_CHECK (COLON & PIND)
#define Seg_Clear  PORTD = 0x00 | COLON_CHECK
#define Seg_ONE_ON PORTD = Seg_ONE | COLON_CHECK
#define Seg_TEN_ON PORTD = Seg_TEN | COLON_CHECK
#define Seg_HUNDRED_ON PORTD = Seg_HUNDRED | COLON_CHECK
#define Seg_THOU_ON PORTD = Seg_THOU | COLON_CHECK

#define DOT		 ~(1<<7)
#define CLEAR	0xff
//							 .abcdefg
#define ZERO	(uint8_t)~(0b01111110)
#define ONE		(uint8_t)~(0b00110000)
#define TWO		(uint8_t)~(0b01101101)
#define THREE	(uint8_t)~(0b01111001)
#define FOUR	(uint8_t)~(0b00110011)
#define FIVE	(uint8_t)~(0b01011011)
#define SIX		(uint8_t)~(0b01011111)
#define SEVEN	(uint8_t)~(0b01110010)
#define EIGHT	(uint8_t)~(0b01111111)
#define NINE	(uint8_t)~(0b01111011)



extern uint8_t dispNum[10];

void initDisp();
void setDisp(uint8_t oneData, uint8_t tenData, uint8_t hunData, uint8_t thouData);
void clearDisp();


#endif //__DISPLAY_H__
