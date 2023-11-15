#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>

#include "indexbuffer.h"
#include "shader.h"
#include "utl.h"
#include "vertexbuffer.h"

using utl::EdgeType;
using utl::mat4_t;
using utl::Pos;
using utl::Rgba;
using utl::VertexType;

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT

 public:
  OpenGLWidget(QWidget* parent = nullptr);

  void loadModel(utl::model_t* model);

  void setEdgeType(EdgeType et);
  void setEdgeThickness(float thickness);

  void setVertexType(VertexType vt);
  void setVertexSize(float sz);

  void setBackgroundColor(int r, int g, int b, int a);
  void setEdgeColor(int r, int g, int b, int a);
  void setVertexColor(int r, int g, int b, int a);

  void scaleObject(int value);

  void rotateObjectX(int xDeg);
  void rotateObjectY(int yDeg);
  void rotateObjectZ(int zDeg);

  void translateObjectX(int value);
  void translateObjectY(int value);
  void translateObjectZ(int value);

 private:
  unsigned int m_FacesCount;

  EdgeType m_EdgeType;
  float m_EdgeThickness;

  VertexType m_VertexPoint;
  float m_VertexPointSize;

  VertexBuffer m_VertexBuf;
  IndexBuffer m_IndexBuf;

  Shader m_Program;

  int m_Scale;
  Pos m_Rotation, m_Translation;

  Rgba m_BackgroundColor, m_EdgeColor, m_VertexColor;

  mat4_t computeTransform();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  void wheelEvent(QWheelEvent* ev) override;
};

#endif  // OPENGLWIDGET_H
