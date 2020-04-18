#include "Shader.hpp"

using namespace std;

namespace LaughCrab {
    Shader::Shader(const GLchar *shaderPath, const GLenum shaderClass) {
        string shaderCode;
        ifstream shaderSource;

        shaderSource.exceptions(ifstream::badbit);

        try {
            shaderSource.open(shaderPath);

            if (!shaderSource.is_open()) {
                cout << "!open!!!!!!" << endl;
            }

            stringstream shaderStream;
            shaderStream << shaderSource.rdbuf();

            shaderSource.close();
            shaderCode = shaderStream.str();
        }
        catch (ifstream::failure& e) {
            cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
        }

        GLint success = 1;
        GLchar infoLog[512];
        const GLchar *shaderCodeChar = shaderCode.c_str();

        shaderId = glCreateShader(shaderClass);
        glShaderSource(shaderId, 1, &shaderCodeChar, 0);
        glCompileShader(shaderId);

        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderId, sizeof(infoLog), 0, infoLog);
            cout << "ERROR::SHADER::" << shaderType(shaderClass)
                 << "::COMPILATION_FAILED " << shaderCode << "  "<< infoLog << endl;
        }
    }

    string Shader::shaderType(const GLenum shaderClass) {
        string ret;
        switch (shaderClass) {
            case GL_VERTEX_SHADER:
                ret = string("VERTEX");
                break;
            case GL_FRAGMENT_SHADER:
                ret = string("FRAGMENT");
                break;
            default:
                ret = string("UNKNOWN");
                break;
        }

        return ret;
    }
}
