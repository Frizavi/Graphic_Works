#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


//Чтение шейдеров из файлов
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

//Функция компиляции шейдера
static GLuint compileShader(const string& code, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    const char* shaderSource = code.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    //Проверка ошибок компиляции

    GLint success; //флажок

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        cerr << "ERROR: COMPILATION ERROR\n" << infoLog << endl;
    }
    return shader;
}

//Проверка ошибок линковки программы
static void checkProgramErrors(GLuint program) {

    GLint success; //флажок

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        cerr << "ERROR: LINKING ERROR\n" << infoLog << endl;
    }
}

//Загрузка шейдеров
static GLuint loadShader(const string& vertexPath, const string& fragmentPath) {

    //Чтение шейдеров
    string vertexCode = readFile(vertexPath);
    string fragmentCode = readFile(fragmentPath);

    //Компиляция шейдеров
    GLuint vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

    //Создание шейдерной программы
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //Проверка ошибок линковки
    checkProgramErrors(shaderProgram);

    //Удаление шейдеров
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

//Установка uniform-переменной
static void setUniform4f(GLuint program, const string& name, float f0, float f1, float f2, float f3) {
    glUniform4f(glGetUniformLocation(program, name.c_str()), f0, f1, f2, f3);
}