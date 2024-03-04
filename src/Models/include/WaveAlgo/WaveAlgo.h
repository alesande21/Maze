//
// Created by Alesander Britni on 10/19/23.
//

#ifndef MAZE_WAVEALGO_H
#define MAZE_WAVEALGO_H

#include <iostream>

#include "../DataStruct/DataStruct.h"

namespace s21 {
class WaveAlgo {
 public:
  using path_type = std::vector<std::vector<int>>;
  using wave_type = std::pair<path_type, bool>;

  WaveAlgo() = default;
  wave_type CreatePath(Data *data, std::pair<std::pair<int, int>, bool> enter,
                       std::pair<std::pair<int, int>, bool> exit);

 private:
  Data *data_;
  path_type path_{};
  bool status_searching = false;
  void Print(path_type path);
  bool Wave(int row, int col, int step);
};
}  // namespace s21

#endif  // MAZE_WAVEALGO_H
