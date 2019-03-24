/*
 * scenario.h
 *
 *  Created on: Dec 31, 2018
 *      Author: francois
 */

#ifndef SRC_SCENARIO_H_
#define SRC_SCENARIO_H_
#include "Arduino.h"

class scenario {
public:
	scenario(const uint8_t * _actions);
	virtual ~scenario();

	void run();
	uint32_t delay_time;
	bool active;
	const uint8_t * actions; // Start of the scenario string
	const uint8_t * pc;
};

#endif /* SRC_SCENARIO_H_ */
