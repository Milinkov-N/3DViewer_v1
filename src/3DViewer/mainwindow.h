#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  void showEvent(QShowEvent* event) override;
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void on_combo_Vertex_Type_currentIndexChanged(int index);

  void on_slider_X_Axis_Rotation_valueChanged(int value);

  void on_slider_Y_Axis_Rotation_valueChanged(int value);

  void on_slider_Z_Axis_Rotation_valueChanged(int value);

  void on_slider_X_Axis_Translation_valueChanged(int value);

  void on_slider_Y_Axis_Translation_valueChanged(int value);

  void on_slider_Z_Axis_Translation_valueChanged(int value);

  void on_slider_Vertex_Size_valueChanged(int value);

  void on_slider_Scale_valueChanged(int value);

  void on_btn_ChooseBackgorundColor_clicked();

  void on_btn_ChooseEdgeColor_clicked();

  void on_btn_ChooseVertexColor_clicked();

  void on_combo_Edge_Type_currentIndexChanged(int index);

  void on_slider_Edge_Thickness_valueChanged(int value);

  void on_pushButton_clicked();

  void on_btn_Take_Screenshot_clicked();

  void takeScreenshots();

  void createGif();

  void on_btn_Create_Gif_clicked();

 private:
  Ui::MainWindow* ui;

  Settings m_Config;

  QTimer* m_Timer;

  float m_Elapsed;

  std::vector<QImage> m_Screenshots;
};
#endif  // MAINWINDOW_H
