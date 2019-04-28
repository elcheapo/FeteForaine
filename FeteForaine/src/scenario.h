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
	scenario(uint32_t (*_action)(void));
	virtual ~scenario();

	void run();
	void enable(void);
	void disable(void);
	boolean enabled;
	uint32_t delay_time;
	uint32_t (*action)(void); // returns delay
};

#endif /* SRC_SCENARIO_H_ */
