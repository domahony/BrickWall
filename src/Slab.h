/*
 * Slab.h
 *
 *  Created on: Jul 1, 2015
 *      Author: domahony
 */

#ifndef SLAB_H_
#define SLAB_H_

#include "ObjMesh.h"
#include "ShaderBase.h"
#include "RenderBody.h"
#include <memory>

namespace app {
namespace gl {

class Slab {
public:
	Slab(const float& size, ShaderPtr shader) :
		size(size),
		obj(std::make_shared<ObjMesh>("./media/plane.dat", shader, size)),
		render(std::make_shared<RenderBody>(obj->getMesh(), btTransform(btQuaternion::getIdentity(), btVector3(0, 0, 0)))),
		rigid(std::make_shared<btRigidBody>(0, render.get(), obj->getShape(), btVector3(0, 0, 0)))
	{
		rigid->setUserPointer(render.get());
	}

	const float get_size() const {
		return size;
	}


	const std::shared_ptr<btRigidBody> getRigidBody() {
		return rigid;
	}

private:
	const float size;
	const std::shared_ptr<ObjMesh> obj;
	const std::shared_ptr<RenderBody> render;
	const std::shared_ptr<btRigidBody> rigid;
};

} /* namespace gl */
} /* namespace app */

#endif /* SLAB_H_ */
