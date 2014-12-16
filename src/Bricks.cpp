/*
 ============================================================================
 Name        : Bricks.cpp
 Author      : David O'Mahony
 Version     :
 Copyright   : GPL
 Description : Hello World in C++,
 ============================================================================
 */

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1


#include <iosfwd>
#include <GL/gl.h>
#include <SDL.h>
#include <btBulletDynamicsCommon.h>
#include <ctime>

using namespace std;

int main(void) {

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_Event windowEvent;

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    auto control_rate = 1./120.;
    auto tick_rate = 0.;
    auto last_tick = clock();
    auto frame_time = 0.;
    auto done = false;

    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));

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
        dynamicsWorld->stepSimulation(1/60.f, 10);

        while (SDL_PollEvent(&windowEvent)) {

        	switch (windowEvent.type) {
        	case SDL_QUIT:
        		done = true;
        		break;
        	default:
        		break;
        	}
        }

        // Clear the screen to black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);

    SDL_Quit();

	return 0;
}
