/*
 * EventLoop.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: domahony
 */

#include <SDL.h>
#include "EventLoop.h"
#include "FrameRateController.h"

namespace app {

EventLoop::EventLoop(float fps) : fps(fps) {
	// TODO Auto-generated constructor stub

}

EventLoop::~EventLoop() {
	// TODO Auto-generated destructor stub
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

        for (auto f: fn) {
        	f();
        }

    }
}

} /* namespace app */
