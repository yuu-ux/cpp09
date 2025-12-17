#pragma once

#include <deque>
#include <string>
#include <vector>

namespace ex02 {
typedef struct pairs_vec {
  int num; // 親要素
  std::vector<struct pairs_vec> nums; // 親より小さい数の集まり
} pairs_vec;

typedef struct pairs_deque {
  int num; // 親要素
  std::vector<struct pairs_deque> nums; // 親より小さい数の集まり
} pairs_deque;

struct PairVecLess {
    bool operator()(const ex02::pairs_vec& a, const ex02::pairs_vec& b) const { return a.num < b.num; }
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

  bool validate(int argc, char **argv);
  void initVector();
  void initDeque();

  void executeSortVector();
  void executeSortDeque();

/**
  * paires_vec の配列を num をキーとして昇順にソートするための関数
  * @param data ソート対象
  */
  void mergeInsertionSort(std::vector<ex02::pairs_vec>& data);

 /**
  * 入力をペアに分割するための関数
  * @param data 分割対象
  * @param pending このレベルでペアにできなかった要素
 */
  std::vector<ex02::pairs_vec> makePairs(const std::vector<ex02::pairs_vec>& data, std::vector<ex02::pairs_vec>& pending);

 /**
  * num を昇順にソート済みの配列に elem を挿入するための関数
  * @param data インサート対象
  * @param elem インサートする要素
  */
  void insertSorted(std::vector<ex02::pairs_vec>& data, const ex02::pairs_vec& elem);

  void printResult() const;
  void printTime(const std::string &container_name, const std::clock_t start,
                 const std::clock_t end);
};
