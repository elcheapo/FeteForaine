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
<<<<<<< HEAD
	scenario(void (*_init)(void), uint32_t (*_action)(void));
=======
	scenario(uint32_t (*_action)(uint8_t &));
>>>>>>> branch 'master' of git://cygne/git/FeteForaine
	virtual ~scenario();

	void run(void);
	void enable(uint8_t & cycle);
	void disable(uint8_t & cycle);
	boolean enabled;
	uint32_t delay_time;
<<<<<<< HEAD
	void (*init)(void);
	uint32_t (*action)(void); // returns delay
=======
	uint8_t cycle;
	uint32_t (*action)(uint8_t &cycle); // returns delay
>>>>>>> branch 'master' of git://cygne/git/FeteForaine
};


#endif /* SRC_SCENARIO_H_ */
