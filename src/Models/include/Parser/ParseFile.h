//
// Created by Alesander Britni on 8/23/23.
//

#ifndef INC_3D_TEST_PARSEOBJECT_H
#define INC_3D_TEST_PARSEOBJECT_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

#include "../DataStruct/DataStruct.h"

namespace s21 {
class ParseFile {
 public:
  using data_type = Data;

  data_type Parser(std::string name_file);
  data_type SendVec();
  inline void ClearData() { data_.Clear(); }
  static bool Compare(const Data& data, int row, int col);
  static bool IsBorder(const Data& data, int row, int col);

 private:
  Data data_;

  bool SetRowsCols(const std::string& line);
  void ReadLine(const std::string& line);
};
}  // namespace s21

#endif  // INC_3D_TEST_PARSEOBJECT_H
