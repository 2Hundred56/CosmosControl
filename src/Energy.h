/*
 * Energy.hpp
 *
 *  Created on: Sep 2, 2019
 *      Author: triforce
 */

#ifndef ENERGY_H_
#define ENERGY_H_

class Energy {

};

class EnergyDistribution {
};

class EnergyDelta {
public:
	EnergyDelta();
	EnergyDelta(float);
	EnergyDelta(float, EnergyDistribution);
};

Energy operator+(Energy, EnergyDelta);
Energy operator-(Energy, EnergyDelta);
Energy operator+=(Energy, EnergyDelta);
Energy operator-=(Energy, EnergyDelta);
EnergyDelta operator+(EnergyDelta, EnergyDelta);
EnergyDelta operator-(EnergyDelta, EnergyDelta);
EnergyDelta operator*(EnergyDelta, float);
EnergyDelta operator/(EnergyDelta, float);
EnergyDelta operator+=(EnergyDelta, EnergyDelta);
EnergyDelta operator-=(EnergyDelta, EnergyDelta);
bool operator<(EnergyDelta, EnergyDelta);
bool operator>(EnergyDelta, EnergyDelta);
bool operator==(EnergyDelta, EnergyDelta);
bool operator!=(EnergyDelta, EnergyDelta);
bool operator<=(EnergyDelta, EnergyDelta);
bool operator>=(EnergyDelta, EnergyDelta);

bool CanReceive(Energy, EnergyDelta);

#endif /* ENERGY_H_ */
