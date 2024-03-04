#include "../../include/Draw/DrawWidget.h"

namespace s21 {

DrawWidget::DrawWidget(QWidget *parent) : QGraphicsView(parent) {
  scene_ = new QGraphicsScene();
  setGeometry(1000, 1000, 1000, 1000);
  setBackgroundBrush(QColor(61, 61, 61));
  InitScene();
  this->setFocus();
}

DrawWidget::~DrawWidget() { delete scene_; }

void DrawWidget::Draw() {
  scene_->clear();
  if (vec_.vec_.empty()) return;
  QPen pen(Qt::red, 2);
  scene_->addLine(0, 0, 500, 0, pen);
  scene_->addLine(0, 0, 0, 500, pen);

  double width = 500.0 / vec_.cols_;
  double height = 500.0 / vec_.rows_;

  for (int r = 0, all_rows = vec_.rows_ * 2; r < all_rows; ++r) {
    for (int c = 0; c < vec_.cols_; ++c) {
      int x_0 = width * c;
      int y_0 = height * (r < vec_.rows_ ? r : (r - vec_.rows_));
      int x_1 = width * (c + 1);
      int y_1 = height * ((r < vec_.rows_ ? r : (r - vec_.rows_)) + 1);

      if (ParseFile::Compare(vec_, r, c) && ParseFile::IsBorder(vec_, r, c)) {
        scene_->addLine(x_1, y_0, x_1, y_1, pen);
      }

      if (!ParseFile::Compare(vec_, r, c) && ParseFile::IsBorder(vec_, r, c)) {
        scene_->addLine(x_0, y_1, x_1, y_1, pen);
      }
    }
  }
  SetPoint(width, height);
}

void DrawWidget::mousePressEvent(QMouseEvent *event) {
  if (vec_.vec_.empty()) return;
  if (event->button() == Qt::LeftButton) {
    entry_point_ = GetPostion(event);

  } else if (event->button() == Qt::RightButton) {
    exit_point_ = GetPostion(event);
  }
  Draw();
}

DrawWidget::type_position DrawWidget::GetPostion(QMouseEvent *event) {
  double width{}, height{};
  width = 500.0 / vec_.cols_;
  height = 500.0 / vec_.rows_;
  auto first = event->pos();
  if (first.x() < 500 || first.x() > 1000 || first.y() < 250 || first.y() > 750)
    return {{}, false};
  return std::make_pair(std::make_pair((event->pos().x() - 500) / width,
                                       (event->pos().y() - 250) / height),
                        true);
}

void DrawWidget::SetPoint(double width, double height) {
  int x_0{};
  int y_0{};
  if (entry_point_.second) {
    x_0 = width * entry_point_.first.first + width / 2;
    y_0 = height * entry_point_.first.second + height / 2;
    scene_->addLine(x_0, y_0, x_0, y_0, QPen(Qt::green, 2));
  }
  if (exit_point_.second) {
    x_0 = width * exit_point_.first.first + width / 2;
    y_0 = height * exit_point_.first.second + height / 2;
    scene_->addLine(x_0, y_0, x_0, y_0, QPen(Qt::magenta, 2));
  }
}

void DrawWidget::InitScene() {
  this->setScene(scene_);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setAlignment(Qt::AlignCenter);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setMinimumHeight(500);
  this->setMinimumWidth(500);
}

void DrawWidget::SetData() {
  ClearPoints();
  vec_ = object_controller_.GetVec();
  Draw();
}

ObjectController &DrawWidget::SendController() { return object_controller_; }

ObjectController::data_type &DrawWidget::GetData() { return vec_; }

void DrawWidget::GenLab(int rows, int cols) {
  ClearPoints();
  object_controller_.GenLab(vec_, rows, cols);
  Draw();
}

void DrawWidget::ClearPoints() {
  entry_point_ = {{}, false};
  exit_point_ = {{}, false};
}

void DrawWidget::GetPath() {
  auto path = object_controller_.CreatePath(&vec_, entry_point_, exit_point_);
  if (!path.second) {
    std::cerr << "Путь не найден!" << std::endl;
    return;
  }
  Draw();
  int row = exit_point_.first.second;
  int col = exit_point_.first.first;
  int x_0{}, x_1{};
  int y_0{}, y_1{};
  double width{}, height{};
  width = 500.0 / vec_.cols_;
  height = 500.0 / vec_.rows_;
  int *search = &path.first[row][col];
  int *exit = &path.first[entry_point_.first.second][entry_point_.first.first];
  while (search != exit) {
    if (col > 0 && (*search - path.first[row][col - 1]) == 1 &&
        !vec_.vec_[row][col - 1]) {
      x_0 = width * col + width / 2;
      x_1 = width * (col - 1) + width / 2;
      y_0 = height * row + height / 2;
      scene_->addLine(x_0, y_0, x_1, y_0, QPen(Qt::blue, 2));
      search = &path.first[row][col - 1];
      col -= 1;
    } else if (row > 0 && (*search - path.first[row - 1][col]) == 1 &&
               !vec_.vec_[row - 1 + vec_.rows_][col]) {
      x_0 = width * col + width / 2;
      y_0 = height * row + height / 2;
      y_1 = height * (row - 1) + height / 2;
      scene_->addLine(x_0, y_0, x_0, y_1, QPen(Qt::blue, 2));
      search = &path.first[row - 1][col];
      row -= 1;
    } else if (col < vec_.cols_ - 1 &&
               (*search - path.first[row][col + 1]) == 1 &&
               !vec_.vec_[row][col]) {
      x_0 = width * col + width / 2;
      x_1 = width * (col + 1) + width / 2;
      y_0 = height * row + height / 2;
      scene_->addLine(x_0, y_0, x_1, y_0, QPen(Qt::blue, 2));
      search = &path.first[row][col + 1];
      col += 1;
    } else if (row < vec_.rows_ - 1 &&
               (*search - path.first[row + 1][col]) == 1 &&
               !vec_.vec_[row + vec_.rows_][col]) {
      x_0 = width * col + width / 2;
      y_0 = height * row + height / 2;
      y_1 = height * (row + 1) + height / 2;
      scene_->addLine(x_0, y_0, x_0, y_1, QPen(Qt::blue, 2));
      search = &path.first[row + 1][col];
      row += 1;
    }
  }
}

}  // namespace s21
