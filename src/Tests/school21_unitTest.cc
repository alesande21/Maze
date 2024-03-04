#include <gtest/gtest.h>

#include "../Models/include/EllerAlgo//EllerAlgo.h"
#include "../Models/include/Parser/ParseFile.h"
#include "../Models/include/WaveAlgo//WaveAlgo.h"

class ParseFileTest : public ::testing::Test {
 protected:
  s21::ParseFile parser;
  s21::EllerAlgo eller;
  s21::WaveAlgo wave;
};

TEST_F(ParseFileTest, FileNotFound) {
  ASSERT_THROW(parser.Parser("../../ResourceFiles/no_file.txt"),
               std::invalid_argument);
}

TEST_F(ParseFileTest, FileThrow1) {
  ASSERT_THROW(parser.Parser("../../ResourceFiles/4_4_throw.txt"),
               std::invalid_argument);
}

TEST_F(ParseFileTest, ValidFileParsing) {
  s21::Data data = parser.Parser("../../ResourceFiles/4_4.txt");

  ASSERT_EQ(data.cols_, 4);
  ASSERT_EQ(data.rows_, 4);
  ASSERT_EQ(data.vec_.size(), 8);
}

TEST_F(ParseFileTest, ValidFileParsing2) {
  s21::Data data = parser.Parser("../../ResourceFiles/4_4.txt");

  ASSERT_EQ(data.cols_, 4);
  ASSERT_EQ(data.rows_, 4);
  ASSERT_EQ(data.vec_.size(), 8);
}

TEST_F(ParseFileTest, ClearData) {
  s21::Data data = parser.Parser("../../ResourceFiles/4_4.txt");

  data.Clear();

  ASSERT_EQ(data.cols_, 0);
  ASSERT_EQ(data.rows_, 0);
  ASSERT_EQ(data.vec_.size(), 0);
}

TEST_F(ParseFileTest, EllerTest) {
  s21::Data data;
  eller.RunEller(data, 4, 4);

  ASSERT_EQ(data.cols_, 4);
  ASSERT_EQ(data.rows_, 4);
  ASSERT_EQ(data.vec_.size(), 8);
}

TEST_F(ParseFileTest, EllerTestError) {
  s21::Data data;
  eller.RunEller(data, 51, 51);

  ASSERT_EQ(data.cols_, 0);
  ASSERT_EQ(data.rows_, 0);
  ASSERT_EQ(data.vec_.size(), 0);
}

TEST_F(ParseFileTest, EllerTestError2) {
  s21::Data data1;
  eller.RunEller(data1, 50, 50);

  ASSERT_EQ(data1.cols_, 50);
  ASSERT_EQ(data1.rows_, 50);
  ASSERT_EQ(data1.vec_.size(), 100);

  s21::Data data2;
  eller.RunEller(data2, -1, -1);

  ASSERT_EQ(data2.cols_, 0);
  ASSERT_EQ(data2.rows_, 0);
  ASSERT_EQ(data2.vec_.size(), 0);
}

TEST_F(ParseFileTest, WaveTest) {
  s21::Data data1;
  eller.RunEller(data1, 50, 50);

  ASSERT_EQ(data1.cols_, 50);
  ASSERT_EQ(data1.rows_, 50);
  ASSERT_EQ(data1.vec_.size(), 100);

  s21::WaveAlgo::wave_type wave_data =
      wave.CreatePath(&data1, {{0, 0}, true}, {{49, 49}, true});

  ASSERT_EQ(wave_data.second, true);
}

TEST_F(ParseFileTest, WaveTestError) {
  s21::Data data1 = parser.Parser("../../ResourceFiles/4_4_error.txt");

  ASSERT_EQ(data1.cols_, 4);
  ASSERT_EQ(data1.rows_, 4);
  ASSERT_EQ(data1.vec_.size(), 8);

  s21::WaveAlgo::wave_type wave_data =
      wave.CreatePath(&data1, {{1, 2}, true}, {{0, 0}, true});

  ASSERT_EQ(wave_data.second, false);
}