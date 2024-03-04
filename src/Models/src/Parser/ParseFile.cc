//
// Created by Alesander Britni on 9/19/23.
//

#include "../../include/Parser/ParseFile.h"

namespace s21 {

ParseFile::data_type ParseFile::Parser(std::string name_file) {
  std::ifstream file(name_file);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << name_file << std::endl;
    throw std::invalid_argument("Invalid file extension");
  }
  ClearData();
  std::string line;
  std::getline(file, line);
  if (!SetRowsCols(line)) return {};

  while (std::getline(file, line)) {
    ReadLine(line);
  }

  //  std::cout << data_.vec_.size() << " - " <<  data_.rows_ << std::endl;
  if (data_.vec_.size() != data_.rows_ * 2) {
    std::cerr << "Error parsing date" << std::endl;
    data_.rows_ = data_.cols_ = 0;
    data_.vec_.clear();
    throw std::invalid_argument("Invalid vec size");
  }

  return data_;
}

bool ParseFile::SetRowsCols(const std::string& line) {
  std::istringstream iss(line);
  iss >> data_.rows_;
  iss >> data_.cols_;
  if ((data_.rows_ > 0 && data_.cols_ > 0) &&
      (data_.rows_ <= 50 && data_.cols_ <= 50))
    return true;
  return false;
}

void ParseFile::ReadLine(const std::string& line) {
  std::istringstream iss(line);
  std::vector<int> vec;
  int val{};
  for (int i = 0; i < data_.cols_; ++i) {
    if (!(iss >> val)) {
      return;
    }

    vec.push_back(val);
  }
  data_.vec_.push_back(vec);
}

ParseFile::data_type ParseFile::SendVec() { return data_; }

bool ParseFile::Compare(const Data& data, int row, int col) {
  return ((row)*data.cols_ + (col + 1)) <= (data.cols_ * data.rows_);
}

bool ParseFile::IsBorder(const Data& data, int row, int col) {
  if (data.cols_ <= col || data.rows_ * 2 <= row || row < 0 || col < 0)
    return false;
  return data.vec_[row][col];
}

}  // namespace s21
