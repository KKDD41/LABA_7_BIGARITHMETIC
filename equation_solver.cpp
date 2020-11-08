#include "equation_solver.h"

// using namespace big_num_arithmetic;

namespace equation_solver {

QuadraticEquation GenerateEquation(const big_num_arithmetic::BigInteger& a,
                              const big_num_arithmetic::BigInteger& root_1,
                              const big_num_arithmetic::BigInteger& root_2) {
  QuadraticEquation equation;
  equation.a = a;
  equation.b = -a * (root_1 + root_2);
  equation.c = a * root_1 * root_2;
  return equation;
}

bool Solve(const QuadraticEquation& equation,
           big_num_arithmetic::BigInteger& root_1,
           big_num_arithmetic::BigInteger& root_2) {
  big_num_arithmetic::BigInteger
  big_disc = equation.b * equation.b - 4 * equation.c * equation.a;
  if (big_disc < 0) {
    return false;
  }
  root_1 = (-equation.b - helpers::Sqrt(big_disc)) / (equation.a * 2);
  root_2 = (-equation.b + helpers::Sqrt(big_disc)) / (equation.a * 2);
  return true;
}

namespace helpers {

template <typename T>
T Sqrt(const T& value) {
  T zero = value - value;
  if (value < zero) {
    throw std::runtime_error("Square root of negative number");
  }
  if (value == zero) {
    return value;
  }
  T one = (value / value);
  if (value == one) {
    return one;
  }
  T left = (T) 0;
  T right = value;
  T middle = (T) 0;
  while (left <= right) {
    middle = (left + right) / (one + one);
    if (middle < value / middle) {
      left = middle + one;
    } else {
      right = middle - one;
    }
    if (middle == value / middle) {
      return middle;
    }
  }
  return right;
}

}  // namespace helpers

}  // namespace equation_solver

// }  // namespace big_num_arithmetic
