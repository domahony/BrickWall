/*
 * EventLoop.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: domahony
 */

#include "types.h"
#include <SDL.h>
#include "EventLoop.h"
#include "FrameRateController.h"

namespace app {

EventLoop::EventLoop(float fps, app::CameraPtr& camera) : fps(fps), camera(camera) {

}

EventLoop::~EventLoop() {
}

void EventLoop::
run()
{

    auto done = false;
    SDL_Event windowEvent;

    app::FrameRateController frc(fps);

    while (!done)
    {

    	if (!frc.tick()) {
    		continue;
    	}

        while (SDL_PollEvent(&windowEvent)) {

        	switch (windowEvent.type) {
        	case SDL_QUIT:
        		done = true;
        		break;
        	default:
        		break;
        	}
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto f: fn) {
        	f();
        }

    }
}

} /* namespace app */
