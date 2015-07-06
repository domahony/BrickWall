/*
 * AppObject.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: domahony
 */

#include "AppObject.h"
#include "World.h"
#include "bullet/btBulletDynamicsCommon.h"

namespace app {
namespace gl {

AppObject::
AppObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<btCollisionShape> shape, const btTransform& pos) :
mesh(mesh), shape(shape), wtransform(pos)
{

}

void AppObject::
addToWorld(app::WorldPtr world, const btRigidBody::btRigidBodyConstructionInfo& ctor)
{
	btRigidBody::btRigidBodyConstructionInfo c(ctor);
	c.m_motionState = this;

	if (!c.m_collisionShape)
		c.m_collisionShape = shape.get();

	//rigid = std::make_shared<btRigidBody>(c);
	rigid = std::make_shared<btRigidBody>(c.m_mass, this, c.m_collisionShape, btVector3(0, 0, 0));
	rigid->setUserPointer(this);
	world->addRigidBody(rigid.get());
}

void AppObject::
render(const app::CameraPtr& c, const app::ViewPort& vp) const
{
	mesh->render(c, vp, wtransform);
}

} /* namespace gl */
} /* namespace app */
