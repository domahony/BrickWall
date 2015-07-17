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

Maze::
Maze(std::shared_ptr<app::World> w) :
	shader(std::make_shared<app::gl::Shader2>()),
	floor("./media/plane.dat", shader, 1),
	mesh(floor.getMesh()),
	shape(floor.getShape<btBvhTriangleMeshShape>()),
	world(w)
{
	btRigidBody::btRigidBodyConstructionInfo info(0, nullptr, nullptr);

	btTransform tran(btTransform::getIdentity());
	std::shared_ptr<app::gl::AppObject> s(std::make_shared<app::gl::Slab>(mesh, shape, tran));
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(20, 0, 0));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(0, 0, -20));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(0, 0, -20));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(0, 0, -20));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(0, 0, -20));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(-20, 0, 0));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(-20, 0, 0));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(-20, 0, 0));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(-20, 0, 0));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);
}

void Maze::
addStraight()
{

}

void Maze::
addLeftTurn()
{

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
