#pragma once

#include <deque>
#include <string>
#include <vector>

namespace ex02 {
typedef struct pairs_vec {
  int num;
  std::vector<struct pairs_vec> nums;
} pairs_vec;

typedef struct pairs_deque {
  int num;
  std::vector<struct pairs_deque> nums;
} pairs_deque;
} // namespace ex02

class PmergeMe {
private:
  int argc;
  char **argv;
  std::vector<ex02::pairs_vec> vector;
  std::deque<ex02::pairs_deque> deque;

public:
  PmergeMe(int argc, char **argv);
  ~PmergeMe();

  void execute();

private:
  PmergeMe();
  PmergeMe(const PmergeMe &other);
  PmergeMe &operator=(const PmergeMe &rhs);

  bool validate(int argc, char **argv);
  void initVector();
  void initDeque();
  void executeSortVector();
  void executeSortDeque();
  void printResult() const;
  void printTime(const std::string &container_name, const std::clock_t start,
                 const std::clock_t end);
};
