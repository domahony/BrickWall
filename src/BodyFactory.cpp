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


btRigidBody* BodyFactory::
createRoom(const btTransform& location, std::shared_ptr<app::gl::Mesh> mesh)
{

	/*
    transform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0))),
    groundShape(new btStaticPlaneShape(btVector3(0, 1, 0), 1)),
    groundRigidBody(0)
{
*/
	/*
    btRigidBody::btRigidBodyConstructionInfo
                    groundRigidBodyCI(0, this, groundShape, btVector3(0, 0, 0));

    groundRigidBody = new btRigidBody(groundRigidBodyCI);

    */
	btCollisionShape* ground = new btStaticPlaneShape(btVector3(0,1,0), 1);
    app::RenderBody *rb = new RenderBody(mesh, location);

	btRigidBody *ret = new btRigidBody(0, rb, ground, btVector3(0,0,0));

    ret->setUserPointer(rb);

    return ret;
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
