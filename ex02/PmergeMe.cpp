#include "PmergeMe.h"
#include "../ex00/util.h"
#include <cctype>
#include <iostream>
#include <ostream>
#include <stdexcept>

namespace ex02 {
    std::clock_t safeClock() {
        std::clock_t clock = std::clock();
        if (clock == static_cast<std::clock_t>(-1))
            throw std::runtime_error("Failed clock()");
        return clock;
    }
}

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

  std::cout << result << '\n';
}

std::vector<ex02::pairs_vec> PmergeMe::makePairs(const std::vector<ex02::pairs_vec>& data, std::vector<ex02::pairs_vec>& pending) {
    std::vector<ex02::pairs_vec> result;
    // ループ条件 i + 1 < size により、(i, i+1) の2 要素が必ず存在するペアだけ処理する
    for (size_t i = 0; i + 1 < data.size(); i += 2) {
        ex02::pairs_vec parent;
        // 2 要素を比較して、大きい方を親(parent.num)、小さい方を子(parent.nums)として束ねる
        if (data[i].num < data[i + 1].num) {
            parent.num = data[i + 1].num;
            parent.nums = data[i + 1].nums;
            parent.nums.push_back(data[i]);
        } else {
            parent.num = data[i].num;
            parent.nums = data[i].nums;
            parent.nums.push_back(data[i + 1]);
        }
        result.push_back(parent);
    }

    // input の個数が奇数だった場合ペアが作れずあまりが生じるため、あとでインサートするために pending として保持する
    if (data.size() % 2 != 0) {
        pending.push_back(data.back());
    }
    return result;
}


void PmergeMe::insertSorted(std::vector<ex02::pairs_vec>& data, const ex02::pairs_vec& elem) {
    size_t i = 0;
    while (i < data.size() && data[i].num < elem.num)
        ++i;
    data.insert(data.begin() + i, elem);
}

void PmergeMe::mergeInsertionSort(std::vector<ex02::pairs_vec>& data) {
    // ベースケース
    if (data.size() <= 1)
        return ;

    std::vector<ex02::pairs_vec> pending;
    std::vector<ex02::pairs_vec> paired = makePairs(data, pending);

    // 例: 入力が [4,3,2,1,5] のとき、(4,3),(2,1) をペア化し、余りの 5 は pending に入る
    // paired は {num=4,kids=[3]} {num=2,kids=[1]}、pending は [5] のような形
    mergeInsertionSort(paired);

    // insert 対象の要素のみ to_insert 取り出す
    std::vector<ex02::pairs_vec> to_insert;
    for (size_t i = 0; i < paired.size(); ++i) {
        for (size_t j = 0; j < paired[i].nums.size(); ++j) {
            to_insert.push_back(paired[i].nums[j]);
        }
        paired[i].nums.clear();
    }

    // 再帰後の paired は parent.num の並びがソート済みの状態
    data = paired;
    for (size_t i = 0; i < to_insert.size(); ++i) {
        insertSorted(data, to_insert[i]);
    }

    for (size_t i = 0; i < pending.size(); ++i) {
        insertSorted(data, pending[i]);
    }
}

void PmergeMe::executeSortVector() {
    mergeInsertionSort(this->vector);
}

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
  std::clock_t start_vec = ex02::safeClock();
  initVector();
  executeSortVector();
  std::clock_t end_vec = ex02::safeClock();

  std::clock_t start_deque = ex02::safeClock();
  initDeque();
  executeSortDeque();
  std::clock_t end_deque = ex02::safeClock();

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
