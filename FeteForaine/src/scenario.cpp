/*
 * scenario.cpp
 *
 *  Created on: Dec 31, 2018
 *      Author: francois
 */

#include <avr/pgmspace.h>
#include "scenario.h"
#include "actions.h"

scenario::scenario(uint32_t (*_action)(void)) {
	enabled = false;
	delay_time = 0;
	action = _action;
}

scenario::~scenario() {
	// TODO Auto-generated destructor stub
}

void scenario::enable() {
	enabled = true;
}

void scenario::disable() {
	enabled = true;
}

void scenario::run() {
	if (!enabled) return;
	if (delay_time != 0) {
		if (millis() < delay_time)
			return;
	}
	delay_time = millis() + action();
}

