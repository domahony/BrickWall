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
#include "Body.h"
#include "Ground.h"
#include "FrameRate.h"
#include "Renderer.h"
#include "ViewPort.h"
#include "Camera.h"
#include "BodyFactory.h"
#include "BoxMesh.h"
#include <btBulletDynamicsCommon.h>

using std::function;
using std::unique_ptr;

static function<void ()> windowFn();

int
main(int argc, char **argv)
{
	auto swapbuffer = windowFn();

	app::World w;
	app::FrameRate fr;

	app::ViewPort view_port;
	app::Camera camera;
	app::gl::Renderer renderer(view_port, camera);

	std::shared_ptr<app::gl::Mesh> mesh(new app::BoxMesh());

	btTransform loc1(btQuaternion(0,0,0,1), btVector3(0,50,0));
	btTransform loc2(btQuaternion(0,0,0,1), btVector3(-0.33,48,0));
	btTransform loc3(btQuaternion(0,0,0,1), btVector3(0.25,52,0));
	btTransform loc4(btQuaternion(0,0,0,1), btVector3(0.5,50,1));

	btTransform loc5(btQuaternion(0,0,0,1), btVector3(0, 0, 0));

	btRigidBody* b1 = app::tmp::BodyFactory::createBody(loc1, mesh);
	btRigidBody* b2 = app::tmp::BodyFactory::createBody(loc2, mesh);
	btRigidBody* b3 = app::tmp::BodyFactory::createBody(loc3, mesh);
	btRigidBody* b4 = app::tmp::BodyFactory::createBody(loc4, mesh);

	btRigidBody* room = app::tmp::BodyFactory::createRoom(loc5);

	w.addRigidBody(b1);
	w.addRigidBody(b2);
	w.addRigidBody(b3);
	w.addRigidBody(b4);
	w.addRigidBody(room);

	auto frameFn = [&fr]() {
		fr();
	};

	auto renderfn = [&view_port, &camera, &w, &renderer]() {
		w.stepSimulation();
		w.render(view_port, camera, renderer);
	};

	app::EventLoop el(renderer, 60);

	//el.addFn(frameFn);
	el.addFn(renderfn);
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
