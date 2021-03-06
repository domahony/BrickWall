/*
 * Slab.h
 *
 *  Created on: Jul 13, 2015
 *      Author: domahony
 */

#ifndef SLAB_H_
#define SLAB_H_

#include <memory>
#include "AppObject.h"
#include "ObjMesh.h"

class btCollisionShape;

namespace app {

namespace gl {
class ShaderBase;
class Mesh;

class Slab : public AppObject {
public:
	Slab(const btTransform&);
	~Slab();

	float get_width() const {
		return width;
	}

	float get_height() const {
		return height;
	}

private:
	static std::shared_ptr<app::gl::ShaderBase> shader;
	static app::ObjMesh floor;
	static std::shared_ptr<app::gl::Mesh> mesh;
	static std::shared_ptr<btCollisionShape> shape;
	float width;
	float height;
};

} /* namespace gl */
} /* namespace app */

#endif /* SLAB_H_ */
