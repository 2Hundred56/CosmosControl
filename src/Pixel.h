/*
 * Pixel.hpp
 *
 *  Created on: Sep 4, 2019
 *      Author: triforce
 */

#ifndef PIXEL_H_
#define PIXEL_H_

class Pixel {
public:
	float r;
	float g;
	float b;
	float a;
	float z;
	Pixel(float r, float g, float b, float a = 1, float z=0) : r(r), g(g), b(b), a(a), z(z){

	}
	Pixel() : r(0), g(0), b(0), a(0), z(-1000){

	}
};
Pixel& operator+= (Pixel&, Pixel);
bool operator<(const Pixel&, const Pixel&);


#endif /* PIXEL_H_ */
