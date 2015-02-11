/*
 * RenderObject.cpp
 *
 *  Created on: Feb 10, 2015
 *      Author: domahony
 */

#include "RenderObject.h"
#include "RenderBody.h"
#include <vector>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

namespace app {

class RenderObject::impl {
public:

void
render(const app::Camera& c, const app::ViewPort& vp) const {

	for (auto b = body.begin(); b != body.end(); ++b) {
		(*b)->render(c, vp);
	}
}

void
add_body(shared_ptr<RenderBody> b) {
	body.push_back(b);
}


private:
	vector<shared_ptr<RenderBody>> body;
};

RenderObject::RenderObject() : pimpl(new RenderObject::impl()) {
	// TODO Auto-generated constructor stub

}

RenderObject::~RenderObject() {
	// TODO Auto-generated destructor stub
}

void RenderObject::add_body(shared_ptr<RenderBody> b) {
	pimpl->add_body(b);
}

void RenderObject::
render(const app::Camera& c, const app::ViewPort& vp) const
{
	pimpl->render(c, vp);
}


} /* namespace app */
