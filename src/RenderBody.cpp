/*
 * RenderBody.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#include "RenderBody.h"
#include "Mesh.h"

namespace app {

void RenderBody::
render(const app::Camera& c, const app::ViewPort& vp) const {
		mesh->render(c, vp, transform);
	}

} /* namespace app */
