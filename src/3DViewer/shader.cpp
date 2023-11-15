#include "shader.h"

#include <QOpenGLFunctions>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "utl.h"

static unsigned int create_shader(const char* source, unsigned int type);

static unsigned int create_program(unsigned int vs, unsigned int fs);

void Shader::create(const char* vsFilepath, const char* fsFilepath) {
  std::string vsSource, fsSource;

  utl::fileReadToStr(vsFilepath, vsSource);
  utl::fileReadToStr(fsFilepath, fsSource);

  unsigned int vert = create_shader(vsSource.c_str(), GL_VERTEX_SHADER);
  unsigned int frag = create_shader(fsSource.c_str(), GL_FRAGMENT_SHADER);

  m_Id = create_program(vert, frag);

  utl::GLCall(glDeleteShader(vert));
  utl::GLCall(glDeleteShader(frag));
}

void Shader::use() { utl::GLCall(glUseProgram(m_Id)); }

void Shader::setUniform(const char* name, float value) const {
  utl::GLCall(glUniform1f(glGetUniformLocation(m_Id, name), value));
}

void Shader::setUniform(const char* name, float v1, float v2, float v3,
                        float v4) const {
  utl::GLCall(glUniform4f(glGetUniformLocation(m_Id, name), v1, v2, v3, v4));
}

void Shader::setUniform(const char* name, float* mat) const {
  utl::GLCall(
      glUniformMatrix4fv(glGetUniformLocation(m_Id, name), 1, GL_FALSE, mat));
}

static unsigned int create_shader(const char* source, unsigned int type) {
  unsigned int shader;
  int status;

  shader = glCreateShader(type);
  utl::GLCall(glShaderSource(shader, 1, &source, NULL));
  utl::GLCall(glCompileShader(shader));

  utl::GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
  if (!status) {
    char errMsg[512];
    utl::GLCall(glGetShaderInfoLog(shader, 512, NULL, errMsg));
    std::cout << "Shader compilation failed: " << errMsg << std::endl;
  }

  return shader;
}

static unsigned int create_program(unsigned int vs, unsigned int fs) {
  unsigned int id = glCreateProgram();
  int status;

  utl::GLCall(glBindAttribLocation(id, 0, "a_Vertex"));

  utl::GLCall(glAttachShader(id, vs));
  utl::GLCall(glAttachShader(id, fs));
  utl::GLCall(glLinkProgram(id));

  utl::GLCall(glGetProgramiv(id, GL_LINK_STATUS, &status));
  if (!status) {
    char errMsg[512];
    utl::GLCall(glGetProgramInfoLog(id, 512, NULL, errMsg));
    std::cout << "Program linking failed: " << errMsg << std::endl;
  }

  return id;
}
