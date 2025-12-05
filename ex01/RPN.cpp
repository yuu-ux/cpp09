#include "RPN.h"
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>

bool RPN::isOperator(const char token) {
  return (token == '+' || token == '-' || token == '*' || token == '/');
}

bool isInt(double value) { return (static_cast<int>(value) == value); }

RPN::RPN(const char *argv) : result(0) {
  if (!argv) {
    throw std::runtime_error("Invalid argv");
  }

  std::stringstream ss(argv);
  std::string token;
  std::stack<int> stack;

  while (ss >> token) {
    if (isOperator(token[0])) {

      if (stack.size() < RPN::MINIMUM_STACK_SIZE) {
        throw std::runtime_error("Error");
      }

      int rvalue = stack.top();
      stack.pop();
      int lvalue = stack.top();
      stack.pop();

      int result = 0;
      switch (token[0]) {
      case '+':
        result = lvalue + rvalue;
        break;
      case '-':
        result = lvalue - rvalue;
        break;
      case '*':
        result = lvalue * rvalue;
        break;
      case '/':
        if (rvalue == 0) {
          throw std::runtime_error("Error");
        }
        result = lvalue / rvalue;
        break;
      }

      stack.push(result);
      continue;
    }

    double value;
    std::stringstream tmp(token);
    tmp >> value;

    if (!isInt(value) || tmp.fail() || value < 0 || value > MAX_VALUE) {
      throw std::runtime_error("Error");
    }

    stack.push(value);
  }

  if (stack.size() != 1) {
    throw std::runtime_error("Error");
  }

  this->result = stack.top();
}

int RPN::getResult() const { return this->result; }

RPN::~RPN() {}
