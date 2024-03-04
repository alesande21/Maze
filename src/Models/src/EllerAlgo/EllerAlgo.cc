//
// Created by Slava on 10.10.2023.
//
#include "../../include/EllerAlgo/EllerAlgo.h"

namespace s21 {
void EllerAlgo::RunEller(Data& data, int rows, int cols) {
  if (!data.SetParam(rows, cols)) {
    std::cerr << "Неверные параметры для rows или cols" << std::endl;
    return;
  }

  std::vector<int> line(cols);
  FillLine(line);
  GetNextNum(data.cols_);

  for (int row = 0, rows = data.rows_; row < rows - 1; ++row) {
    data.vec_.emplace(data.vec_.begin() + row,
                      SetVerticalWall(line, data.cols_));
    data.vec_.emplace(data.vec_.end(), SetHorizontalWall(line, data.cols_));
  }
  data.vec_.emplace(data.vec_.begin() + data.rows_ - 1,
                    SetLastLine(line, data.cols_));
  data.vec_.emplace(data.vec_.end(), std::vector<int>(data.cols_, 1));
}

std::vector<int> EllerAlgo::SetVerticalWall(std::vector<int>& line, int cols) {
  std::vector<int> walls(cols, 0);
  for (auto it = line.begin(), ite = line.end(), itw = walls.begin(); it != ite;
       ++it, ++itw) {
    bool gen_wall = GetRandom();
    if (*it == *std::next(it) || std::next(it) == ite) {
      *itw = 1;
    } else if (gen_wall) {
      *itw = gen_wall;
    } else if (!gen_wall) {
      FindMultitude(it, line);
    }
  }
  return walls;
}

std::vector<int> EllerAlgo::SetHorizontalWall(std::vector<int>& line,
                                              int cols) {
  bool has_window = false;
  std::vector<int> walls(cols, 0);
  for (auto it = line.begin(), ite = line.end(), itw = walls.begin(); it != ite;
       ++it, ++itw) {
    bool gen_wall = GetRandom();
    if (gen_wall) {
      int count{};
      for (auto it_c = line.begin(); it_c != ite; ++it_c) {
        if (*it_c == *it) count++;
      }
      if (count > 1) {
        *itw = gen_wall;
        *it = GetNextNum(0);
      }
    }
  }
  return walls;
}

std::vector<int> EllerAlgo::SetLastLine(std::vector<int>& line, int cols) {
  std::vector<int> walls(cols, 0);
  for (auto it = line.begin(), ite = line.end(), itw = walls.begin(); it != ite;
       ++it, ++itw) {
    if (*it == *std::next(it) || std::next(it) == ite) {
      *itw = 1;
    } else {
      FindMultitude(it, ite);
    }
  }
  return walls;
}

void EllerAlgo::FindMultitude(std::vector<int>::iterator pos,
                              std::vector<int>::iterator ite) {
  auto find_pos = *std::next(pos);
  for (auto it = std::next(pos); it != ite; ++it) {
    if (*it == find_pos) *it = *pos;
  }
}

void EllerAlgo::FindMultitude(std::vector<int>::iterator pos,
                              std::vector<int>& line) {
  auto find_pos = *std::next(pos);
  for (auto it = line.begin(), ite = line.end(); it != ite; ++it) {
    if (*it == find_pos) *it = *pos;
  }
}

void EllerAlgo::FillLine(std::vector<int>& line) {
  for (size_t i = 0; i < line.size(); ++i) {
    line[i] = i + 1;
  }
}

int EllerAlgo::GetNextNum(int set_num) {
  static int curr_num = 0;
  set_num ? curr_num = set_num : curr_num += 1;
  return curr_num;
}

void EllerAlgo::SetNextNum(std::vector<int>& line, Data& data) {
  for (auto it = line.begin(), ite = line.end(),
            itd = (--data.vec_.end())->begin();
       it != ite; ++it, ++itd) {
    if (*itd) *it = GetNextNum(0);
  }
}

bool EllerAlgo::GetRandom() {
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(1, 1000000000);
  return uniform_dist(e1) % 2;
}

}  // namespace s21
