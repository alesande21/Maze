//
// Created by Alesander Britni on 10/30/23.
//

#include "../../include/Recoder/Recoder.h"

namespace s21 {
void Recoder::Record(const std::string& file_path, Data& data) {
  if (data.vec_.empty()) return;
  std::ofstream out;
  out.open(file_path);
  if (!out.is_open()) {
    std::cerr << "Error opening file: " << file_path << std::endl;
    out.close();
    return;
  }

  out << data.rows_ << " " << data.cols_ << std::endl;
  int count{};
  for (const auto& row : data.vec_) {
    if (count == data.vec_.size() / 2) {
      out << std::endl;
    }
    for (const auto& param : row) {
      out << param << " ";
    }
    out << std::endl;
    count++;
  }
}
}  // namespace s21
