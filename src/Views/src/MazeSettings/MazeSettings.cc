#include "../../include/MazeSettings/MazeSettings.h"

#include "ui_mazesettings.h"

namespace s21 {

MazeSettings::MazeSettings(DrawWidget &scene, QWidget *parent)
    : QWidget(parent), ui_(new Ui::MazeSettings), scene_(&scene) {
  ui_->setupUi(this);

  connect(ui_->rows, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &MazeSettings::SetRows);
  connect(ui_->cols, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &MazeSettings::SetCols);
  connect(ui_->gen_lab, QOverload<bool>::of(&QPushButton::clicked), this,
          &MazeSettings::GenLab);
  connect(ui_->create_path, QOverload<bool>::of(&QPushButton::clicked), this,
          &MazeSettings::CreatePath);
}

MazeSettings::~MazeSettings() { delete ui_; }

void MazeSettings::SetRows() { rows_ = ui_->rows->value(); }

void MazeSettings::SetCols() { cols_ = ui_->cols->value(); }

void MazeSettings::GenLab() { scene_->GenLab(rows_, cols_); }

void MazeSettings::CreatePath() { scene_->GetPath(); }

}  // namespace s21
