#include "utl.h"

#include <fstream>
#include <sstream>
#include <string>

using utl::EdgeType;
using utl::Pos;
using utl::Rgba;
using utl::VertexType;

EdgeType utl::EdgeTypeFromStr(const std::string& str) {
  if (!str.compare("Dashed")) return EdgeType::Dashed;

  return EdgeType::Solid;
}

std::string utl::EdgeTypeToStr(EdgeType& edgeType) {
  switch (edgeType) {
    case EdgeType::Dashed:
      return std::string("Dashed");
      break;
    case EdgeType::Solid:
      return std::string("Solid");
      break;
  }
}

VertexType utl::VertexTypeFromStr(const std::string& str) {
  if (!str.compare("Square"))
    return VertexType::Square;
  else if (!str.compare("Circle"))
    return VertexType::Circle;

  return VertexType::None;
}

std::string utl::VertexTypeToStr(VertexType& vertexType) {
  switch (vertexType) {
    case VertexType::None:
      return std::string("None");
      break;
    case VertexType::Square:
      return std::string("Square");
      break;
    case VertexType::Circle:
      return std::string("Circle");
      break;
  }
}

void utl::fileReadToStr(const char* filepath, std::string& dest) {
  std::ifstream fp(filepath);

  if (!fp.is_open()) {
    std::cout << "Failed to open file \"" << filepath << "\"" << std::endl;
    return;
  }

  std::stringstream ss;

  ss << fp.rdbuf();
  dest = ss.str();
  fp.close();
}

float utl::radians(float degrees) { return ((360 - degrees) * M_PI) / 180; }

Rgba::Rgba() {}

Rgba::Rgba(const std::string& str) {
  std::stringstream ss(str);
  std::string value;

  if (std::getline(ss, value, ',')) r = std::stof(value);
  if (std::getline(ss, value, ',')) g = std::stof(value);
  if (std::getline(ss, value, ',')) b = std::stof(value);
  if (std::getline(ss, value, ',')) a = std::stof(value);
}

std::string Rgba::toString() {
  std::stringstream ss;

  ss << r << "," << g << "," << b << "," << a;

  return ss.str();
}

Pos::Pos(const std::string& str) {
  std::stringstream ss(str);
  std::string value;

  if (std::getline(ss, value, ',')) x = std::stof(value);
  if (std::getline(ss, value, ',')) y = std::stof(value);
  if (std::getline(ss, value, ',')) z = std::stof(value);
}

std::string Pos::toString() {
  std::stringstream ss;

  ss << x << "," << y << "," << z;

  return ss.str();
}

void utl::GLClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool utl::GLLogCall(const char* func_name, const char* file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OPENGL ERROR(" << error << ")] " << file << ":" << line
              << " " << func_name << std::endl;
    return false;
  }

  return true;
}
