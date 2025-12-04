#pragma once

#include "Date.h"
#include <map>

typedef std::map<int, double> Bitcoin;
class BitcoinRateDatabase {
private:
  static const char *DEFAULT_DATA_FILE_NAME;

  Bitcoin data;

public:
  BitcoinRateDatabase();
  ~BitcoinRateDatabase();

  const Bitcoin &getData() const;
  std::string toString() const;

private:
  BitcoinRateDatabase(const BitcoinRateDatabase &other);
  BitcoinRateDatabase &operator=(const BitcoinRateDatabase &rhs);
};
