/*
 * AppObject.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: domahony
 */

#include "AppObject.h"
#include "World.h"

namespace app {
namespace gl {

AppObject::
AppObject(app::World& world)
{
	world.addRigidBody(rigid.get());
}


void AppObject::
render(const app::CameraPtr& c, const app::ViewPort& vp) const
{
	mesh->render(c, vp, wtransform * local_size);
}

} /* namespace gl */
} /* namespace app */
