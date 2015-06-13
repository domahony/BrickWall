/*
 * Shader2.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: domahony
 */

#include "Shader2.h"

namespace app {
namespace gl {

static const
GLchar* getVS() {
	return R"(#version 150 core
    in vec3 position;
    in vec3 normal;
    out vec3 normOut;
    out vec3 pos;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;
    uniform vec3 viewPos;
    uniform vec3 lightPos;
    void main() {
       gl_Position = proj * view * model * vec4(position, 1.0);
       normOut = normal; 
       pos = position;
    }
)";
}

static const
GLchar* getFS()
{
	return R"(#version 150 core
    
    in vec3 normOut;
    in vec3 pos;
    out vec4 outColor;
    uniform vec3 viewPos;
    uniform vec3 lightPos;
    void main() {

       vec4 constantColor = vec4(0.9, 0.9, 0.9, 1.0);
       float invOmniRad = 1.0/190.5;
       vec3 omniColor = vec3(1.0, 1.0, 1.0);
       vec3 ambientLightColor = vec3(0.2, 0.2, 0.2);
       float specExponent = 15000;
       vec4 mattDiff = vec4(1.0, 1.0, 1.0, 1.0);
       vec4 mattSpec = mattDiff;

       vec3 N = normalize(normOut);
       vec3 L = lightPos - pos; 
       float dist = length(L);
       L /= dist;

       vec3 V = normalize(viewPos - pos);
       vec3 H = normalize(V + L);

       vec3 lightColor = omniColor * max(1 - dist * invOmniRad, 0);
       float diffFactor = max(dot(N,L), 0);
       float specFactor = pow(max(dot(N,H), 0), specExponent);

       vec3 diffColor = lightColor * diffFactor + ambientLightColor;
       vec3 specColor = lightColor * specFactor;

       outColor = mattDiff;
       outColor.rgb *= diffColor;
       outColor.rgb += mattSpec.rgb * specColor;

       outColor *= constantColor;

       //outColor = vec4(1.0,1.0,1.0,1.0);
    };
)";
}

Shader2::
Shader2() : ShaderBase(getVS(), getFS())
{

}

} /* namespace gl */
} /* namespace app */
