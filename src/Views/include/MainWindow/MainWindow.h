#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QStackedLayout>

#include "../MazeSettings/MazeSettings.h"
#include "TempWindowFactory.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui_;
  QWidget *window_{};

 private slots:
  void OpenFile();
  void OpenTempWindow(int num_window);
  void SaveMaze();
};
}  // namespace s21

#endif  // MAINWINDOW_H
