#ifndef UTL_H
#define UTL_H

#include <QOpenGLFunctions>
#include <iostream>

namespace utl {
extern "C" {
#include "utils.h"
}

#define GLCall(FUNC) \
  GLClearError();    \
  FUNC;              \
  utl::GLLogCall(#FUNC, __FILE__, __LINE__)

class Rgba {
 public:
  float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;

  Rgba();
  Rgba(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
  Rgba(const std::string& str);

  std::string toString();
};

enum class EdgeType {
  Solid = 0,
  Dashed = 1,
};

enum class VertexType {
  None = 0,
  Square = 1,
  Circle = 2,
};

class Pos {
 public:
  float x, y, z;

  Pos() : x(0), y(0), z(0) {}
  Pos(float x, float y, float z) : x(x), y(y), z(z) {}
  Pos(const std::string& str);

  std::string toString();
};

EdgeType EdgeTypeFromStr(const std::string& str);

std::string EdgeTypeToStr(EdgeType& edgeType);

VertexType VertexTypeFromStr(const std::string& str);

std::string VertexTypeToStr(VertexType& vertexType);

void fileReadToStr(const char* filepath, std::string& dest);

float radians(float degrees);

void GLClearError();

bool GLLogCall(const char* func_name, const char* file, int line);
}  // namespace utl

#endif  // UTL_H
