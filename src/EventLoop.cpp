/*
 * EventLoop.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: domahony
 */

#include <SDL.h>
#include <ctime>
#include "EventLoop.h"

namespace app {

EventLoop::EventLoop(float rate) : rate(rate) {
	// TODO Auto-generated constructor stub

}

EventLoop::~EventLoop() {
	// TODO Auto-generated destructor stub
}

void EventLoop::
run()
{
	auto done = false;
    auto control_rate = 1./120.;
    auto tick_rate = 0.;
    auto last_tick = clock();
    auto frame_time = 0.;

    SDL_Event windowEvent;

    while (!done)
    {
        auto cur_tick = clock();
        auto delta = cur_tick - last_tick / CLOCKS_PER_SEC;

        frame_time += delta;
        last_tick = cur_tick;

        if (frame_time < control_rate) {
        	continue;
        }

        frame_time -= control_rate;

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