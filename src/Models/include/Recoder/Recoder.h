//
// Created by Alesander Britni on 10/30/23.
//

#ifndef MAZE_RECODER_H
#define MAZE_RECODER_H

#include <fstream>
#include <iostream>
#include <string>

#include "../DataStruct/DataStruct.h"

namespace s21 {
class Recoder {
 public:
  Recoder() = default;
  void Record(const std::string& file_path, Data& data);
};
}  // namespace s21

#endif  // MAZE_RECODER_H
