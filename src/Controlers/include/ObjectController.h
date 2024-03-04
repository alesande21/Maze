#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <QDir>
#include <QtGui/QKeyEvent>

#include "../../Models/include/EllerAlgo/EllerAlgo.h"
#include "../../Models/include/Parser/ParseFile.h"
#include "../../Models/include/Recoder/Recoder.h"
#include "../../Models/include/WaveAlgo/WaveAlgo.h"

namespace s21 {
class ObjectController {
 public:
  using data_type = s21::ParseFile::data_type;

  ObjectController() = default;
  data_type Parse(const std::string& file_path);
  data_type GetVec();
  void GenLab(Data& data, int rows, int cols);
  WaveAlgo::wave_type CreatePath(Data* data,
                                 std::pair<std::pair<int, int>, bool> enter,
                                 std::pair<std::pair<int, int>, bool> exit);
  void RecordMaze(const std::string& file_path, Data& data);

 private:
  ParseFile parser_;
  EllerAlgo eller_;
  WaveAlgo wave_;
  Recoder recoder_;
};
}  // namespace s21

#endif  // OBJECTCONTROLLER_H
