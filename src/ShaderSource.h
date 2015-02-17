/*
 * ShaderSource.h
 *
 *  Created on: Feb 17, 2015
 *      Author: domahony
 */

#ifndef SHADERSOURCE_H_
#define SHADERSOURCE_H_

#include <string>

namespace app {
namespace gl {

class ShaderSource {
public:
	ShaderSource();

	virtual const std::string get_vertex_source() const = 0;
	virtual const std::string get_fragment_source()  const = 0;

	virtual ~ShaderSource();
};

} /* namespace gl */
} /* namespace app */

#endif /* SHADERSOURCE_H_ */
