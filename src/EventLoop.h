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

namespace app {

class EventLoop {
public:
	EventLoop(float rate);
	virtual ~EventLoop();

	void run();
	void addFn(std::function<void ()> f) {
		fn.push_back(f);
	}

private:
	float fps;
	std::vector<std::function<void ()>> fn;
};

} /* namespace app */

#endif /* EVENTLOOP_H_ */
