#include "PmergeMe.h"
#include <cstdlib>
#include <iostream>

namespace ex02 {
const int MINIMUM_ARG = 3;
}
int main(int argc, char **argv) {
  if (argc < ex02::MINIMUM_ARG) {
    std::cerr << "invalid input\n";
    return EXIT_FAILURE;
  }

  PmergeMe pm(argc, argv);
  pm.execute();
  return EXIT_SUCCESS;
}
