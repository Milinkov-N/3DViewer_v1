#include "settings.h"

#include <fstream>
#include <iostream>
#include <sstream>

Settings::Settings(const char* filepath)
    : m_Scale(1.0f), m_EdgeThickness(1.0f), m_VertexSize(1.0f) {
  std::string configSource, line;

  utl::fileReadToStr(filepath, configSource);

  std::stringstream configStream(configSource);

  while (std::getline(configStream, line, '\n')) {
    auto npos = line.find('=');

    auto key = line.substr(0, npos);
    auto value = line.substr(npos + 1, line.size() - 1);

    if (!key.compare("BackgroundColor")) {
      m_BackgroundColor = Rgba(value);
    } else if (!key.compare("Scale")) {
      m_Scale = std::stof(value);
    } else if (!key.compare("Translation")) {
      m_Translation = Pos(value);
    } else if (!key.compare("Rotation")) {
      m_Rotation = Pos(value);
    } else if (!key.compare("EdgeType")) {
      m_EdgeType = utl::EdgeTypeFromStr(value);
    } else if (!key.compare("EdgeColor")) {
      m_EdgeColor = Rgba(value);
    } else if (!key.compare("EdgeThickness")) {
      m_EdgeThickness = std::stof(value);
    } else if (!key.compare("VertexType")) {
      m_VertexType = utl::VertexTypeFromStr(value);
    } else if (!key.compare("VertexColor")) {
      m_VertexColor = Rgba(value);
    } else if (!key.compare("VertexSize")) {
      m_VertexSize = std::stof(value);
    }
  }
}

void Settings::save(const char* filepath) {
  std::ofstream fs(filepath);

  if (fs.is_open()) {
    fs.clear();
    fs << this->toString();
    fs.close();
  }
}

std::string Settings::toString() {
  std::stringstream ss;

  ss << "BackgroundColor=" << m_BackgroundColor.toString() << std::endl
     << "Scale=" << m_Scale << std::endl
     << "Translation=" << m_Translation.toString() << std::endl
     << "Rotation=" << m_Rotation.toString() << std::endl
     << "EdgeType=" << utl::EdgeTypeToStr(m_EdgeType) << std::endl
     << "EdgeColor=" << m_EdgeColor.toString() << std::endl
     << "EdgeThickness=" << m_EdgeThickness << std::endl
     << "VertexType=" << utl::VertexTypeToStr(m_VertexType) << std::endl
     << "VertexColor=" << m_VertexColor.toString() << std::endl
     << "VertexSize=" << m_VertexSize << std::endl;

  return ss.str();
}
