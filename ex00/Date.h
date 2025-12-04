#pragma once

#include <string>

class Date {
private:
  static const int YEAR_MULTIPLIER = 10000;
  static const int MONTH_MULTIPLIER = 100;
  static const int MONTH_MAX = 12;
  static const int MONTH_MIN = 1;
  static const int YEAR_DIGITS = 4;

  int year;
  int month;
  int day;

public:
  Date(const std::string &date);
  ~Date();

  int toInt() const;
  std::string toString() const;

private:
  Date();
  Date(const Date &other);
  Date &operator=(const Date &rhs);
  void validate();
  int parseIntChunk(const std::string &s);
};
