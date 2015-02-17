/*
 * main.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: domahony
 */

#include "types.h"
#include <SDL.h>
#include <functional>
#include <memory>
#include "Shader.h"
#include "BoxMesh.h"
#include "ObjMesh.h"
#include "EventLoop.h"
#include "World.h"
#include "FrameRate.h"
#include "ViewPort.h"
#include "Camera.h"
#include "BodyFactory.h"
#include "BlinPhonBasic.h"
#include <btBulletDynamicsCommon.h>

using std::function;
using std::unique_ptr;
using app::gl::BlinPhonBasic;

static function<void ()> windowFn();

int
main(int argc, char **argv)
{
	auto swapbuffer = windowFn();

	app::World w;
	app::FrameRate fr;

	app::ViewPort view_port;
	app::Camera camera;

	std::shared_ptr<app::gl::ShaderSource> bpb(new app::gl::BlinPhonBasic());
	std::shared_ptr<app::gl::Shader> shader(new app::gl::Shader(bpb));

	app::ObjMesh floor("/home/domahony/git/BrickWall/media/plane.obj", shader);
	app::ObjMesh cubeplus("/home/domahony/git/BrickWall/media/cubeplus.obj", shader);
	app::ObjMesh cube("/home/domahony/git/BrickWall/media/cube.obj", shader);
	app::ObjMesh sphere("/home/domahony/git/BrickWall/media/world.obj", shader);

	/*
	app::ObjMesh floor("/home/domahony/Projects/ws-ogldev/Bricks2/media/plane.obj", shader);
	app::ObjMesh cubeplus("/home/domahony/Projects/ws-ogldev/Bricks2/media/cubeplus.obj", shader);
	app::ObjMesh cube("/home/domahony/Projects/ws-ogldev/Bricks2/media/cube.obj", shader);
	app::ObjMesh sphere("/home/domahony/Projects/ws-ogldev/Bricks2/media/sphere.obj", shader);
	*/

	btTransform loc1(btQuaternion(0,0,0,1), btVector3(0,50,0));
	btTransform loc2(btQuaternion(0,0,0,1), btVector3(-0.33,48,6));
	btTransform loc3(btQuaternion(0,0,0,1), btVector3(0.25,52,0));
	btTransform loc4(btQuaternion(0,0,0,1), btVector3(0.5,50,1));
	btTransform loc6(btQuaternion(0,0,0,1), btVector3(-5,55,6));
	btTransform loc7(btQuaternion(0,0,0,1), btVector3(-1,20,0));

	btTransform loc8(btQuaternion(0,0,0,1), btVector3(-8.0, 500,-8.5));
	btTransform loc9(btQuaternion(0,0,0,1), btVector3(5,75,0));
	btTransform loc10(btQuaternion(0,0,0,1), btVector3(-9,60,-9));

	btTransform loc5(btQuaternion(0,0,0,1), btVector3(0, 0, 0));

	btRigidBody* b1 = app::tmp::BodyFactory::createBody(loc1, cubeplus.getMesh());
	btRigidBody* b2 = app::tmp::BodyFactory::createBody(loc2, sphere.getMesh());
	btRigidBody* b3 = app::tmp::BodyFactory::createBody(loc3, sphere.getMesh());
	btRigidBody* b4 = app::tmp::BodyFactory::createBody(loc4, sphere.getMesh());
	btRigidBody* b5 = app::tmp::BodyFactory::createBody(loc6, sphere.getMesh());
	btRigidBody* b6 = app::tmp::BodyFactory::createBody(loc7, sphere.getMesh());

	btRigidBody* b7 = app::tmp::BodyFactory::createBody(loc8, sphere.getMesh());
	btRigidBody* b8 = app::tmp::BodyFactory::createBody(loc9, sphere.getMesh());
	btRigidBody* b9 = app::tmp::BodyFactory::createBody(loc10, sphere.getMesh());

	app::tmp::BodyFactory::createRoom(loc5, floor.getMesh(), w, floor.getShape());

	w.addRigidBody(b1);
	w.addRigidBody(b2);
	w.addRigidBody(b3);
	w.addRigidBody(b4);
	w.addRigidBody(b5);
	w.addRigidBody(b6);

	w.addRigidBody(b7);
	w.addRigidBody(b8);
	w.addRigidBody(b9);

	auto frameFn = [&fr]() {
		fr();
	};

	auto renderfn = [&view_port, &camera, &w]() {
		w.stepSimulation();
		w.render(view_port, camera);
	};

	app::EventLoop el(60);

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
