/*
 * Rotation.hpp
 *
 *  Created on: Sep 2, 2019
 *      Author: triforce
 */

#ifndef ROTATION_H_
#define ROTATION_H_

class Rotation {

};

class RotationDelta {
public:
	RotationDelta();
	RotationDelta(float);
};

Rotation operator+(Rotation, RotationDelta);
Rotation operator-(Rotation, RotationDelta);
RotationDelta operator+(RotationDelta, RotationDelta);
RotationDelta operator-(RotationDelta, RotationDelta);
RotationDelta operator*(RotationDelta, float);
RotationDelta operator/(RotationDelta, float);
bool operator<(RotationDelta, RotationDelta);
bool operator>(RotationDelta, RotationDelta);
bool operator==(RotationDelta, RotationDelta);
bool operator!=(RotationDelta, RotationDelta);
bool operator<=(RotationDelta, RotationDelta);
bool operator>=(RotationDelta, RotationDelta);

#endif /* ROTATION_H_ */
