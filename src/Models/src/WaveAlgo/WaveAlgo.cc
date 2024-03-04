//
// Created by Alesander Britni on 10/19/23.
//

#include "../../include/WaveAlgo/WaveAlgo.h"

namespace s21 {

WaveAlgo::wave_type WaveAlgo::CreatePath(
    Data *data, std::pair<std::pair<int, int>, bool> enter,
    std::pair<std::pair<int, int>, bool> exit) {
  data_ = data;
  status_searching = false;
  path_.clear();
  path_.resize(data->rows_, std::vector<int>(data->cols_, -1));

  if (!enter.second || !exit.second) return {path_, false};

  path_[enter.first.second][enter.first.first] = 0;
  path_[exit.first.second][exit.first.first] = -2;

  Wave(enter.first.second, enter.first.first, 0);

  return {path_, status_searching};
}

bool WaveAlgo::Wave(int row, int col, int step) {
  if (path_[row][col] == -2) {
    status_searching = true;
    path_[row][col] = step;
    return true;
  }
  path_[row][col] = step;
  if (!status_searching && row + 1 < data_->rows_ && path_[row + 1][col] < 0 &&
      data_->vec_[row + data_->rows_][col] == 0) {
    Wave(row + 1, col, step + 1);
  }
  if (!status_searching && row - 1 >= 0 && path_[row - 1][col] < 0 &&
      data_->vec_[row - 1 + data_->rows_][col] == 0) {
    Wave(row - 1, col, step + 1);
  }
  if (!status_searching && col + 1 < data_->cols_ && path_[row][col + 1] < 0 &&
      data_->vec_[row][col] == 0) {
    Wave(row, col + 1, step + 1);
  }
  if (!status_searching && col - 1 >= 0 && path_[row][col - 1] < 0 &&
      data_->vec_[row][col - 1] == 0) {
    Wave(row, col - 1, step + 1);
  }
  return false;
}

}  // namespace s21
