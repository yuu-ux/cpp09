#include "Date.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string Date::toString() const {
  std::string string_date;
  string_date.assign(util::to_string(this->year))
      .append("-")
      .append(util::to_string(month))
      .append("-")
      .append(util::to_string(day));
  return string_date;
}

static std::string extractChunk(const std::string &date,
                                std::string::size_type start,
                                std::string::size_type &next_pos) {
  next_pos = date.find('-', start);
  if (next_pos == std::string::npos)
    next_pos = date.size();
  return date.substr(start, next_pos - start);
}

bool isLeap(int year) {
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

void Date::validate() {
  if (this->month > MONTH_MAX || this->month < MONTH_MIN) {
    throw std::runtime_error(std::string("Error: bad month => ")
                                 .append(util::to_string(this->month)));
  }

  static const int days_in_month[] = {31, 28, 31, 30, 31, 30,
                                      31, 31, 30, 31, 30, 31};
  int max_day = days_in_month[this->month - 1];

  if (this->month == 2 && isLeap(this->year))
    max_day = 29;

  if (this->day < 1 || this->day > max_day) {
    throw std::runtime_error(
        std::string("Error: bad day => ").append(util::to_string(this->day)));
  }
}

int Date::parseIntChunk(const std::string &date_str) {
  int value;
  std::istringstream iss(date_str);
  iss >> value;
  if (iss.fail()) {
    throw std::runtime_error(
        std::string("Error: bad format => ").append(date_str));
  }
  return value;
}

Date::Date(const std::string &date) {
  std::string::size_type pos = 0;
  std::string::size_type next;

  std::string year_str = extractChunk(date, pos, next);
  if (year_str.size() > YEAR_DIGITS) {
    throw(std::runtime_error(
        std::string("Error: bad year => ").append(year_str)));
  }
  this->year = parseIntChunk(year_str);

  pos = next + 1;
  std::string month_str = extractChunk(date, pos, next);
  this->month = parseIntChunk(month_str);

  pos = next + 1;
  std::string day_str = extractChunk(date, pos, next);
  this->day = parseIntChunk(day_str);

  this->validate();
}

int Date::toInt() const {
  return (this->year * YEAR_MULTIPLIER) + (this->month * MONTH_MULTIPLIER) +
         this->day;
}

Date::~Date() {}
