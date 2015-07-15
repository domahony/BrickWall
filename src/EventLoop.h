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
#include "Camera.h"
#include "World.h"

namespace app {

class EventLoop {
public:
	EventLoop(float rate, app::CameraPtr& camera, app::WorldPtr& world);
	virtual ~EventLoop();

	void run();
	void addFn(std::function<void ()> f) {
		fn.push_back(f);
	}
private:
	void handleKey(const SDL_KeyboardEvent&);

private:
	float fps;
	std::vector<std::function<void ()>> fn;
	app::CameraPtr camera;
	app::WorldPtr world;
};

} /* namespace app */

#endif /* EVENTLOOP_H_ */
