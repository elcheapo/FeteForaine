/*
 * scenario.cpp
 *
 *  Created on: Dec 31, 2018
 *      Author: francois
 */

#include <avr/pgmspace.h>
#include "scenario.h"
#include "actions.h"

<<<<<<< HEAD
scenario::scenario(void (*_init)(void), uint32_t (*_action)(void)) {
=======
scenario::scenario(uint32_t (*_action)(uint8_t &)) {
>>>>>>> branch 'master' of git://cygne/git/FeteForaine
	enabled = false;
	delay_time = 0;
	cycle = 0;
	action = _action;
	init = _init;
}

scenario::~scenario() {
	// TODO Auto-generated destructor stub
}

<<<<<<< HEAD
void scenario::enable(uint8_t &cycle) {
=======
void scenario::enable() {
	cycle = 0;
>>>>>>> branch 'master' of git://cygne/git/FeteForaine
	enabled = true;
	cycle = 1;
}

<<<<<<< HEAD
void scenario::disable(uint8_t &cycle) {
	enabled = false;
	cycle = 0;
	init();
=======
void scenario::disable() {
	cycle = 0;
	run();
	enabled = false;
>>>>>>> branch 'master' of git://cygne/git/FeteForaine
}

void scenario::run() {
	if (!enabled) return;
	if (delay_time != 0) {
		if (millis() < delay_time)
			return;
	}
	delay_time = millis() + action(cycle);
}

