/*
 * Vehicle.h
 *
 *  Created on: Jul 25, 2015
 *      Author: domahony
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <memory>
#include <bullet/BulletDynamics/Dynamics/btActionInterface.h>
#include "ObjMesh.h"
#include "AppObject.h"

namespace app {
namespace gl {

class Vehicle: public btActionInterface {
public:
	Vehicle(std::shared_ptr<app::gl::ShaderBase>);
	~Vehicle() {
		// TODO Auto-generated destructor stub
	}

	void updateAction(btCollisionWorld*, btScalar);

	void debugDraw(btIDebugDraw* d) {

	}

private:
	app::ObjMesh sphere;
	std::shared_ptr<app::gl::AppObject> appObject;

};

} /* namespace gl */
} /* namespace app */

#endif /* VEHICLE_H_ */
