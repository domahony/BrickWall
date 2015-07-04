/*
 * BodyFactory.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: domahony
 */

#include <memory>
#include "BodyFactory.h"
#include <btBulletDynamicsCommon.h>
#include "RenderBody.h"

namespace app {
namespace tmp {


void BodyFactory::
createRoom(const btTransform& location, std::shared_ptr<app::gl::Mesh> mesh,
		app::WorldPtr w, std::shared_ptr<btCollisionShape> shape)
{
	/*
	 * create floor
	 *
	 * create back wall
	 * rotate about the X axis
	 * translate -5 Z
	 * translate +5 Y
	 */

	//btCollisionShape* ground = new btStaticPlaneShape(btVector3(0,1,0), 1);
	btQuaternion rot0(btVector3(0, 0, 1), 0.0 * M_PI/180.0);
	btTransform t0(rot0, btVector3(0, 0, 0));
    app::RenderBody *rb = new RenderBody(mesh, t0 * location);
	btRigidBody *ret = new btRigidBody(0, rb, shape.get(), btVector3(0,0,0));
    ret->setUserPointer(rb);
    w->addRigidBody(ret);

	btQuaternion rot(btVector3(1, 0, 0), 90.0 * M_PI/180.0);
	btTransform t1(rot, btVector3(0, 10, -10));
 	btTransform loc2(location * t1);

	rb = new RenderBody(mesh, loc2);
	ret = new btRigidBody(0, rb, shape.get(), btVector3(0,0,0));
	ret->setUserPointer(rb);
	w->addRigidBody(ret);

	btQuaternion rot2(btVector3(0, 0, 1), 90 * M_PI/180.0);
	btTransform t2(rot2, btVector3(10, 10, 0));

 	btTransform loc3(location * t2);

	rb = new RenderBody(mesh, loc3);
	ret = new btRigidBody(0, rb, shape.get(), btVector3(0,0,0));
	ret->setUserPointer(rb);
	w->addRigidBody(ret);

	btQuaternion rot3(btVector3(0, 0, -1), 90 * M_PI/180.0);
	btTransform t3(rot3, btVector3(-10, 10, 0));

 	btTransform loc4(location * t3);

	rb = new RenderBody(mesh, loc4);
	ret = new btRigidBody(0, rb, shape.get(), btVector3(0,0,0));
	ret->setUserPointer(rb);
	w->addRigidBody(ret);

}

btRigidBody* BodyFactory::
createBody(const btTransform& location, std::shared_ptr<app::gl::Mesh> mesh)
{
	btCollisionShape* box = new btBoxShape(btVector3(1,1,1));
    btScalar mass(1);

    app::RenderBody *rb = new RenderBody(mesh, location);

    btVector3 fallInertia(0, 0, 0);
    box->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, rb, box, fallInertia);

    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);

    fallRigidBody->setUserPointer(rb);

    return fallRigidBody;
}


} /* namespace tmp */
} /* namespace app */
