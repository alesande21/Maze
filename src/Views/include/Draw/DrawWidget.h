#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QApplication>
#include <QCursor>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGuiApplication>
#include <QMessageBox>
#include <QMouseEvent>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QScreen>
#include <QSettings>
#include <QTimer>
#include <QtGui/QWheelEvent>
#include <filesystem>

#include "../../../Controlers/include/ObjectController.h"

namespace s21 {
class DrawWidget : public QGraphicsView {
  Q_OBJECT

 public:
  using type_position = std::pair<std::pair<int, int>, bool>;

  DrawWidget(QWidget *parent = nullptr);
  DrawWidget(DrawWidget &other) = delete;
  DrawWidget(DrawWidget &&other) = delete;
  DrawWidget &operator=(const DrawWidget other) = delete;
  DrawWidget &operator=(DrawWidget &&other) = delete;
  ~DrawWidget();

  void SetData();
  void Draw();
  void InitScene();
  ObjectController &SendController();
  type_position GetPostion(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void GenLab(int rows, int cols);
  void SetPoint(double width, double height);
  void GetPath();
  ObjectController::data_type &GetData();

 private:
  ObjectController::data_type vec_;
  ObjectController object_controller_;
  //  std::shared_ptr<QGraphicsScene> scene_
  QGraphicsScene *scene_;
  bool left_btn_ = false;
  QPoint mPos_;
  type_position entry_point_ = {{}, false};
  type_position exit_point_ = {{}, false};

 private slots:
  void ClearPoints();
};
}  // namespace s21
#endif  // DRAWWIDGET_H

// https://evileg.com/ru/post/80/
