/*
 * Maze.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: domahony
 */

#include "Maze.h"
#include "World.h"
#include "Slab.h"
#include "Shader2.h"
#include "Camera.h"

namespace app {
namespace gl {

btQuaternion Maze::ZP90(btVector3(0, 0, 1), glm::radians(90.f));
btQuaternion Maze::ZN90(btVector3(0, 0, 1), glm::radians(-90.f));
btQuaternion Maze::XN90(btVector3(1, 0, 0), glm::radians(-90.f));
btQuaternion Maze::XP90(btVector3(1, 0, 0), glm::radians(90.f));

Maze::
Maze(std::shared_ptr<app::World> w, app::CameraPtr camera) :
	shader(std::make_shared<app::gl::Shader2>()),
	floor("./media/plane.dat", shader, 1),
	mesh(floor.getMesh()),
	shape(floor.getShape<btBvhTriangleMeshShape>()),
	world(w),
	pos(btTransform::getIdentity()),
	width(20),
	length(20),
	halfX(width/2.f, 0, 0),
	halfY(0, width/2.f, 0),
	halfZ(0, 0, width/2.f),
	info(0, nullptr, nullptr)
{
	app::ObjMesh cubeplus("./media/cubeplus.dat", shader, 2);
    auto cubeShape = cubeplus.getShape<btConvexHullShape>();

	btScalar mass(3.0);
	btVector3 inertia(0, 0, 0);
    cubeShape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo info(mass, nullptr, nullptr, inertia);

	btTransform loc1(btQuaternion(0,0,0,1), btVector3(0, 2, 0));
	std::shared_ptr<app::gl::AppObject> o(std::make_shared<app::gl::AppObject>(
			cubeplus.getMesh(), cubeShape, loc1));

	w->addToWorld(o, info);
	//w->addVehicle(&vehicle);

	addStraight();
	addLeftTurn();
	addStraight();
	addStraight();
	addRightTurn();
	addStraight();
	addStraight();
	addStraight();
	addRightTurn();
	addLeftTurn();
	addStraight();
	addStraight();
	addRightTurn();
	addStraight();
	addStraight();
	addStraight();
	addStraight();

}

void Maze::
addStraight()
{
	addSection(btTransform(ZN90, -halfX + halfY), btTransform(ZP90, halfX + halfY));
}

void Maze::
addSection(const btTransform& left, const btTransform& right)
{
	std::shared_ptr<app::gl::AppObject> s(std::make_shared<app::gl::Slab>(mesh, shape, pos));
	world->addToWorld(s, info);
	slabs.push_back(s);

	s = std::make_shared<app::gl::Slab>(mesh, shape, pos * right);
	world->addToWorld(s, info);
	slabs.push_back(s);

	s = std::make_shared<app::gl::Slab>(mesh, shape, pos * left);
	world->addToWorld(s, info);
	slabs.push_back(s);
	pos.setOrigin(pos.getOrigin() + quatRotate(pos.getRotation(), btVector3(0, 0, -length)));

}

void Maze::
addLeftTurn()
{
	btTransform delta(btQuaternion(btVector3(0, 1, 0), glm::radians(90.f)));
	pos = pos * delta;

	addSection(btTransform(XN90, halfZ + halfY), btTransform(ZP90, halfX + halfY));
}

void Maze::
addRightTurn()
{
	btTransform delta(btQuaternion(btVector3(0, 1, 0), glm::radians(-90.f)));
	pos = pos * delta;

	addSection(btTransform(XN90, halfZ + halfY), btTransform(ZN90, -halfX + halfY));
}

void Maze::
addFork()
{

}

void Maze::
addLeftFork()
{

}

void Maze::
addRightFork()
{

}

} /* namespace gl */
} /* namespace app */
