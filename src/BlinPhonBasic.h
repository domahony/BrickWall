/*
 * BlinPhonBasic.h
 *
 *  Created on: Feb 16, 2015
 *      Author: domahony
 */

#ifndef BLIN_PHON_BASIC_H_
#define BLIN_PHON_BASIC_H_

#include "types.h"
#include "ShaderSource.h"
#include <iostream>

namespace app {
namespace gl {

class BlinPhonBasic : public ShaderSource {
public:

	BlinPhonBasic();

	const std::string get_vertex_source() const {
		return vertex_source;
	}

	const std::string get_fragment_source() const {
		return fragment_source;
	}

protected:
	const std::string vertex_source;
	const std::string fragment_source;

};

} /* namespace gl */
} /* namespace app */

#endif
