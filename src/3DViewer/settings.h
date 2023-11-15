#ifndef SETTINGS_H
#define SETTINGS_H

#include "utl.h"

using utl::EdgeType;
using utl::Pos;
using utl::Rgba;
using utl::VertexType;

class Settings {
 private:
  Rgba m_BackgroundColor;

  float m_Scale;
  Pos m_Translation;
  Pos m_Rotation;

  EdgeType m_EdgeType;
  Rgba m_EdgeColor;
  float m_EdgeThickness;

  VertexType m_VertexType;
  Rgba m_VertexColor;
  float m_VertexSize;

 public:
  Settings(const char* filepath);

  void save(const char* filepath);

  std::string toString();

  const Rgba& background_color() const { return m_BackgroundColor; }

  const float& scale() const { return m_Scale; }

  const Pos& tranlation() const { return m_Translation; }

  const Pos& rotation() const { return m_Rotation; }

  const EdgeType& edge_type() const { return m_EdgeType; }

  const Rgba& edge_color() const { return m_EdgeColor; }

  const float& edgeThickness() const { return m_EdgeThickness; }

  const VertexType& vertex_type() const { return m_VertexType; }

  const Rgba& vertex_color() const { return m_VertexColor; }

  const float& vertex_size() const { return m_VertexSize; }

  void set_background_color(Rgba color) { m_BackgroundColor = color; }

  void set_scale(float scale) { m_Scale = scale; }

  void set_translationX(float x) { m_Translation.x = x; }

  void set_translationY(float y) { m_Translation.y = y; }

  void set_translationZ(float z) { m_Translation.z = z; }

  void set_rotationX(float x) { m_Rotation.x = x; }

  void set_rotationY(float y) { m_Rotation.y = y; }

  void set_rotationZ(float z) { m_Rotation.z = z; }

  void set_edge_type(EdgeType et) { m_EdgeType = et; }

  void set_edge_color(Rgba color) { m_EdgeColor = color; }

  void set_edgeThickness(float thickness) { m_EdgeThickness = thickness; }

  void set_vertex_type(VertexType vt) { m_VertexType = vt; }

  void set_vertex_color(Rgba color) { m_VertexColor = color; }

  void set_vertex_size(float sz) { m_VertexSize = sz; }
};

#endif  // SETTINGS_H
