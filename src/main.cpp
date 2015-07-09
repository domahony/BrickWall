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
#include "Shader2.h"
#include "BoxMesh.h"
#include "ObjMesh.h"
#include "EventLoop.h"
#include "World.h"
#include "FrameRate.h"
#include "ViewPort.h"
#include "Camera.h"
#include "BodyFactory.h"
#include <btBulletDynamicsCommon.h>
#include "AppObject.h"

using std::function;
using std::unique_ptr;

static function<void ()> windowFn();

void
populateSimulation(const app::ObjMesh& cubeplus, const app::ObjMesh& sphere,
		app::WorldPtr w, std::vector<std::shared_ptr<app::gl::AppObject>>& sim)
{
	btScalar mass(50);
	btVector3 inertia(0, 0, 0);
    cubeplus.getShape<btConvexHullShape>()->calculateLocalInertia(mass, inertia);

	//btRigidBody::btRigidBodyConstructionInfo info(mass, nullptr, new btBoxShape(btVector3(1,1,1)), inertia);
	btRigidBody::btRigidBodyConstructionInfo info(mass, nullptr, nullptr, inertia);

	btTransform loc1(btQuaternion(0,0,0,1), btVector3(0,50,0));
	std::shared_ptr<app::gl::AppObject> o(std::make_shared<app::gl::AppObject>(
			cubeplus.getMesh(), cubeplus.getShape<btConvexHullShape>(), loc1));
	o->addToWorld(w, info);
	sim.push_back(o);

	btTransform loc2(btQuaternion(0,0,0,1), btVector3(-0.33,48,6));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphere.getShape<btConvexHullShape>(), loc2);
	o->addToWorld(w, info);
	sim.push_back(o);

	btTransform loc3(btQuaternion(0,0,0,1), btVector3(0.25,52,0));
	o = std::make_shared<app::gl::AppObject>(cubeplus.getMesh(), cubeplus.getShape<btConvexHullShape>(), loc3);
	o->addToWorld(w, info);
	sim.push_back(o);

	btTransform loc4(btQuaternion(0,0,0,1), btVector3(0.5,50,1));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphere.getShape<btConvexHullShape>(), loc4);
	o->addToWorld(w, info);
	sim.push_back(o);

	btTransform loc6(btQuaternion(0,0,0,1), btVector3(-5,55,6));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphere.getShape<btConvexHullShape>(), loc6);
	o->addToWorld(w, info);
	sim.push_back(o);

	btTransform loc7(btQuaternion(0,0,0,1), btVector3(-1,20,0));
	o = std::make_shared<app::gl::AppObject>(cubeplus.getMesh(), cubeplus.getShape<btConvexHullShape>(), loc7);
	o->addToWorld(w, info);
	sim.push_back(o);

	btTransform loc8(btQuaternion(0,0,0,1), btVector3(-8.0, 500,-8.5));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphere.getShape<btConvexHullShape>(), loc8);
	o->addToWorld(w, info);
	sim.push_back(o);

	btTransform loc9(btQuaternion(0,0,0,1), btVector3(5,75,0));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphere.getShape<btConvexHullShape>(), loc9);
	o->addToWorld(w, info);
	sim.push_back(o);

	btTransform loc10(btQuaternion(0,0,0,1), btVector3(-9,60,-9));
	o = std::make_shared<app::gl::AppObject>(cubeplus.getMesh(), cubeplus.getShape<btConvexHullShape>(), loc10);
	o->addToWorld(w, info);
	sim.push_back(o);


}

int
main(int argc, char **argv)
{
	auto swapbuffer = windowFn();

	app::FrameRate fr;

	app::ViewPort view_port;
	app::CameraPtr camera(new app::Camera);
	app::WorldPtr w = std::make_shared<app::World>();
	std::shared_ptr<app::gl::ShaderBase> shader(new app::gl::Shader2());

	app::ObjMesh floor("./media/plane.dat", shader, 1);
	app::ObjMesh cubeplus("./media/cubeplus.dat", shader, 2);
	app::ObjMesh cube("./media/cube.dat", shader);
	app::ObjMesh sphere("./media/sphere.dat", shader, 1.5);

	std::vector<std::shared_ptr<app::gl::AppObject>> objects;
	populateSimulation(cubeplus, sphere, w, objects);

	btTransform loc5(btQuaternion(0,0,0,1), btVector3(0, 0, 0));
	btTransform loc5b(btQuaternion(btVector3(0, 1, 0), 72.f * M_PI/180.f), btVector3(-65, -10, 0));
	app::tmp::BodyFactory::createRoom(loc5, floor.getMesh(), w, floor.getShape<btBvhTriangleMeshShape>());
	//app::tmp::BodyFactory::createRoom(loc5b, floor.getMesh(), w, floor.getShape());

	/*
	btRigidBody::btRigidBodyConstructionInfo info(0, nullptr, nullptr);
	app::gl::AppObject ao(floor.getMesh(), floor.getShape(), loc5);
	ao.addToWorld(w, info);
	*/

	//app::gl::Maze maze(w, shader, 10, 10);

	auto frameFn = [&fr]() {
		fr();
	};


	auto renderfn = [&view_port, &camera, &w]() {
		w->stepSimulation();
		w->render(view_port, camera);
	};

	app::EventLoop el(60, camera, w);

	//el.addFn(frameFn);
	el.addFn(renderfn);
	el.addFn(swapbuffer);
	el.run();

	return 0;
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
