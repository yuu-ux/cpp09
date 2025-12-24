#pragma once

#include <limits.h>
#include <stack>
class RPN {
private:
  static const int MAX_VALUE = 10;
  static const int MINIMUM_STACK_SIZE = 2;

  int result;

public:
  RPN(const char *argv);
  ~RPN();

  int getResult() const;

private:
  RPN &operator=(const RPN &rhs);
  RPN(const RPN &other);

  static bool isOperator(const char token);
};
