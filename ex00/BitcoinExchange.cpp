#include "BitcoinExchange.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

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

      errno = 0;
      std::string value_str = line.substr(pipe_pos + 1);
      char *end = NULL;
      const long value = strtoul(value_str.c_str(), &end, 10);

      // 1文字も読めてないため、数値じゃない
        if (end == value_str.c_str() || *end != '\0' || errno == ERANGE) {
            std::cout << "Error: bad input => " << value_str << '\n';
            continue;
        }

      if (value < 0) {
        std::cout << "Error: not a positive number.\n";
        continue;
      }

      if (value > BitcoinExchange::MAX_VALUE) {
        std::cout << "Error: too large a number\n";
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
