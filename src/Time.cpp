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

Time operator -(Time time, TimeDelta timeDelta) {
	return Time(time.seconds-timeDelta.seconds);
}

TimeDelta operator +(TimeDelta timeDelta, TimeDelta timeDelta1) {
	return TimeDelta(timeDelta.seconds+timeDelta1.seconds);
}

TimeDelta operator -(TimeDelta timeDelta, TimeDelta timeDelta1) {
	return TimeDelta(timeDelta.seconds+timeDelta1.seconds);
}

TimeDelta operator *(TimeDelta timeDelta, float float1) {
	return TimeDelta(timeDelta.seconds*float1);
}

TimeDelta operator /(TimeDelta timeDelta, float float1) {
	return TimeDelta(timeDelta.seconds/float1);
}

bool operator <(TimeDelta timeDelta, TimeDelta timeDelta1) {
	return timeDelta.seconds<timeDelta1.seconds;
}

bool operator >(TimeDelta timeDelta, TimeDelta timeDelta1) {
	return timeDelta.seconds>timeDelta1.seconds;
}

bool operator ==(TimeDelta timeDelta, TimeDelta timeDelta1) {
	return timeDelta.seconds==timeDelta1.seconds;
}

bool operator !=(TimeDelta timeDelta, TimeDelta timeDelta1) {
	return timeDelta.seconds!=timeDelta1.seconds;
}

bool operator <=(TimeDelta timeDelta, TimeDelta timeDelta1) {
	return timeDelta.seconds<=timeDelta1.seconds;
}

bool operator >=(TimeDelta timeDelta, TimeDelta timeDelta1) {
	return timeDelta.seconds>=timeDelta1.seconds;
}
