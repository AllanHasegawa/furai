/*
 * ApplicationListener.h
 *
 *  Created on: Aug 13, 2012
 *      Author: AranHase
 */

#ifndef FURAI_APPLICATIONLISTENER_H_
#define FURAI_APPLICATIONLISTENER_H_

class ApplicationListener {
	virtual ~ApplicationListener() {};

	virtual void on_create();
	virtual void on_resume();
	virtual void on_draw(const double delta_time);
	virtual void on_resize(const int width, const int height);
	virtual void on_pause();
	virtual void on_destroy();
};


#endif /* APPLICATIONLISTENER_H_ */
