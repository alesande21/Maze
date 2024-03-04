#include "../../include/MainWindow/MainWindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  setWindowTitle("3DViewer_v2.0");
  setGeometry(1000, 1000, 1500, 1000);
  //  SetParamObj("");
  connect(ui_->call_color_ui, &QPushButton::clicked,
          [this]() { OpenTempWindow(0); });

  connect(ui_->open_file, SIGNAL(triggered()), this, SLOT(OpenFile()));
  connect(ui_->save_file, SIGNAL(triggered()), this, SLOT(SaveMaze()));
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::OpenTempWindow(int num_window) {
  static int prev_window = 7;
  if (ui_->horizontalLayout_2->indexOf(window_) != -1) {
    ui_->horizontalLayout_2->removeWidget(window_);
    window_->hide();
    delete window_;
    window_ = nullptr;
  } else {
    prev_window = 7;
  }

  if (window_ == nullptr && prev_window != num_window) {
    prev_window = num_window;
    window_ = TempWindowFactory::CreateTempWin(num_window, ui_->widget);
    ui_->horizontalLayout_2->addWidget(window_);
    window_->show();
  }
}

void MainWindow::OpenFile() {
  QString file =
      QFileDialog::getOpenFileName(this, "Upload file ", "", "TXT (*.txt)");
  if (!file.isEmpty()) {
    ui_->widget->SendController().Parse(file.toUtf8().constData());
    ui_->widget->SetData();
  }
}

void MainWindow::SaveMaze() {
  QString filepath = QFileDialog::getSaveFileName(
      this, "Save as...", "labirint.txt", "Maze (*.txt)");
  if (!filepath.isEmpty()) {
    ui_->widget->SendController().RecordMaze(filepath.toUtf8().constData(),
                                             ui_->widget->GetData());
  }
}

}  // namespace s21
