#ifndef EQUATION_SOLVER_H_
#define EQUATION_SOLVER_H_

#include "big_integer.h"
#include <exception>
#include <stdexcept>
#include <utility>

// namespace big_num_arithmetic {

namespace equation_solver {

struct QuadraticEquation {
  QuadraticEquation() = default;
  big_num_arithmetic::BigInteger a{0};
  big_num_arithmetic::BigInteger b{0};
  big_num_arithmetic::BigInteger c{0};
};

QuadraticEquation GenerateEquation(const big_num_arithmetic::BigInteger& a,
                                 const big_num_arithmetic::BigInteger& root_1,
                                 const big_num_arithmetic::BigInteger& root_2);

bool Solve(const QuadraticEquation& equation,
           big_num_arithmetic::BigInteger& root_1,
           big_num_arithmetic::BigInteger& root_2);

namespace helpers {

template<typename T>
T Sqrt(const T&);

}  // namespace helpers

}  // namespace equation_solver

#endif  // EQUATION_SOLVER_H_
