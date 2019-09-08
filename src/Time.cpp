/*
 * Time.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */
#include "Time.h"

Time operator +(Time time, TimeDelta timeDelta) {
	return Time(time.seconds+timeDelta.seconds);
}
