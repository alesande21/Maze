//
// Created by Slava on 10.10.2023.
//

#ifndef MAZE_DATASTRUCT_H
#define MAZE_DATASTRUCT_H
#include <vector>

namespace s21 {
struct Data {
  int rows_{};
  int cols_{};
  std::vector<std::vector<int>> vec_;

  Data() = default;

  void Clear() {
    rows_ = 0;
    cols_ = 0;
    vec_.clear();
  }

  bool SetParam(int rows, int cols) {
    Clear();
    if (!CheckParam(rows, cols)) return false;
    rows_ = rows;
    cols_ = cols;
    return true;
  }

  bool CheckParam(int rows, int cols) {
    return ((rows > 0 && cols > 0) && (rows <= 50 && cols <= 50));
  }
};
}  // namespace s21

#endif  // MAZE_DATASTRUCT_H
