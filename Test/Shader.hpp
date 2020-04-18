#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "base.hpp"

using std::string;
namespace LaughCrab {
class Shader
{
public:
	Shader() = default;
	Shader(const GLchar* shaderPath, const GLenum shaderClass);

	const GLuint& getShaderId() const { return shaderId; }
	virtual ~Shader() = default;
private:
	string shaderType(const GLenum shaderClass);
private:
	GLuint shaderId;
};
}
#endif // !__SHADER_H__