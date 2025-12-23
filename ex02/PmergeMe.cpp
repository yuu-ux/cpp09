#include "PmergeMe.h"
#include "../ex00/util.h"
#include <algorithm>
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
    std::vector<ex02::pairs_vec>::iterator pos = std::lower_bound(data.begin(), data.end(), elem, ex02::PairVecLess());
    data.insert(pos, elem);
}

static std::vector<size_t> makeJacobsthalOrder(size_t array_length)
{
    std::vector<size_t> order;
    if (array_length == 0)
        return order;
    if (array_length == 1) {
        order.push_back(0);
        return order;
    }
    order.push_back(0);
    // Ji = Ji−1 + 2Ji−2
    // 初期値が 1 なのは 3 からヤコブスタール数列を作りたいため
    // 0, 1, 1, 3, 2, 5, 4, 11, 10
    size_t ji2  = 1;
    size_t ji1  = 1;
    while (true) {
        size_t ji = ji1 + 2 * ji2;
        // m が 8だった場合、11になった時点で breakする
        if (ji > array_length) break;
        for (size_t x = ji; x > ji1; --x) {
            order.push_back(x-1);
        }
        ji2 = ji1;
        ji1 = ji;
    }
    // 3, 2, 5, 4, (11, 10, 9), 8, 7, 6
    for (size_t x = array_length; x > ji1; --x) {
        order.push_back(x-1);
    }
    return order;
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
    std::vector<size_t> order = makeJacobsthalOrder(to_insert.size());

    for (size_t i = 0; i < order.size(); i++) {
        ex02::pairs_vec elem = to_insert[order[i]];
        std::vector<ex02::pairs_vec>::iterator pos = std::lower_bound(data.begin(), data.end(), elem, ex02::PairVecLess());
        data.insert(pos, elem);
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
