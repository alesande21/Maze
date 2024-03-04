#ifndef MAZESETTINGS_H
#define MAZESETTINGS_H

#include <QOpenGLFunctions>
#include <QWidget>

#include "../Draw/DrawWidget.h"

namespace Ui {
class MazeSettings;
}

namespace s21 {
class MazeSettings : public QWidget {
  Q_OBJECT

 public:
  MazeSettings() = delete;
  explicit MazeSettings(DrawWidget &scene, QWidget *parent = nullptr);
  MazeSettings(MazeSettings &other) = delete;
  MazeSettings(MazeSettings &&other) = delete;
  MazeSettings &operator=(const MazeSettings other) = delete;
  MazeSettings &operator=(MazeSettings &&other) = delete;
  ~MazeSettings();

 private:
  Ui::MazeSettings *ui_;
  DrawWidget *scene_;
  int rows_{};
  int cols_{};

 private slots:
  void SetRows();
  void SetCols();
  void GenLab();
  void CreatePath();
};
}  // namespace s21

#endif  // MAZESETTINGS_H
