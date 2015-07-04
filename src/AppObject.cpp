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
AppObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<btCollisionShape> shape) :
mesh(mesh), shape(shape)
{

}

void AppObject::
addToWorld(app::World& world, const btRigidBody::btRigidBodyConstructionInfo& ctor)
{
	btRigidBody::btRigidBodyConstructionInfo c(ctor);
	c.m_motionState = this;
	c.m_collisionShape = shape.get();
	rigid = std::make_shared<btRigidBody>(c);
}

void AppObject::
render(const app::CameraPtr& c, const app::ViewPort& vp) const
{
	mesh->render(c, vp, wtransform);
}

} /* namespace gl */
} /* namespace app */
