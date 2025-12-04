#pragma once

#include <string>
#include <sstream>

namespace util {
    template <typename T>
    std::string to_string(T value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
}
