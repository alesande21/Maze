#include "../../include/MainWindow/TempWindowFactory.h"

namespace s21 {

QWidget* TempWindowFactory::CreateTempWin(int windowType, DrawWidget* widget) {
  QWidget* window = nullptr;
  switch (windowType) {
    case 0:
      window = new MazeSettings(*widget);
      break;
  }
  return window;
}

}  // namespace s21
