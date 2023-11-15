#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QPixmap>
#include <QScreen>

#include "qgifimage.h"
#include "settings.h"
#include "ui_mainwindow.h"

constexpr auto CONFIG_PATH = PROJECT_DIR "/.config";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_Config(CONFIG_PATH),
      m_Timer(new QTimer(0)),
      m_Elapsed(0.0f) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete m_Timer;
  delete ui;
}

void MainWindow::showEvent(QShowEvent* event) {
  (void)event;

  connect(m_Timer, &QTimer::timeout, this, &MainWindow::takeScreenshots);

  ui->slider_Scale->setValue(m_Config.scale());
  connect(ui->slider_Scale, &QSlider::valueChanged, this,
          &MainWindow::on_slider_Scale_valueChanged);

  ui->slider_X_Axis_Rotation->setValue(m_Config.rotation().x);
  connect(ui->slider_X_Axis_Rotation, &QSlider::valueChanged, this,
          &MainWindow::on_slider_X_Axis_Rotation_valueChanged);

  ui->slider_Y_Axis_Rotation->setValue(m_Config.rotation().y);
  connect(ui->slider_Y_Axis_Rotation, &QSlider::valueChanged, this,
          &MainWindow::on_slider_Y_Axis_Rotation_valueChanged);

  ui->slider_Z_Axis_Rotation->setValue(m_Config.rotation().z);
  connect(ui->slider_Z_Axis_Rotation, &QSlider::valueChanged, this,
          &MainWindow::on_slider_Z_Axis_Rotation_valueChanged);

  ui->slider_X_Axis_Translation->setValue(m_Config.tranlation().x);
  connect(ui->slider_X_Axis_Translation, &QSlider::valueChanged, this,
          &MainWindow::on_slider_X_Axis_Translation_valueChanged);

  ui->slider_Y_Axis_Translation->setValue(m_Config.tranlation().y);
  connect(ui->slider_Y_Axis_Translation, &QSlider::valueChanged, this,
          &MainWindow::on_slider_Y_Axis_Translation_valueChanged);

  ui->slider_Z_Axis_Translation->setValue(m_Config.tranlation().z);
  connect(ui->slider_Z_Axis_Translation, &QSlider::valueChanged, this,
          &MainWindow::on_slider_Z_Axis_Translation_valueChanged);

  switch (m_Config.edge_type()) {
    case utl::EdgeType::Solid:
      ui->combo_Edge_Type->setCurrentIndex(0);
      break;
    case utl::EdgeType::Dashed:
      ui->combo_Edge_Type->setCurrentIndex(1);
      break;
  }

  ui->slider_Edge_Thickness->setValue(m_Config.edgeThickness());
  connect(ui->slider_Edge_Thickness, &QSlider::valueChanged, this,
          &MainWindow::on_slider_Edge_Thickness_valueChanged);
  connect(ui->combo_Edge_Type, &QComboBox::currentIndexChanged, this,
          &MainWindow::on_combo_Edge_Type_currentIndexChanged);

  switch (m_Config.vertex_type()) {
    case VertexType::None:
      ui->slider_Vertex_Size->setDisabled(true);
      break;
    case VertexType::Square:
      ui->slider_Vertex_Size->setDisabled(false);
      ui->combo_Vertex_Type->setCurrentIndex(1);
      break;
    case VertexType::Circle:
      ui->slider_Vertex_Size->setDisabled(false);
      ui->combo_Vertex_Type->setCurrentIndex(2);
      break;
  }

  ui->slider_Vertex_Size->setValue(m_Config.vertex_size());
  connect(ui->slider_Vertex_Size, &QSlider::valueChanged, this,
          &MainWindow::on_slider_Vertex_Size_valueChanged);
  connect(ui->combo_Vertex_Type, &QComboBox::currentIndexChanged, this,
          &MainWindow::on_combo_Vertex_Type_currentIndexChanged);

  auto bgColor = m_Config.background_color();
  ui->glWidget->setBackgroundColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

  auto edgeColor = m_Config.edge_color();
  ui->glWidget->setEdgeColor(edgeColor.r, edgeColor.g, edgeColor.b,
                             edgeColor.a);

  auto vertexColor = m_Config.vertex_color();
  ui->glWidget->setVertexColor(vertexColor.r, vertexColor.g, vertexColor.b,
                               vertexColor.a);
}

void MainWindow::closeEvent(QCloseEvent* event) {
  (void)event;
  m_Config.save(CONFIG_PATH);
}

void MainWindow::on_combo_Vertex_Type_currentIndexChanged(int index) {
  switch (index) {
    case 0:
      m_Config.set_vertex_type(VertexType::None);
      ui->slider_Vertex_Size->setDisabled(true);
      ui->glWidget->setVertexType(VertexType::None);
      break;

    case 1:
      m_Config.set_vertex_type(VertexType::Square);
      ui->slider_Vertex_Size->setDisabled(false);
      ui->glWidget->setVertexType(VertexType::Square);
      break;

    case 2:
      m_Config.set_vertex_type(VertexType::Circle);
      ui->slider_Vertex_Size->setDisabled(false);
      ui->glWidget->setVertexType(VertexType::Circle);
      break;
  }

  ui->glWidget->update();
}

void MainWindow::on_slider_X_Axis_Rotation_valueChanged(int value) {
  m_Config.set_rotationX(value);
  ui->glWidget->rotateObjectX(value);
}

void MainWindow::on_slider_Y_Axis_Rotation_valueChanged(int value) {
  m_Config.set_rotationY(value);
  ui->glWidget->rotateObjectY(value);
}

void MainWindow::on_slider_Z_Axis_Rotation_valueChanged(int value) {
  m_Config.set_rotationZ(value);
  ui->glWidget->rotateObjectZ(value);
}

void MainWindow::on_slider_X_Axis_Translation_valueChanged(int value) {
  m_Config.set_translationX(value);
  ui->glWidget->translateObjectX(value);
}

void MainWindow::on_slider_Y_Axis_Translation_valueChanged(int value) {
  m_Config.set_translationY(value);
  ui->glWidget->translateObjectY(value);
}

void MainWindow::on_slider_Z_Axis_Translation_valueChanged(int value) {
  m_Config.set_translationZ(value);
  ui->glWidget->translateObjectZ(value);
}

void MainWindow::on_slider_Vertex_Size_valueChanged(int value) {
  m_Config.set_vertex_size(value);
  ui->glWidget->setVertexSize(value);
}

void MainWindow::on_slider_Scale_valueChanged(int value) {
  m_Config.set_scale(value);
  ui->glWidget->scaleObject(value);
}

void MainWindow::on_btn_ChooseBackgorundColor_clicked() {
  QColorDialog colorPicker;
  int r, g, b, a;

  colorPicker.exec();

  QColor color = colorPicker.selectedColor();
  color.getRgb(&r, &g, &b, &a);
  m_Config.set_background_color(Rgba(r, g, b, a));
  ui->glWidget->setBackgroundColor(r, g, b, a);
}

void MainWindow::on_btn_ChooseEdgeColor_clicked() {
  QColorDialog colorPicker;
  int r, g, b, a;

  colorPicker.exec();

  QColor color = colorPicker.selectedColor();
  color.getRgb(&r, &g, &b, &a);
  m_Config.set_edge_color(Rgba(r, g, b, a));
  ui->glWidget->setEdgeColor(r, g, b, a);
}

void MainWindow::on_btn_ChooseVertexColor_clicked() {
  QColorDialog colorPicker;
  int r, g, b, a;

  colorPicker.exec();

  QColor color = colorPicker.selectedColor();
  color.getRgb(&r, &g, &b, &a);
  m_Config.set_vertex_color(Rgba(r, g, b, a));
  ui->glWidget->setVertexColor(r, g, b, a);
}

void MainWindow::on_combo_Edge_Type_currentIndexChanged(int index) {
  switch (index) {
    case 0:
      m_Config.set_edge_type(EdgeType::Solid);
      ui->glWidget->setEdgeType(EdgeType::Solid);
      break;
    case 1:
      m_Config.set_edge_type(EdgeType::Dashed);
      ui->glWidget->setEdgeType(EdgeType::Dashed);
      break;
  }
}

void MainWindow::on_slider_Edge_Thickness_valueChanged(int value) {
  m_Config.set_edgeThickness(value);
  ui->glWidget->setEdgeThickness(value);
}

void MainWindow::on_pushButton_clicked() {
  QFileDialog fd;
  utl::model_t model;

  utl::model_create(&model);
  fd.setDirectory(PROJECT_DIR);
  fd.exec();

  auto selected = fd.selectedFiles();
  if (selected.size() > 0 && selected[0].endsWith(".obj") &&
      !utl::parser_v2(&model, (char*)selected[0].toStdString().c_str())) {
    ui->glWidget->loadModel(&model);
    ui->display_Selected_Model->setText(selected[0]);
    ui->display_Number_of_Edges->setText(QString::number(model.indices.len));
    ui->display_Number_of_Vertices->setText(
        QString::number(model.vertices.len * 3));

    utl::model_free(&model);
  }
}

void MainWindow::on_btn_Take_Screenshot_clicked() {
  QString fileExt;
  const char* fileType;
  auto filename = QFileDialog::getSaveFileName(this, "Save screenshot");

  switch (ui->combo_File_Ext->currentIndex()) {
    case 0:
      fileExt = ".jpg";
      fileType = "JPG";
      break;

    case 1:
      fileExt = ".bmp";
      fileType = "BMP";
      break;

    default:
      fileExt = ".bmp";
      fileType = "BMP";
      break;
  }

  filename.append(fileExt);

  QPixmap pm(ui->glWidget->rect().size());
  ui->glWidget->render(&pm, QPoint(), QRegion(ui->glWidget->rect()));
  QFile file(filename);

  file.open(QIODevice::WriteOnly);

  if (file.isOpen()) pm.save(&file, fileType);
}

void MainWindow::takeScreenshots() {
  if (m_Elapsed <= 5.0) {
    m_Screenshots.push_back(ui->glWidget->grab().toImage());
    m_Elapsed += 0.1f;
  } else {
    createGif();
    m_Timer->stop();
    m_Elapsed = 0.0f;
  }
}

void MainWindow::createGif() {
  auto filename = QFileDialog::getSaveFileName(this, "Save screenshot");

  QGifImage gif(QSize(640, 480));

  gif.setDefaultDelay(100);

  for (auto scr : m_Screenshots) gif.addFrame(scr.scaled(QSize(640, 480)));

  gif.save(filename);
  m_Screenshots.clear();
}

void MainWindow::on_btn_Create_Gif_clicked() {
  m_Timer->start(100);

  takeScreenshots();
}
