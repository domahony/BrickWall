/*
 * main.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: domahony
 */

#include <GL/gl.h>
#include <SDL.h>
#include <functional>
#include <memory>
#include "EventLoop.h"
#include "World.h"
#include "FrameRate.h"

using std::function;
using std::unique_ptr;

static function<void ()> windowFn();

int
main(int argc, char **argv)
{
	auto swapbuffer = windowFn();

	app::World w;
	app::FrameRate fr;

	auto worldFn = [&w]() {
			w.stepSimulation();
	};

	auto frameFn = [&fr]() {
		fr();
	};

	app::EventLoop el(60);

	el.addFn(worldFn);
	el.addFn(frameFn);
	el.addFn(swapbuffer);
	el.run();
}

function<void ()>
windowFn()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    auto swapbuffer = [window] () {
        SDL_GL_SwapWindow(window);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    };

   return swapbuffer;
}
