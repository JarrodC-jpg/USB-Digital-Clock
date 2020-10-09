/* 
* numberFunctions.h
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
* Created: 10/1/2020 1:50:41 AM
* Author: Jarrod Coffin
*/


#ifndef __NUMBERFUNCTIONS_H__
#define __NUMBERFUNCTIONS_H__

#include <avr/io.h>
#include <math.h>
#include "millis.h"
#include "display.h"

extern uint16_t seconds;
extern uint16_t minutes;
extern uint16_t hours;
extern uint16_t days;

#define PORTE_ADDR 0x0C
#define DDR_OFFSET 0x01
#define PORT_OFFSET 0x02
#define PIN_OFFSET 0x00

#define SWITCH_TOP_PIN 1
#define SWITCH_BOTTOM_PIN 0

#define PRESSED 0
#define SINGLE 1
#define HOLD 2

#define ON 1
#define OFF 0

struct switch_struct {
	
	uint8_t port_addr;
	uint8_t pin;
	uint8_t state;
	uint8_t prev_state;
	uint8_t long_press;
	long unsigned int read_time;
	long unsigned int last_read_time;
	
};

extern switch_struct switch_top;
extern switch_struct switch_bottom;
extern uint8_t debounce;
extern uint16_t long_press_time;

extern uint8_t dispHours[2];
extern uint8_t dispMinutes[2];
extern uint8_t dispSecond[2];


void convertNum(uint16_t cNum, uint8_t *dispArr);

void S_M_H_Count();

void set_time();

void switch_init();

uint8_t switch_read(switch_struct &sw);

void blinkCOLON(int blink);


#endif //__NUMBERFUNCTIONS_H__
