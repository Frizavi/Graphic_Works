#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


//������ �������� �� ������
static string readFile(const string& filePath) {
    ifstream file(filePath);

    string content; 
    string str;    

    while (getline(file, str)) {
        content += str + "\n"; 
    }
    file.close();
    return content; 
}

//������� ���������� �������
static GLuint compileShader(const string& code, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    const char* shaderSource = code.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    //�������� ������ ����������

    GLint success; //������

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        cerr << "ERROR: COMPILATION ERROR\n" << infoLog << endl;
    }
    return shader;
}

//�������� ������ �������� ���������
static void checkProgramErrors(GLuint program) {

    GLint success; //������

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        cerr << "ERROR: LINKING ERROR\n" << infoLog << endl;
    }
}

//�������� ��������
static GLuint loadShader(const string& vertexPath, const string& fragmentPath) {

    //������ ��������
    string vertexCode = readFile(vertexPath);
    string fragmentCode = readFile(fragmentPath);

    //���������� ��������
    GLuint vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

    //�������� ��������� ���������
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //�������� ������ ��������
    checkProgramErrors(shaderProgram);

    //�������� ��������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

//��������� uniform-����������
static void setUniform4f(GLuint program, const string& name, float f0, float f1, float f2, float f3) {
    glUniform4f(glGetUniformLocation(program, name.c_str()), f0, f1, f2, f3);
}