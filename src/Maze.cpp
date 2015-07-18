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
	float width = 20;
	float length = 20;
	btVector3 halfX(width/2.f, 0, 0);
	btVector3 halfY(0, width/2.f, 0);
	btVector3 halfZ(0, 0, width/2.f);

	btQuaternion ZP90(btVector3(0, 0, 1), glm::radians(90.f));
	btQuaternion ZN90(btVector3(0, 0, 1), glm::radians(-90.f));
	btQuaternion XN90(btVector3(1, 0, 0), glm::radians(-90.f));
	btQuaternion XP90(btVector3(1, 0, 0), glm::radians(90.f));

	btRigidBody::btRigidBodyConstructionInfo info(0, nullptr, nullptr);

	btTransform tran(btTransform::getIdentity());
	std::shared_ptr<app::gl::AppObject> s(std::make_shared<app::gl::Slab>(mesh, shape, tran));
	world->addToWorld(s, info);
	slabs.push_back(s);

	btTransform l(ZP90, tran.getOrigin() + halfX + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	l = btTransform(ZN90, tran.getOrigin() - halfX + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);


	tran.setOrigin(tran.getOrigin() + btVector3(0, 0, -width));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	l = btTransform(ZP90, tran.getOrigin() + halfX + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	l = btTransform(XP90, tran.getOrigin() - halfZ + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	tran.setOrigin(tran.getOrigin() + btVector3(-width, 0, 0));
	s = std::make_shared<app::gl::Slab>(mesh, shape, tran);
	world->addToWorld(s, info);
	slabs.push_back(s);

	l = btTransform(XP90, tran.getOrigin() - halfZ + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	l = btTransform(XN90, tran.getOrigin() + halfZ + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);
	/*
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
	*/
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
