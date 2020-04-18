#include "ShaderProgram.hpp"

#include <vector>

using namespace std;
namespace LaughCrab {

    ShaderProgram::ShaderProgram(const map<GLenum, const GLchar *> &pathList) {
        programId = glCreateProgram();

        vector<Shader *> pshaderVec;
        for (auto &path : pathList) {
            Shader *pshader = new Shader(path.second, path.first);
            pshaderVec.push_back(pshader);
            glAttachShader(programId, pshader->getShaderId());
        }
        glLinkProgram(programId);

        GLint success = 1;
        GLchar infoLog[512];

        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programId, sizeof(infoLog), 0, infoLog);
            cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED " << infoLog << endl;
        }

        for (auto &pshader : pshaderVec) {
            glDeleteShader(pshader->getShaderId());
            delete pshader;
        }
    }
}