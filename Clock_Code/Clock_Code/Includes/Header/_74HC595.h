/* 
* _74HC595.h
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
* Created: 10/1/2020 12:29:20 AM
* Author: Jarrod Coffin
*/


#ifndef ___74HC595_H__
#define ___74HC595_H__
#include <avr/io.h>

//74hc595
#define SHCP_PIN	(1<<3) 
#define STCP_PIN	(1<<4) 
#define DATA_PIN	(1<<2)
#define OUT_PIN		(1<<0)

#define DATA_PIN_SET PORTC |= DATA_PIN
#define DATA_PIN_CLEAR PORTC &= ~DATA_PIN

void init_74hc595();

void sendData(uint8_t data);

#endif //___74HC595_H__
