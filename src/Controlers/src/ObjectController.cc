#include "../include/ObjectController.h"

namespace s21 {

ObjectController::data_type ObjectController::Parse(
    const std::string& path_file) {
  try {
    return parser_.Parser(path_file);
  } catch (...) {
    return Data{};
  }
}

ObjectController::data_type ObjectController::GetVec() {
  return parser_.SendVec();
}

void ObjectController::GenLab(Data& data, int rows, int cols) {
  eller_.RunEller(data, rows, cols);
}

WaveAlgo::wave_type ObjectController::CreatePath(
    Data* data, std::pair<std::pair<int, int>, bool> enter,
    std::pair<std::pair<int, int>, bool> exit) {
  return wave_.CreatePath(data, enter, exit);
}

void ObjectController::RecordMaze(const std::string& file_path, Data& data) {
  recoder_.Record(file_path, data);
}

}  // namespace s21
