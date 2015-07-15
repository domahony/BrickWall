/*
 * RenderBody.h
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#ifndef RENDERBODY_H_
#define RENDERBODY_H_

#include <iostream>
#include <bullet/LinearMath/btMotionState.h>
#include <vector>
#include <memory>
#include "Camera.h"
#include "ViewPort.h"


namespace app {

	namespace gl {
		class Mesh;
	}

class RenderBody: public btMotionState {
public:
	RenderBody(std::shared_ptr<app::gl::Mesh> mesh, const btTransform& trans) : mesh(mesh), transform(trans) {

	}

	virtual ~RenderBody() {

	}

	void getWorldTransform(btTransform& trans) const {
		trans = transform;
	}

	void setWorldTransform(const btTransform& trans) {
		transform = trans;
		std::cout << "Yeah! " << transform.getOrigin().getX() << ", " << transform.getOrigin().getY() << std::endl;
	}

	void render(const app::CameraPtr& c, const app::ViewPort& vp) const;

private:
	btTransform transform;
	std::shared_ptr<app::gl::Mesh> mesh;

};

} /* namespace app */

#endif /* RENDERBODY_H_ */
