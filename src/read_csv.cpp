#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

struct DataPoint {
  float min;
  float max;
  float avg;
  float span;
  uint64_t num;
  uint64_t lifetime_1;
  uint64_t lifetime_2;
  uint64_t lifetime_3;
};

static bool line_to_datapoint(const std::string& line, DataPoint& dp) {
  std::istringstream iss{line};
  size_t tok_num = 1;
  for (std::string curr_tok; std::getline(iss, curr_tok, ';');) {
    switch (tok_num) {
      case 1: {
        if (!(std::istringstream(curr_tok) >> dp.min)) {
          std::cout << "Error: element " << tok_num << " is not a float\n";
          return false;
        }
        break;
      }
      case 2: {
        if (!(std::istringstream(curr_tok) >> dp.max)) {
          std::cout << "Error: element " << tok_num << " is not a float\n";
          return false;
        }
        break;
      }
      case 3: {
        if (!(std::istringstream(curr_tok) >> dp.avg)) {
          std::cout << "Error: element " << tok_num << " is not a float\n";
          return false;
        }
        break;
      }
      case 4: {
        if (!(std::istringstream(curr_tok) >> dp.span)) {
          std::cout << "Error: element " << tok_num << " is not a float\n";
          return false;
        }
        break;
      }
      case 5: {
        if (!(std::istringstream(curr_tok) >> dp.num)) {
          std::cout << "Error: element " << tok_num << " is not an int\n";
          return false;
        }
        break;
      }
      case 6: {
        if (!(std::istringstream(curr_tok) >> dp.lifetime_1)) {
          std::cout << "Error: element " << tok_num << " is not an int\n";
          return false;
        }
        break;
      }
      case 7: {
        if (!(std::istringstream(curr_tok) >> dp.lifetime_2)) {
          std::cout << "Error: element " << tok_num << " is not an int\n";
          return false;
        }
        break;
      }
      case 8: {
        if (!(std::istringstream(curr_tok) >> dp.lifetime_3)) {
          std::cout << "Error: element " << tok_num << " is not an int\n";
          return false;
        }
        break;
      }
      default: {
        std::cout << "Extra element in csv line (" << tok_num << "), ignoring...\n";
        break;
      }
    }
    tok_num++;
  }
  return true;
}

static bool load_csv_file(const std::string& filename, std::vector<DataPoint>& data) {
  const std::string csv_file_name{filename};
  std::ifstream csv_file{csv_file_name, std::ios::in};
  size_t curr_line = 1;
  for (std::string line; std::getline(csv_file, line, '\n');) {
    DataPoint curr_sample;
    if (!line_to_datapoint(line, curr_sample)) {
      std::cout << "Error: parsing line " << curr_line << " does not have enough elements\n";
      return false;
    }
    data.push_back(curr_sample);
    curr_line++;
  }
  return true;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " csv_file_to_use\n";
    return 1;
  }

  std::vector<DataPoint> full_data;
  if (!load_csv_file(argv[1], full_data)) {
    std::cout << "Error: parsing file " << argv[1] << "\n";
    return 1;
  }

  // TODO: computations here, the file's contents are in full_data

  return 0;
}