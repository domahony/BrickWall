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

	rigid = std::make_shared<btRigidBody>(c);
	rigid->setUserPointer(this);
	world->addRigidBody(rigid.get());
}

void AppObject::
render(const app::CameraPtr& c, const app::ViewPort& vp) const
{
	mesh->render(c, vp, wtransform);
}

void AppObject::
left()
{
	rigid->translate(btVector3(-1, 0, 0));
	//rigid->setCollisionFlags(rigid->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	rigid->setActivationState(DISABLE_DEACTIVATION);
}

void AppObject::
right()
{
	rigid->translate(btVector3(1, 0, 0));
	//rigid->setCollisionFlags(rigid->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	rigid->setActivationState(DISABLE_DEACTIVATION);
}

void AppObject::
forward()
{
	rigid->translate(btVector3(0, 0, 1));
	//rigid->setCollisionFlags(rigid->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	rigid->setActivationState(DISABLE_DEACTIVATION);
}

void AppObject::
back()
{
	rigid->translate(btVector3(0, 0, -1));
	//rigid->setCollisionFlags(rigid->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	rigid->setActivationState(DISABLE_DEACTIVATION);
}

int
keyboard_callback(void *p, SDL_Event *e)
{
	int ret = 1;
	if (e->type == SDL_KEYDOWN) {
		AppObject* c = static_cast<AppObject*>(p);

		switch (e->key.keysym.sym) {
		case SDLK_h: //left
			c->left();
			ret = 1;
			break;
		case SDLK_l:  //right
			c->right();
			ret = 0;
			break;
		case SDLK_k: //forward (up)
			c->forward();
			ret = 0;
			break;
		case SDLK_j: //back (down)
			c->back();
			ret = 0;
			break;
		default:
			break;
		}
	}

	return ret;
}

} /* namespace gl */
} /* namespace app */
