/*
 * BoxCreator.h
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#ifndef BOXCREATOR_H_
#define BOXCREATOR_H_

namespace app {
namespace gl {

#include "RenderBody.h"

class BoxCreator {
public:
	BoxCreator();
	virtual ~BoxCreator();

	app::RenderBody createBox();
};

} /* namespace gl */
} /* namespace app */

#endif /* BOXCREATOR_H_ */
