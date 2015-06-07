/*
 * RenderObject.h
 *
 *  Created on: Feb 10, 2015
 *      Author: domahony
 */

#ifndef RENDEROBJECT_H_
#define RENDEROBJECT_H_

#include <memory>
#include "Camera.h"
#include "ViewPort.h"

namespace app {

class RenderBody;

class RenderObject {
public:
	RenderObject();
	virtual ~RenderObject();

	void render(const app::CameraPtr& c, const app::ViewPort& vp) const;
	void add_body(std::shared_ptr<RenderBody> b);

private:
	class impl;
	std::unique_ptr<impl> pimpl;
};

} /* namespace app */

#endif /* RENDEROBJECT_H_ */
