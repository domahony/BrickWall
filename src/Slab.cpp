/*
 * Slab.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: domahony
 */

#include "Slab.h"
#include "Mesh.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>

namespace app {
namespace gl {

Slab::
Slab(std::shared_ptr<app::gl::Mesh> mesh, std::shared_ptr<btCollisionShape> shape, const btTransform& pos)
	: AppObject(mesh, shape, pos), width(0), height(0)
{

}

Slab::
~Slab()
{

}

} /* namespace gl */
} /* namespace app */
