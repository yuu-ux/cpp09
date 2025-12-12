#include "PmergeMe.h"
#include "../ex00/util.h"
#include <cctype>
#include <iostream>
#include <ostream>
#include <stdexcept>

bool PmergeMe::validate(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    if (!std::isdigit(argv[i][0])) {
      return false;
    }
    int num = atoi(argv[i]);
    if (num < 0) {
      return false;
    }
  }
  return true;
}

void PmergeMe::printResult() const {
  std::string result;
  result.append("Before: ");
  for (int i = 1; i < this->argc; ++i) {
    result.append(this->argv[i]).append(" ");
  }
  result.pop_back();
  result.append("\n");

  result.append("After: ");
  for (std::vector<ex02::pairs_vec>::const_iterator it = this->vector.begin();
       it != this->vector.end(); ++it) {
    result.append(util::to_string(it->num)).append(" ");
  }
  result.pop_back();

  std::cout << result << std::endl;
}

void PmergeMe::executeSortVector() { return; }

void PmergeMe::executeSortDeque() { return; }

void PmergeMe::printTime(const std::string &container_name,
                         const std::clock_t start, const std::clock_t end) {
  std::cout << "Time to process a range of " << this->argc - 1
            << " elements with "
            << "std::" << container_name << " : " << end - start << " us\n";
}

void PmergeMe::initVector() {
  for (int i = 1; i < this->argc; ++i) {
    ex02::pairs_vec pair;
    pair.num = atoi(argv[i]);
    this->vector.push_back(pair);
  }
}

void PmergeMe::initDeque() {
  for (int i = 1; i < this->argc; ++i) {
    ex02::pairs_deque pair;
    pair.num = atoi(argv[i]);
    this->deque.push_back(pair);
  }
}

void PmergeMe::execute() {
  std::clock_t start_vec = std::clock();
  initVector();
  executeSortVector();
  std::clock_t end_vec = std::clock();

  std::clock_t start_deque = std::clock();
  initDeque();
  executeSortDeque();
  std::clock_t end_deque = std::clock();

  printResult();
  printTime("vector", start_vec, end_vec);
  printTime("deque", start_deque, end_deque);
}

PmergeMe::PmergeMe(int argc, char **argv) {
  if (!validate(argc, argv)) {
    std::runtime_error("invalid input");
  }
  this->argc = argc;
  this->argv = argv;
}

PmergeMe::~PmergeMe() {}
