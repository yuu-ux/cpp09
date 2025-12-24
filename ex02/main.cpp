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

  try {
      PmergeMe pm(argc, argv);
      pm.execute();
      // pm.testSorted();
  } catch (std::exception& e) {
      std::cerr << e.what() << '\n';
  }
  return EXIT_SUCCESS;
}
