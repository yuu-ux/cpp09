#include "BitcoinExchange.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

BitcoinExchange::BitcoinExchange(const BitcoinRateDatabase &db) : db(db) {}
BitcoinExchange::~BitcoinExchange() {}

double BitcoinExchange::calc_exchange(const Date &date, double value) {
  const Bitcoin &data = this->db.getData();
  Bitcoin::const_iterator found = data.upper_bound(date.toInt());

  if (found == data.begin())
    throw std::runtime_error("Error: Invalid Date");

  --found;
  return value * found->second;
}

void BitcoinExchange::exchange(const char *input) {
  std::ifstream ifs(input);
  if (!ifs) {
    throw std::runtime_error("Error: could not open file.");
  }
  std::string line;
  bool first = true;
  while (std::getline(ifs, line)) {
    if (first) {
      first = false;
      continue;
    }
    std::string::size_type pipe_pos = line.find('|');
    if (pipe_pos == std::string::npos) {
      std::cout << std::string("Error: bad input => ").append(line) << '\n';
      continue;
    }

    try {
      Date date(line.substr(0, pipe_pos));

      std::istringstream iss(line.substr(pipe_pos + 1));
      double value = 0;
      iss >> value;
      if (value < 0) {
        std::cout << "Error: not a positive number.\n";
        continue;
      }

      if (value > BitcoinExchange::MAX_VALUE) {
        std::cout << "Error: too large a number\n";
        continue;
      }

      if (iss.fail()) {
        std::cout << std::string("Error: bad input => ").append(line) << '\n';
        continue;
      }
      std::cout << date.toString() << " => " << value << " = "
                << calc_exchange(date, value) << '\n';
    } catch (std::runtime_error &e) {
      std::cout << e.what() << '\n';
      continue;
    }
  }
}
