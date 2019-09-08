/*
 * Time.hpp
 *
 *  Created on: Sep 2, 2019
 *      Author: triforce
 */

#ifndef TIME_H_
#define TIME_H_

class Time {
public:
	Time();
	Time(float);
	float seconds;
};

class TimeDelta {
public:
	TimeDelta();
	TimeDelta(float);
	float seconds;
};

Time operator+(Time, TimeDelta);
Time operator-(Time, TimeDelta);
Time& operator+=(Time&, TimeDelta);
Time& operator-=(Time&, TimeDelta);
TimeDelta operator+(TimeDelta, TimeDelta);
TimeDelta operator-(TimeDelta, TimeDelta);
TimeDelta operator*(TimeDelta, float);
TimeDelta operator/(TimeDelta, float);
TimeDelta& operator+=(TimeDelta&, TimeDelta);
TimeDelta& operator-=(TimeDelta&, TimeDelta);
bool operator<(TimeDelta, TimeDelta);
bool operator>(TimeDelta, TimeDelta);
bool operator==(TimeDelta, TimeDelta);
bool operator!=(TimeDelta, TimeDelta);
bool operator<=(TimeDelta, TimeDelta);
bool operator>=(TimeDelta, TimeDelta);



#endif /* TIME_H_ */
