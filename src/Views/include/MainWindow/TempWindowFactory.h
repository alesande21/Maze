#ifndef TEMPWINDOWFACTORY_H
#define TEMPWINDOWFACTORY_H

#include "../MazeSettings/MazeSettings.h"

namespace s21 {
class TempWindowFactory {
 public:
  static QWidget* CreateTempWin(int windowType, DrawWidget* widget);
};
}  // namespace s21
#endif  // TEMPWINDOWFACTORY_H
