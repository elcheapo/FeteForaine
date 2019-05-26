/*
 * scenario.cpp
 *
 *  Created on: Dec 31, 2018
 *      Author: francois
 */

#include <avr/pgmspace.h>
#include "scenario.h"
#include "actions.h"

scenario::scenario(uint32_t (*_action)(uint8_t &)) {
	enabled = false;
	delay_time = 0;
	cycle = 0;
	action = _action;
}

scenario::~scenario() {
	// TODO Auto-generated destructor stub
}

void scenario::enable() {
	cycle = 0;
	enabled = true;
}

void scenario::disable() {
	cycle = 0;
	run();
	enabled = false;
}

void scenario::run() {
	if (!enabled) return;
	if (delay_time != 0) {
		if (millis() < delay_time)
			return;
	}
	delay_time = millis() + action(cycle);
}

