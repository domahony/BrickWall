/*
 * main.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: domahony
 */

#include <random>
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
#include "Slab.h"

using std::function;
using std::unique_ptr;

static function<void ()> windowFn();

void
populateSimulation(const app::ObjMesh& cubeplus, const app::ObjMesh& sphere, app::WorldPtr w)
{
	std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<> dis(0.1,500);
    std::uniform_real_distribution<> xdis(-9,9);
    std::uniform_real_distribution<> ydis(25,400);
    std::uniform_real_distribution<> zdis(-9,9);

    auto sphereShape = sphere.getShape<btConvexHullShape>();
    auto cubeShape = cubeplus.getShape<btConvexHullShape>();

	btScalar mass(dis(gen));
	btVector3 inertia(0, 0, 0);
    sphereShape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo info(mass, nullptr, nullptr, inertia);

	btTransform loc1(btQuaternion(0,0,0,1), btVector3(xdis(gen), ydis(gen), zdis(gen)));
	std::shared_ptr<app::gl::AppObject> o(std::make_shared<app::gl::AppObject>(
			cubeplus.getMesh(), cubeShape, loc1));
	w->addToWorld(o, info);

	mass = dis(gen);
    sphereShape->calculateLocalInertia(mass, info.m_localInertia);

	btTransform loc2(btQuaternion(0,0,0,1), btVector3(xdis(gen), ydis(gen), zdis(gen)));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphereShape, loc2);
	w->addToWorld(o, info);

	mass = dis(gen);
    sphereShape->calculateLocalInertia(mass, info.m_localInertia);

	btTransform loc3(btQuaternion(0,0,0,1), btVector3(xdis(gen), ydis(gen), zdis(gen)));
	o = std::make_shared<app::gl::AppObject>(cubeplus.getMesh(), cubeShape, loc3);
	w->addToWorld(o, info);

	mass = dis(gen);
    sphereShape->calculateLocalInertia(mass, info.m_localInertia);

	btTransform loc4(btQuaternion(0,0,0,1), btVector3(xdis(gen), ydis(gen), zdis(gen)));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphereShape, loc4);
	w->addToWorld(o, info);

	mass = dis(gen);
    sphereShape->calculateLocalInertia(mass, info.m_localInertia);

	btTransform loc6(btQuaternion(0,0,0,1), btVector3(xdis(gen), ydis(gen), zdis(gen)));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphereShape, loc6);
	w->addToWorld(o, info);

	mass = dis(gen);
    cubeShape->calculateLocalInertia(mass, info.m_localInertia);

	btTransform loc7(btQuaternion(0,0,0,1), btVector3(xdis(gen), ydis(gen), zdis(gen)));
	o = std::make_shared<app::gl::AppObject>(cubeplus.getMesh(), cubeShape, loc7);
	w->addToWorld(o, info);

	mass = dis(gen);
    sphereShape->calculateLocalInertia(mass, info.m_localInertia);

	btTransform loc8(btQuaternion(0,0,0,1), btVector3(xdis(gen), ydis(gen), zdis(gen)));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphereShape, loc8);
	w->addToWorld(o, info);

	mass = dis(gen);
    sphereShape->calculateLocalInertia(mass, info.m_localInertia);

	btTransform loc9(btQuaternion(0,0,0,1), btVector3(xdis(gen), ydis(gen), zdis(gen)));
	o = std::make_shared<app::gl::AppObject>(sphere.getMesh(), sphereShape, loc9);
	w->addToWorld(o, info);

	mass = dis(gen);
    cubeShape->calculateLocalInertia(mass, info.m_localInertia);

	btTransform loc10(btQuaternion(0,0,0,1), btVector3(xdis(gen), ydis(gen), zdis(gen)));
	o = std::make_shared<app::gl::AppObject>(cubeplus.getMesh(), cubeShape, loc10);
	w->addToWorld(o, info);


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

	populateSimulation(cubeplus, sphere, w);

	btTransform loc5(btQuaternion(0,0,0,1), btVector3(0, 0, 0));
	btTransform loc5b(btQuaternion(btVector3(0, 1, 0), 72.f * M_PI/180.f), btVector3(-65, -10, 0));
	app::tmp::BodyFactory::createRoom(loc5, floor.getMesh(), w, floor.getShape<btBvhTriangleMeshShape>());

	app::gl::Slab slab(loc5);

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
