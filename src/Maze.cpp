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

namespace app {
namespace gl {

btQuaternion Maze::ZP90(btVector3(0, 0, 1), glm::radians(90.f));
btQuaternion Maze::ZN90(btVector3(0, 0, 1), glm::radians(-90.f));
btQuaternion Maze::XN90(btVector3(1, 0, 0), glm::radians(-90.f));
btQuaternion Maze::XP90(btVector3(1, 0, 0), glm::radians(90.f));

Maze::
Maze(std::shared_ptr<app::World> w) :
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

	addStraight();
	addLeftTurn();
	addStraight();
	addLeftTurn();
	addStraight();

}

void Maze::
addStraight()
{
	btTransform t(btTransform::getIdentity());

	std::shared_ptr<app::gl::AppObject> s(std::make_shared<app::gl::Slab>(mesh, shape, t * pos));
	world->addToWorld(s, info);
	slabs.push_back(s);

	btTransform l(ZP90, t.getOrigin() + halfX + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, pos * l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	l = btTransform(ZN90, t.getOrigin() -  halfX + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, pos * l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	pos.setOrigin(pos.getOrigin() + quatRotate(pos.getRotation(), btVector3(0, 0, -length)));
}

void Maze::
addLeftTurn()
{
	/*
	 * need to change turn left by 90degrees (-90 deg around Y axis);
	 */
	btTransform t(btTransform::getIdentity());

	btTransform l(ZP90, t.getOrigin() +  halfX + halfY);
	std::shared_ptr<app::gl::AppObject> s(std::make_shared<app::gl::Slab>(mesh, shape, pos * l));
	world->addToWorld(s, info);
	slabs.push_back(s);

	pos = pos * btTransform(btQuaternion(btVector3(0, 1, 0), glm::radians(90.f)));

	s = std::make_shared<app::gl::Slab>(mesh, shape, t * pos);
	world->addToWorld(s, info);
	slabs.push_back(s);

	l = btTransform(ZP90, t.getOrigin() + halfX + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, pos * l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	pos.setOrigin(pos.getOrigin() + quatRotate(pos.getRotation(), btVector3(0, 0, -length)));
}

void Maze::
addRightTurn()
{

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
