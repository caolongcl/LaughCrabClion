#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__

#include <map>
#include "Shader.hpp"

namespace LaughCrab {
	using std::map;

	class ShaderProgram
	{
	public:
		ShaderProgram(const map<GLenum, const GLchar*> &pathList);
		virtual ~ShaderProgram() = default;
		const GLuint& getProgramId()const { return programId; }
		void useProgram() { glUseProgram(programId); }
	private:
		GLuint programId;
	};
}
#endif