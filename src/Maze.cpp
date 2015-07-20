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
	dir(btQuaternion::getIdentity()),
	width(20),
	length(20),
	halfX(width/2.f, 0, 0),
	halfY(0, width/2.f, 0),
	halfZ(0, 0, width/2.f),
	info(0, nullptr, nullptr)
{

	addStraight();
	addStraight();
	addLeftTurn();
	//addStraight();
	/*
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
	*/
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
	std::shared_ptr<app::gl::AppObject> s(std::make_shared<app::gl::Slab>(mesh, shape, pos));
	world->addToWorld(s, info);
	slabs.push_back(s);

	btTransform l(dir * ZP90, pos.getOrigin() + halfX + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	l = btTransform(dir * ZN90, pos.getOrigin() - halfX + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	pos.setOrigin(pos.getOrigin() + quatRotate(dir, btVector3(0, 0, -length)));
}

void Maze::
addLeftTurn()
{
	/*
	 * need to change turn left by 90degrees (-90 deg around Y axis);
	 */

	dir = btQuaternion(btVector3(0, 1, 0), glm::radians(90.f)) * dir;
	addStraight();

	/*
	std::shared_ptr<app::gl::AppObject> s(std::make_shared<app::gl::Slab>(mesh, shape, pos));
	world->addToWorld(s, info);
	slabs.push_back(s);

	btTransform l(ZP90, pos.getOrigin() + halfX + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	l = btTransform(XP90, pos.getOrigin() - halfZ + halfY);
	s = std::make_shared<app::gl::Slab>(mesh, shape, l);
	world->addToWorld(s, info);
	slabs.push_back(s);

	pos.setOrigin(pos.getOrigin() + btVector3(-width, 0, 0));
	*/
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
