/*
 * Renderer.h
 *
 *  Created on: Dec 30, 2014
 *      Author: domahony
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <glm/glm.hpp>
#include "GroundGL.h"
#include "Body.h"
#include "RenderBody.h"
#include "Camera.h"
#include "ViewPort.h"

namespace app {
namespace gl {

class Renderer {
public:
	Renderer(const app::ViewPort&, const app::Camera&);
	virtual ~Renderer();

	void render(GroundGL&);
	void render(Body*);
	void render(const app::ViewPort&, const app::Camera&, const app::RenderBody&) const;

private:
	app::ViewPort vp;
	app::Camera camera;
};

} /* namespace gl */
} /* namespace app */

#endif /* RENDERER_H_ */
