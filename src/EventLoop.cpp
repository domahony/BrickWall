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

EventLoop::EventLoop(float fps, app::CameraPtr& camera, app::WorldPtr& world) : fps(fps), camera(camera), world(world) {

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
        	case SDL_KEYDOWN:
        		handleKey(windowEvent.key);
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

void EventLoop::
handleKey(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym) {
	case SDLK_LEFT:
		camera->left();
		break;
	case SDLK_RIGHT:
		camera->right();
		break;
	case SDLK_UP:
		camera->up();
		break;
	case SDLK_DOWN:
		camera->down();
		break;
	case SDLK_f:
		camera->forward();
		break;
	case SDLK_b:
		camera->backward();
		break;
	case SDLK_r:
		world->reset();
		break;
	default:
		break;
	}
}

} /* namespace app */
