/*
 * scenario.cpp
 *
 *  Created on: Dec 31, 2018
 *      Author: francois
 */

#include <avr/pgmspace.h>
#include "scenario.h"
#include "actions.h"

scenario::scenario(const uint8_t * _actions) {
	// TODO Auto-generated constructor stub
	actions = _actions;
	pc = actions;
	delay_time = 0;
	active = false;
}

scenario::~scenario() {
	// TODO Auto-generated destructor stub
}

void scenario::run() {
	uint8_t current_action;
	// To be called in a loop
	if (delay_time != 0) {
		if (millis() < delay_time)
			return;
	}
	current_action = pgm_read_byte(pc);
	switch (current_action) {
	case 0:{

	}
	} /* end switch */
	pc++;

}

