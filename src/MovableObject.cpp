/*
 * MovableObject.cpp
 *
 *  Created on: Jul 29, 2015
 *      Author: domahony
 */

#include "MovableObject.h"

namespace app {
namespace gl {

MovableObject::
MovableObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<btCollisionShape> shape, const btTransform& pos) :
	AppObject(mesh, shape, pos)
{

}

MovableObject::
~MovableObject()
{

}

} /* namespace gl */
} /* namespace app */
