/*
 * EventLoop.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: domahony
 */

#include <SDL.h>
#include <ctime>
#include <iostream>
#include "EventLoop.h"

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
    auto control_rate = 1./fps;
    auto tick_rate = 0.;
    auto last_tick = clock();
    auto frame_time = 0.;

    SDL_Event windowEvent;

    /*
    int tickcount = 0;
    auto starttime = clock();
    */

    while (!done)
    {
        auto cur_tick = clock();
        auto delta = static_cast<double>(cur_tick - last_tick) / CLOCKS_PER_SEC;

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

        /*
        tickcount++;
        std::cout.precision(5);
        double total = static_cast<double>(clock() - starttime) / CLOCKS_PER_SEC;
        double frate = static_cast<double>(tickcount) / total;

        std::cout << total << " ";
        std::cout << tickcount << " ";
        std::cout << frate << std::endl;
        */
    }
}

} /* namespace app */
