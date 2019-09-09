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

Time& operator +=(Time& time, TimeDelta timeDelta) {
	time=time+timeDelta;
	return time;
}

Time& operator -=(Time& time, TimeDelta timeDelta) {
	time=time-timeDelta;
	return time;
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

TimeDelta& operator +=(TimeDelta& timeDelta1, TimeDelta timeDelta) {
	timeDelta1=timeDelta1+timeDelta;
	return timeDelta1;
}

TimeDelta& operator -=(TimeDelta& timeDelta1, TimeDelta timeDelta) {
	timeDelta1=timeDelta1-timeDelta;
	return timeDelta1;
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

Time& operator +=(Time& time, TimeDelta timeDelta) {
	time.seconds+=timeDelta.seconds;
	return time;
}

Time& operator -=(Time& time, TimeDelta timeDelta) {
	time.seconds-=timeDelta.seconds;
	return time;
}

TimeDelta& operator +=(TimeDelta& timeDelta, TimeDelta timeDelta1) {
	timeDelta.seconds+=timeDelta1.seconds;
	return timeDelta;
}

TimeDelta& operator -=(TimeDelta& timeDelta, TimeDelta timeDelta1) {
	timeDelta.seconds-=timeDelta1.seconds;
	return timeDelta;
}

bool operator >=(TimeDelta timeDelta, TimeDelta timeDelta1) {
	return timeDelta.seconds>=timeDelta1.seconds;
}

Time::Time() {
	seconds = 0;
}

TimeDelta::TimeDelta() {
	seconds = 0;
}

Time::Time(float float1) {
	seconds = float1;
}

TimeDelta::TimeDelta(float float1) {
	seconds = float1;
}
