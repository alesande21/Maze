//
// Created by Slava on 10.10.2023.
//

#ifndef MAZE_ELLERALGO_H
#define MAZE_ELLERALGO_H

#include <cstdio>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "../DataStruct/DataStruct.h"

namespace s21 {
class EllerAlgo final {
 public:
  EllerAlgo() = default;
  void RunEller(Data& data, int rows, int cols);

 private:
  std::vector<int> line_;

  void FillLine(std::vector<int>& line);
  bool GetRandom();
  int GetNextNum(int set_num);
  void FindMultitude(std::vector<int>::iterator pos,
                     std::vector<int>::iterator ite);
  std::vector<int> SetHorizontalWall(std::vector<int>& line, int cols);
  std::vector<int> SetVerticalWall(std::vector<int>& line, int cols);
  std::vector<int> SetLastLine(std::vector<int>& line, int cols);
  void SetNextNum(std::vector<int>& line, Data& data);

  void FindMultitude(std::vector<int>::iterator pos, std::vector<int>& line);
};

}  // namespace s21

#endif  // MAZE_ELLERALGO_H
