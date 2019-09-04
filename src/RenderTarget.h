/*
 * RenderTarget.h
 *
 *  Created on: Sep 4, 2019
 *      Author: triforce
 */

#ifndef RENDERTARGET_H_
#define RENDERTARGET_H_

class RenderTarget {
public:
	RenderTarget();
	virtual ~RenderTarget();
	void Render(unsigned int* data, int w, int h);
};

#endif /* RENDERTARGET_H_ */
