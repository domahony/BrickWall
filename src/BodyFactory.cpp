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
createRoom(const btTransform& location, std::shared_ptr<app::gl::Mesh> mesh, app::World& w)
{
	/*
	 * create floor
	 *
	 * create back wall
	 * rotate about the X axis
	 * translate -5 Z
	 * translate +5 Y
	 */

	btCollisionShape* ground = new btStaticPlaneShape(btVector3(0,1,0), 1);
    app::RenderBody *rb = new RenderBody(mesh, location);
	btRigidBody *ret = new btRigidBody(0, rb, ground, btVector3(0,0,0));
    ret->setUserPointer(rb);
    w.addRigidBody(ret);

	btQuaternion rot(btVector3(1, 0, 0), 90.0 * M_PI/180.0);
	//btTransform t1(rot, btVector3(0, 5, -5));
	btTransform t1(btQuaternion(0,0,0,1), btVector3(0, 5, -5));

 	btTransform loc2(location * t1);

	btCollisionShape *ground2 = new btStaticPlaneShape(btVector3(0, 0, -1), 0);
	app::RenderBody *rb2 = new RenderBody(mesh, loc2);
	btRigidBody* ret2 = new btRigidBody(0, rb2, ground2, btVector3(0,0,0));
	ret2->setUserPointer(rb2);
	w.addRigidBody(ret2);
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
