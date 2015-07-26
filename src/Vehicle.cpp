/*
 * Vehicle.cpp
 *
 *  Created on: Jul 25, 2015
 *      Author: domahony
 */

#include "Vehicle.h"
#include <iostream>

namespace app {
namespace gl {

using namespace std;

Vehicle::
Vehicle(std::shared_ptr<ShaderBase> shader):
	sphere("./media/sphere.dat", shader, 1.5),
	appObject(std::make_shared<app::gl::AppObject>(sphere.getMesh(),
			sphere.getShape<btConvexHullShape>(), btTransform::getIdentity()))
{

}


void Vehicle::
updateAction(btCollisionWorld* w, btScalar s)
{
}

} /* namespace gl */
} /* namespace app */
