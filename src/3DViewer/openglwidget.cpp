#include "openglwidget.h"

#include <iostream>
#include <sstream>
#include <vector>

#include "cube.h"
#include "shader.h"

constexpr auto VERTEX_SHADER_PATH = PROJECT_DIR "/v-shader.glsl";
constexpr auto FRAGMENT_SHADER_PATH = PROJECT_DIR "/f-shader.glsl";

void objToClipSpace(utl::model_t* model) {
  for (int i = 0; i != (int)model->vertices.len; i++) {
    model->vertices.data[i] = (model->vertices.data[i] + 1) * 100;
  }
}

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget{parent},
      m_EdgeThickness(1),
      m_VertexPointSize(5.0f),
      m_Scale(1) {
  setMouseTracking(true);
}

void OpenGLWidget::wheelEvent(QWheelEvent* ev) {
  if (ev->pixelDelta().y() < 0)
    m_Scale -= 1;
  else
    m_Scale += 1;

  mat4_t mvp = computeTransform();

  m_Program.use();
  m_Program.setUniform("u_Matrix", mvp.data);
  update();
}

void OpenGLWidget::initializeGL() {
  utl::model_t model;
  mat4_t mvp = computeTransform();

  utl::model_create(&model);
  utl::parser_v2(&model, PROJECT_DIR "/../objects/cube_2.obj");

  initializeOpenGLFunctions();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_PROGRAM_POINT_SIZE);

  std::cout << "OpenGL v" << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL v" << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;

  m_FacesCount = model.indices.len;
  objToClipSpace(&model);

  m_VertexBuf.generate();
  m_VertexBuf.setData(model.vertices.data, model.vertices.len * sizeof(float));

  m_IndexBuf.generate();
  m_IndexBuf.setData(model.indices.data, model.indices.len);

  utl::GLCall(glEnableVertexAttribArray(0));
  utl::GLCall(
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));

  m_Program.create(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
  m_Program.use();
  m_Program.setUniform("u_Color", m_EdgeColor.r, m_EdgeColor.g, m_EdgeColor.b,
                       m_EdgeColor.a);
  m_Program.setUniform("u_Matrix", mvp.data);
  m_Program.setUniform("u_PointSize", m_VertexPointSize);

  utl::model_free(&model);
}

void OpenGLWidget::paintGL() {
  m_Program.use();

  utl::GLCall(glEnableVertexAttribArray(0));

  m_IndexBuf.bind();

  utl::GLCall(
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));

  glClearColor(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b,
               m_BackgroundColor.a);

  utl::GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  glLineWidth(m_EdgeThickness);

  switch (m_EdgeType) {
    case EdgeType::Solid:
      glDisable(GL_LINE_STIPPLE);
      break;

    case EdgeType::Dashed:
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(7, 0xAAAA);
      break;
  }

  m_Program.setUniform("u_Color", m_EdgeColor.r, m_EdgeColor.g, m_EdgeColor.b,
                       m_EdgeColor.a);
  utl::GLCall(glDrawElements(GL_LINES, m_FacesCount, GL_UNSIGNED_INT, 0));

  switch (m_VertexPoint) {
    case VertexType::None:
      /* Nothing to do */
      break;

    case VertexType::Square:
      m_Program.setUniform("u_Color", m_VertexColor.r, m_VertexColor.g,
                           m_VertexColor.b, m_VertexColor.a);
      utl::GLCall(glDrawElements(GL_POINTS, m_FacesCount, GL_UNSIGNED_INT, 0));
      break;

    case VertexType::Circle:
      glEnable(GL_POINT_SMOOTH);
      m_Program.setUniform("u_Color", m_VertexColor.r, m_VertexColor.g,
                           m_VertexColor.b, m_VertexColor.a);
      utl::GLCall(glDrawElements(GL_POINTS, m_FacesCount, GL_UNSIGNED_INT, 0));
      glDisable(GL_POINT_SMOOTH);
      break;
  }
}

void OpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OpenGLWidget::loadModel(utl::model_t* model) {
  m_FacesCount = model->indices.len;
  objToClipSpace(model);
  m_VertexBuf.setData(model->vertices.data,
                      (model->vertices.len) * sizeof(float));
  m_IndexBuf.setData(model->indices.data, model->indices.len);
  update();
}

void OpenGLWidget::setEdgeType(EdgeType et) {
  m_EdgeType = et;
  update();
}
void OpenGLWidget::setEdgeThickness(float thickness) {
  m_EdgeThickness = thickness;
  update();
}

void OpenGLWidget::setVertexType(VertexType vt) { m_VertexPoint = vt; }

void OpenGLWidget::setVertexSize(float sz) {
  m_VertexPointSize = sz;
  m_Program.use();
  m_Program.setUniform("u_PointSize", m_VertexPointSize);
  update();
}

void OpenGLWidget::setBackgroundColor(int r, int g, int b, int a) {
  m_BackgroundColor.r = r / 255.0f;
  m_BackgroundColor.g = g / 255.0f;
  m_BackgroundColor.b = b / 255.0f;
  m_BackgroundColor.a = a / 255.0f;
}

void OpenGLWidget::setEdgeColor(int r, int g, int b, int a) {
  m_EdgeColor.r = r / 255.0f;
  m_EdgeColor.g = g / 255.0f;
  m_EdgeColor.b = b / 255.0f;
  m_EdgeColor.a = a / 255.0f;
}

void OpenGLWidget::setVertexColor(int r, int g, int b, int a) {
  m_VertexColor.r = r / 255.0f;
  m_VertexColor.g = g / 255.0f;
  m_VertexColor.b = b / 255.0f;
  m_VertexColor.a = a / 255.0f;
}

void OpenGLWidget::scaleObject(int value) {
  m_Scale = value;
  mat4_t mvp = computeTransform();

  m_Program.use();
  m_Program.setUniform("u_Matrix", mvp.data);
  update();
}

void OpenGLWidget::rotateObjectX(int xDeg) {
  m_Rotation.x = xDeg;

  mat4_t mvp = computeTransform();

  m_Program.use();
  m_Program.setUniform("u_Matrix", mvp.data);
  update();
}

void OpenGLWidget::rotateObjectY(int yDeg) {
  m_Rotation.y = yDeg;

  mat4_t mvp = computeTransform();

  m_Program.use();
  m_Program.setUniform("u_Matrix", mvp.data);
  update();
}

void OpenGLWidget::rotateObjectZ(int zDeg) {
  m_Rotation.z = zDeg;

  mat4_t mvp = computeTransform();

  m_Program.use();
  m_Program.setUniform("u_Matrix", mvp.data);
  update();
}

void OpenGLWidget::translateObjectX(int value) {
  m_Translation.x = (value / 1000.0f) * 2 - 1;

  mat4_t mvp = computeTransform();

  m_Program.use();
  m_Program.setUniform("u_Matrix", mvp.data);
  update();
}

void OpenGLWidget::translateObjectY(int value) {
  m_Translation.y = (value / 1000.0f) * 2 - 1;

  mat4_t mvp = computeTransform();

  m_Program.use();
  m_Program.setUniform("u_Matrix", mvp.data);
  update();
}

void OpenGLWidget::translateObjectZ(int value) {
  m_Translation.z = (value / 1000.0f) * 2 - 1;

  mat4_t mvp = computeTransform();

  m_Program.use();
  m_Program.setUniform("u_Matrix", mvp.data);
  update();
}

mat4_t OpenGLWidget::computeTransform() {
  float scale = (float)m_Scale / 1000.0f;

  mat4_t ortho = utl::mat4_orthographic(0, 600, 600, 0, 0, -600);
  mat4_t translate =
      utl::mat4_translation(m_Translation.x / scale, m_Translation.y / scale,
                            m_Translation.z / scale);
  mat4_t x_rotate = utl::mat4_x_rotation(utl::radians(m_Rotation.x));
  mat4_t y_rotate = utl::mat4_y_rotation(utl::radians(m_Rotation.y));
  mat4_t z_rotate = utl::mat4_z_rotation(utl::radians(m_Rotation.z));
  mat4_t scaled = utl::mat4_scaling(scale, scale, scale);

  mat4_t m1 = utl::mat4_multiply(&ortho, &translate);
  mat4_t m2 = utl::mat4_multiply(&m1, &x_rotate);
  mat4_t m3 = utl::mat4_multiply(&m2, &y_rotate);
  mat4_t m4 = utl::mat4_multiply(&m3, &z_rotate);
  return utl::mat4_multiply(&m4, &scaled);
}
