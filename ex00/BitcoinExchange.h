#pragma once

#include "BitcoinRateDatabase.h"
#include <map>

class BitcoinExchange {
private:
  static const int MAX_VALUE = 1000;

  const BitcoinRateDatabase &db;

public:
  BitcoinExchange(const BitcoinRateDatabase &db);
  void exchange(const char *input);
  ~BitcoinExchange();

private:
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &other);
  BitcoinExchange &operator=(const BitcoinExchange &rhs);
  double calc_exchange(const Date &date, double value);
};
