/*
 * EventLoop.h
 *
 *  Created on: Dec 20, 2014
 *      Author: domahony
 */

#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

#include <functional>
#include <vector>
#include "Body.h"

namespace app {

class EventLoop {
public:
	EventLoop(float rate, app::Body* body);
	virtual ~EventLoop();

	void run();
	void addFn(std::function<void ()> f) {
		fn.push_back(f);
	}

private:
	float fps;
	std::vector<std::function<void ()>> fn;
	app::Body* body;
};

} /* namespace app */

#endif /* EVENTLOOP_H_ */
