#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>
#include <type_ptr.hpp>
#include <GL/glew.h>

class Shader {
public:
    unsigned int shaderProgramID;

    Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode = loadFile(vertexPath);
        std::string fragmentCode = loadFile(fragmentPath);

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex = compileShader(GL_VERTEX_SHADER, vShaderCode);
        unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fShaderCode);

        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertex);
        glAttachShader(shaderProgramID, fragment);
        glLinkProgram(shaderProgramID);
        checkProgramLinking(shaderProgramID);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() {
        glUseProgram(shaderProgramID);
    }

    void setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value);
    }

    void setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
    }

    void setVec3(const std::string& name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &value[0]);
    }

    void setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    std::string loadFile(const char* path) {
        std::ifstream shaderFile(path);
        std::stringstream shaderStream;

        if (!shaderFile.is_open()) {
            std::cerr << "Could not open file: " << path << std::endl;
            return "";
        }

        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    }

    GLuint compileShader(GLenum shaderType, const char* shaderCode) {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderCode, nullptr);
        glCompileShader(shader);

        GLint success;
        GLchar infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Shader Compilation Error: " << infoLog << std::endl;
        }

        return shader;
    }

    void checkProgramLinking(GLuint program) {
        GLint success;
        GLchar infoLog[1024];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 1024, nullptr, infoLog);
            std::cerr << "Program Linking Error: " << infoLog << std::endl;
        }
    }
};

#endif