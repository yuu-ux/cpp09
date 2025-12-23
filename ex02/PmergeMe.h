#pragma once

#include <errno.h>
#include <deque>
#include <string>
#include <vector>
#include <ctime>

namespace ex02 {
struct pairs_vec {
  int num;                            // 親要素
  std::vector<pairs_vec> nums; // 親より小さい数の集まり
};

struct pairs_deque {
  int num;                              // 親要素
  std::deque<pairs_deque> nums; // 親より小さい数の集まり
};

struct PairDequeLess {
  bool operator()(const ex02::pairs_deque &a, const ex02::pairs_deque &b) const {
    return a.num < b.num;
  }
};

struct PairVecLess {
  bool operator()(const ex02::pairs_vec &a, const ex02::pairs_vec &b) const {
    return a.num < b.num;
  }
};

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

  void validate(int argc, char **argv);
  void initVector();
  void initDeque();

  void executeSortVector();
  void executeSortDeque();

  /**
   * ヤコブスタール数列を用いて、要素を挿入する順序を表す配列を生成
   * @param array_length 生成するインデックスの個数
   */
  std::vector<size_t> makeJacobsthalOrder(size_t array_length);

  /**
   * paires_vec の配列を num をキーとして昇順にソートするための関数
   * @param data ソート対象
   */
  void mergeInsertionSortVec(std::vector<ex02::pairs_vec> &data);
  void mergeInsertionSortDeque(std::deque<ex02::pairs_deque> &data);

  /**
   * 入力をペアに分割するための関数
   * @param data 分割対象
   * @param pending このレベルでペアにできなかった要素
   */
  std::vector<ex02::pairs_vec> makePairsVec(const std::vector<ex02::pairs_vec> &data, std::vector<ex02::pairs_vec> &pending);
  std::deque<ex02::pairs_deque> makePairsDeque(const std::deque<ex02::pairs_deque> &data, std::deque<ex02::pairs_deque> &pending);

  /**
   * num を昇順にソート済みの配列に elem を挿入するための関数
   * @param data インサート対象
   * @param elem インサートする要素
   */
  void insertSortedVec(std::vector<ex02::pairs_vec> &data, const ex02::pairs_vec &elem);
  void insertSortedDeque(std::deque<ex02::pairs_deque> &data, const ex02::pairs_deque &elem);

  void printResult() const;
  void printTime(const std::string &container_name, const std::clock_t start,
                 const std::clock_t end);
};
