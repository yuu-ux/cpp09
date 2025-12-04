#include "BitcoinExchange.h"
#include "BitcoinRateDatabase.h"
#include <cstdlib>
#include <iostream>

namespace ex00 {
const int ARGV_NUM = 2;
}

int main(int argc, char **argv) {
  if (argc != ex00::ARGV_NUM) {
    std::cerr << "Error: could not open file.\n";
    return EXIT_FAILURE;
  }

  static_cast<void>(argv);
  BitcoinRateDatabase db;
  BitcoinExchange exchanger(db);
  exchanger.exchange(argv[1]);
  return EXIT_SUCCESS;
}
