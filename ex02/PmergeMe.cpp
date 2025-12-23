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
} // namespace ex02

void PmergeMe::validate(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    errno = 0;
    char *end = NULL;
    long num = std::strtoul(argv[i], &end, 10);

    if (end == argv[i])
      throw std::runtime_error("Error: expected a positive integer");

    if (*end != '\0')
      throw std::runtime_error("Error: invalid number");

    if (errno == ERANGE)
      throw std::runtime_error("Error: number out of range");
    if (num < 0)
        throw std::runtime_error("Error: value must be > 0");
  }
}

void PmergeMe::printResult() const {
  std::string result;
  result.append("Before: ");
  for (int i = 1; i < this->argc; ++i) {
    result.append(this->argv[i]).append(" ");
  }
  result.erase(result.size()-1, 1);
  result.append("\n");

  result.append("After: ");
  for (std::vector<ex02::pairs_vec>::const_iterator it = this->vector.begin();
       it != this->vector.end(); ++it) {
    result.append(util::to_string(it->num)).append(" ");
  }
  result.erase(result.size()-1, 1);

  std::cout << result << '\n';
}

std::vector<ex02::pairs_vec> PmergeMe::makePairsVec(const std::vector<ex02::pairs_vec> &data,
                    std::vector<ex02::pairs_vec> &pending) {
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

  // input の個数が奇数だった場合ペアが作れずあまりが生じるため、あとでインサートするために
  // pending として保持する
  if (data.size() % 2 != 0) {
    pending.push_back(data.back());
  }
  return result;
}

std::deque<ex02::pairs_deque> PmergeMe::makePairsDeque(const std::deque<ex02::pairs_deque> &data,
                    std::deque<ex02::pairs_deque> &pending) {
  std::deque<ex02::pairs_deque> result;
  // ループ条件 i + 1 < size により、(i, i+1) の2 要素が必ず存在するペアだけ処理する
  for (size_t i = 0; i + 1 < data.size(); i += 2) {
    ex02::pairs_deque parent;
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

  // input の個数が奇数だった場合ペアが作れずあまりが生じるため、あとでインサートするために
  // pending として保持する
  if (data.size() % 2 != 0) {
    pending.push_back(data.back());
  }
  return result;
}

void PmergeMe::insertSortedVec(std::vector<ex02::pairs_vec> &data, const ex02::pairs_vec &elem) {
  std::vector<ex02::pairs_vec>::iterator pos =
      std::lower_bound(data.begin(), data.end(), elem, ex02::PairVecLess());
  data.insert(pos, elem);
}

void PmergeMe::insertSortedDeque(std::deque<ex02::pairs_deque> &data, const ex02::pairs_deque &elem) {
  std::deque<ex02::pairs_deque>::iterator pos =
      std::lower_bound(data.begin(), data.end(), elem, ex02::PairDequeLess());
  data.insert(pos, elem);
}

std::vector<size_t> PmergeMe::makeJacobsthalOrder(size_t array_length) {
  std::vector<size_t> order;
  if (array_length == 0)
    return order;
  if (array_length == 1) {
    order.push_back(0);
    return order;
  }

  // 0 始まりなので、0 を挿入
  order.push_back(0);
  // ヤコブスタール数列の例: 0, 1, 1, 3, 5, 11, 21, 43
  // 漸化式： J{i} = J{i−1} + 2*J{i−2}
  size_t ji2 = 1;
  size_t ji1 = 1;
  while (true) {
    size_t ji = ji1 + 2 * ji2;
    // ヤブコスタール値が対象範囲を超えたら終了
    // 例： array_length が 8 だった場合、0, 1, 1, 3, 5, 11 になった時点で終了する
    if (ji > array_length)
      break;

    // (ji1, ji] の範囲を降順で追加
    // 例: ji=1, ji=3 のとき、0, 1, 1, 3, 2 となる
    for (size_t x = ji; x > ji1; --x) {
      order.push_back(x - 1);
    }
    ji2 = ji1;
    ji1 = ji;
  }
  // 上のループで追加されなかった残りを、array_length から降順で追加する
  // 例: array_length が 8 だった場合、0, 1, 1, 3, 2, 5, 4, 8, 7, 6 のようになる
  for (size_t x = array_length; x > ji1; --x) {
    order.push_back(x - 1);
  }
  return order;
}

void PmergeMe::mergeInsertionSortVec(std::vector<ex02::pairs_vec> &data) {
  // ベースケース
  if (data.size() <= 1)
    return;

  std::vector<ex02::pairs_vec> pending;
  std::vector<ex02::pairs_vec> paired = makePairsVec(data, pending);

  // 例: 入力が [4,3,2,1,5] のとき、(4,3),(2,1) をペア化し、余りの 5 は pending に入る
  // paired は {num=4,kids=[3]} {num=2,kids=[1]}、pending は [5] のような形
  mergeInsertionSortVec(paired);

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
  // 最適な挿入順序を求める
  std::vector<size_t> order = makeJacobsthalOrder(to_insert.size());

  for (size_t i = 0; i < order.size(); i++) {
    ex02::pairs_vec elem = to_insert[order[i]];
    std::vector<ex02::pairs_vec>::iterator pos =
        std::lower_bound(data.begin(), data.end(), elem, ex02::PairVecLess());
    data.insert(pos, elem);
  }

  // 余った要素を追加する
  for (size_t i = 0; i < pending.size(); ++i) {
    insertSortedVec(data, pending[i]);
  }
}


void PmergeMe::mergeInsertionSortDeque(std::deque<ex02::pairs_deque> &data) {
  // ベースケース
  if (data.size() <= 1)
    return;

  std::deque<ex02::pairs_deque> pending;
  std::deque<ex02::pairs_deque> paired = makePairsDeque(data, pending);

  // 例: 入力が [4,3,2,1,5] のとき、(4,3),(2,1) をペア化し、余りの 5 は pending に入る
  // paired は {num=4,kids=[3]} {num=2,kids=[1]}、pending は [5] のような形
  mergeInsertionSortDeque(paired);

  // insert 対象の要素のみ to_insert 取り出す
  std::deque<ex02::pairs_deque> to_insert;
  for (size_t i = 0; i < paired.size(); ++i) {
    for (size_t j = 0; j < paired[i].nums.size(); ++j) {
      to_insert.push_back(paired[i].nums[j]);
    }
    paired[i].nums.clear();
  }

  // 再帰後の paired は parent.num の並びがソート済みの状態
  data = paired;
  // 最適な挿入順序を求める
  std::vector<size_t> order = makeJacobsthalOrder(to_insert.size());

  for (size_t i = 0; i < order.size(); i++) {
    ex02::pairs_deque elem = to_insert[order[i]];
    std::deque<ex02::pairs_deque>::iterator pos = std::lower_bound(data.begin(), data.end(), elem, ex02::PairDequeLess());
    data.insert(pos, elem);
  }

  // 余った要素を追加する
  for (size_t i = 0; i < pending.size(); ++i) {
    insertSortedDeque(data, pending[i]);
  }
}

void PmergeMe::executeSortVector() { mergeInsertionSortVec(this->vector); }

void PmergeMe::executeSortDeque() { mergeInsertionSortDeque(this->deque); }

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
  validate(argc, argv);
  this->argc = argc;
  this->argv = argv;
}

PmergeMe::~PmergeMe() {}
