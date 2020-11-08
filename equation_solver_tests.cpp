#include "equation_solver.h"
#include "gtest/gtest.h"

namespace equation_solver {

TEST(Test_12, GenerateEquation) {
  {
    big_num_arithmetic::BigInteger a(1);
    big_num_arithmetic::BigInteger b(5);
    big_num_arithmetic::BigInteger c(6);
    QuadraticEquation equation{a, b, c};
    EXPECT_TRUE(equation.a == 1 && equation.b == 5 && equation.c == 6);
    big_num_arithmetic::BigInteger root_1;
    big_num_arithmetic::BigInteger root_2;
    Solve(equation, root_1, root_2);
    EXPECT_TRUE(root_1 == -3);
    EXPECT_TRUE(root_2 == -2);
    QuadraticEquation new_equation = GenerateEquation(a, root_1, root_2);
    EXPECT_TRUE(equation.a == new_equation.a &&
        equation.b == new_equation.b &&
        equation.c == new_equation.c);
  }
  {
    QuadraticEquation empty_equation;
    EXPECT_TRUE(empty_equation.a == 0 && empty_equation.b == 0 &&
        empty_equation.c == 0);
  }
}

TEST(Test_13, DoubleRoots) {
  {
    big_num_arithmetic::BigInteger a(10);
    big_num_arithmetic::BigInteger root(-5);
    QuadraticEquation equation = GenerateEquation(a, root, root);
    big_num_arithmetic::BigInteger root_1;
    big_num_arithmetic::BigInteger root_2;
    Solve(equation, root_1, root_2);
    EXPECT_TRUE(root_1 == -5);
    EXPECT_TRUE(root_2 == -5);
    EXPECT_TRUE(equation.a == 10 && equation.b == 100 &&
                         equation.c == 250);
  }
  {
    big_num_arithmetic::BigInteger a(100);
    big_num_arithmetic::BigInteger root(0);
    QuadraticEquation equation = GenerateEquation(a, root, root);
    big_num_arithmetic::BigInteger root_1;
    big_num_arithmetic::BigInteger root_2;
    Solve(equation, root_1, root_2);
    EXPECT_TRUE(root_1 == 0);
    EXPECT_TRUE(root_2 == 0);
    EXPECT_TRUE(equation.a == 100 && equation.b == 0 &&
        equation.c == 0);
  }
  {
    big_num_arithmetic::BigInteger a(900);
    big_num_arithmetic::BigInteger b(0);
    big_num_arithmetic::BigInteger c(-90000);
    QuadraticEquation equation{a, b, c};
    big_num_arithmetic::BigInteger root_1;
    big_num_arithmetic::BigInteger root_2;
    Solve(equation, root_1, root_2);
    EXPECT_TRUE(root_1 == -10);
    EXPECT_TRUE(root_2 == 10);
  }
}

TEST(Test_14, ExeptionChecking) {
  {
    big_num_arithmetic::BigInteger a(1000);
    big_num_arithmetic::BigInteger b(1000);
    big_num_arithmetic::BigInteger c(1000);
    QuadraticEquation equation{a, b, c};
    big_num_arithmetic::BigInteger root_1;
    big_num_arithmetic::BigInteger root_2;
    EXPECT_FALSE(Solve(equation, root_1, root_2));
  }
  {
    big_num_arithmetic::BigInteger a(1000138749);
    big_num_arithmetic::BigInteger b(1);
    big_num_arithmetic::BigInteger c(1);
    QuadraticEquation equation{a, b, c};
    big_num_arithmetic::BigInteger root_1;
    big_num_arithmetic::BigInteger root_2;
    EXPECT_FALSE(Solve(equation, root_1, root_2));
  }
}

}  // namespace equation_solver