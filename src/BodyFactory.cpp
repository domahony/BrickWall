/*
 * BodyFactory.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: domahony
 */

#include "BodyFactory.h"
#include "RenderBody.h"
#include <btBulletDynamicsCommon.h>

namespace app {
namespace tmp {


btRigidBody* BodyFactory::
createBody()
{
	btCollisionShape* box = new btBoxShape(btVector3(1,1,1));
    btScalar mass(1);
    btTransform transform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0));

    app::RenderBody *rb = new RenderBody();

    btVector3 fallInertia(0, 0, 0);
    box->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, rb, box, fallInertia);

    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);

    fallRigidBody->setUserPointer(rb);

    return fallRigidBody;
}


} /* namespace tmp */
} /* namespace app */
