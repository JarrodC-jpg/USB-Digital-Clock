/* 
* millis.h
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
* Created: 10/1/2020 12:11:51 AM
* Author: Jarrod Coffin
*/


#ifndef __MILLIS_H__
#define __MILLIS_H__

#include <avr/io.h>
#include "avr/interrupt.h"
#include "Functions.h"

#define DIV_128 (1 << CS22)|(1 << CS20)

extern volatile uint16_t millis;
extern volatile uint16_t secs;

extern uint16_t seconds;
extern uint16_t minutes;
extern uint16_t hours;
extern uint16_t days;


void millisInit(); // not very accurate

void RTC_Init(); // RTC for accurate timing


#endif //__MILLIS_H__
