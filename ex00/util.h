#pragma once

#include <sstream>
#include <string>

namespace util {
template <typename T> std::string to_string(T value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}
} // namespace util
