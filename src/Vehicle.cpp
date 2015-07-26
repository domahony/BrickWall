/*
 * Vehicle.cpp
 *
 *  Created on: Jul 25, 2015
 *      Author: domahony
 */

#include "Vehicle.h"
#include "Camera.h"
#include "World.h"
#include <iostream>

namespace app {
namespace gl {

using namespace std;

static btTransform get_init_location(app::CameraPtr c)
{
	glm::vec3 v = c->getViewPos();
	glm::mat4 m = c->getOrientation();

	glm::vec4 v1(m * glm::vec4(0,13,-35,0));

	return btTransform(btQuaternion::getIdentity(),
			btVector3(
					v.x + v1.x,
					v.y + v1.y,
					v.z + v1.z));
}

Vehicle::
Vehicle(std::shared_ptr<app::World> w, std::shared_ptr<ShaderBase> shader, app::CameraPtr camera):
	sphere("./media/sphere.dat", shader, 1.5),
	appObject(std::make_shared<app::gl::AppObject>(sphere.getMesh(),
			sphere.getShape<btConvexHullShape>(), get_init_location(camera)))
{
	btRigidBody::btRigidBodyConstructionInfo info(1.0, nullptr, nullptr);
	w->addToWorld(appObject, info);
}


void Vehicle::
updateAction(btCollisionWorld* w, btScalar s)
{
}

} /* namespace gl */
} /* namespace app */
