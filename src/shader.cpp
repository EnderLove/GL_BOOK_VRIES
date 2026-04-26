#include "../include/shader.h"

#define LOG_BUFFER_SIZE 512

Shader::Shader(const char *vertexPath, const char *fragmentPath){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        // Open files 
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        // Read file's buffer constents into streams 
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        // Close file handlers 
        vShaderFile.close();
        fShaderFile.close();

        // Convert stream into string 
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
    } catch (std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_FOUND_SUCCESFULLY_READ::" << e.what() << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[LOG_BUFFER_SIZE]; // INFO LOG BUFFER

    // VERTEX SHADER 
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertex, LOG_BUFFER_SIZE, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    // FRAGMENT SHADER  
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragment, LOG_BUFFER_SIZE, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    // SHADER PROGRAM
    ID = glCreateProgram();

    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(ID, LOG_BUFFER_SIZE, NULL, infoLog);
        printf("ERROR::lINKING::SHADER::FAILED\n%s\n", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){ glUseProgram(ID); }
unsigned int Shader::getShaderID(){ return ID; }

void Shader::setBool(const std::string name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setVec3(const std::string name, glm::vec3 value) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}
void Shader::setVec4(const std::string name, glm::vec4 value) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}


void Shader::setAttenuation(glm::vec3 value) const {
    glUniform1f(glGetUniformLocation(ID, "light.constant") , value.x);
    glUniform1f(glGetUniformLocation(ID, "light.linear")   , value.y);
    glUniform1f(glGetUniformLocation(ID, "light.quadratic"), value.z);
}

void Shader::setAttenuation(glm::vec3 value, std::string nLight) const {
    std::string constant  = "pointLights[" + nLight + "].constant";
    std::string linear    = "pointLights[" + nLight + "].linear";
    std::string quadratic = "pointLights[" + nLight + "].quadratic";

    glUniform1f(glGetUniformLocation(ID, constant.c_str()) , value.x);
    glUniform1f(glGetUniformLocation(ID, linear.c_str())   , value.y);
    glUniform1f(glGetUniformLocation(ID, quadratic.c_str()), value.z);
}

void Shader::setPointColorLightN(glm::vec3 value, std::string nLight) const {
    std::string ambient  = "pointLights[" + nLight + "].ambient";
    std::string diffuse  = "pointLights[" + nLight + "].diffuse";
    std::string specular = "pointLights[" + nLight + "].specular";

    glUniform1f(glGetUniformLocation(ID, ambient.c_str()) , value.x);
    glUniform1f(glGetUniformLocation(ID, diffuse.c_str()) , value.y);
    glUniform1f(glGetUniformLocation(ID, specular.c_str()), value.z);
}
















