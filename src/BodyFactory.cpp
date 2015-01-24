/*
 * BodyFactory.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: domahony
 */

#include <memory>
#include "BodyFactory.h"
#include <btBulletDynamicsCommon.h>
#include "BoxMesh.h"
#include "RenderBody.h"

namespace app {
namespace tmp {


btRigidBody* BodyFactory::
createBody(const btTransform& location, std::shared_ptr<app::BoxMesh> mesh)
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
