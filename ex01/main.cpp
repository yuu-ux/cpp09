#include "RPN.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace ex01 {
const int ARGV_NUM = 2;
}

int main(int argc, char **argv) {
  if (argc != ex01::ARGV_NUM) {
    std::cerr << "Invalid args\n";
    return EXIT_FAILURE;
  }

  try {
    RPN rpn(argv[1]);
    std::cout << rpn.getResult() << '\n';
  } catch (std::runtime_error &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
