/*
 * BlinPhonBasic.h
 *
 *  Created on: Feb 16, 2015
 *      Author: domahony
 */

#ifndef BLIN_PHON_BASIC_H_
#define BLIN_PHON_BASIC_H_

#include "types.h"
#include <iostream>

namespace app {
namespace gl {

class BlinPhonBasic {
public:

	BlinPhonBasic();

protected:
	const std::string vertex_source;
	const std::string fragment_source;

};

} /* namespace gl */
} /* namespace app */

#endif
