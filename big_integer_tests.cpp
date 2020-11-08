#include "big_integer.h"
#include <gtest/gtest.h>

namespace big_num_arithmetic {

TEST(Test_0, ShortNumberConstructorChecing) {
  BigInteger value_1(150324);
  BigInteger value_2(-151);
  BigInteger value_0(0);
  BigInteger value_min(INT64_MIN);
  EXPECT_TRUE(value_min == -BigInteger(INT64_MAX) - 1);
  EXPECT_TRUE(value_0.Sign() == 0);
  EXPECT_TRUE(value_1.Sign() == 1);
  EXPECT_TRUE(value_2.Sign() == -1);
  EXPECT_EQ(value_1.ToString(10), "150324");
  EXPECT_EQ(value_2.ToString(10), "-151");
}

TEST(Test_1, CompareChecking) {
  {
    BigInteger value_1(-88888);
    int64_t value_2(-77777);
    EXPECT_TRUE(value_2 == -77777);
    EXPECT_TRUE(value_2 >= value_1);
    EXPECT_TRUE(value_2 > value_1);
    EXPECT_TRUE(value_2 - value_1 > 0);
    EXPECT_FALSE(value_2 <= value_1);
    EXPECT_FALSE(value_2 < value_1);
  }
  {
    BigInteger value_1(-88888);
    BigInteger value_2(-77777);
    EXPECT_TRUE(value_2 >= value_1);
    EXPECT_TRUE(value_2 > value_1);
    EXPECT_TRUE(value_2 - value_1 > 0);
    EXPECT_FALSE(value_2 <= value_1);
    EXPECT_FALSE(value_2 < value_1);
  }
  {
    int64_t value_1 = 398413209;
    BigInteger value_2(-38474);
    BigInteger zero(0);
    EXPECT_TRUE(value_1 >= value_2);
    EXPECT_TRUE(value_1 > value_2);
    EXPECT_TRUE(value_1 > value_2.abs());
    EXPECT_TRUE(value_1 >= value_2.abs());
    EXPECT_TRUE(value_1 > 0);
    EXPECT_TRUE(value_1 >= 0);
    EXPECT_TRUE(value_2 < 0);
    EXPECT_TRUE(value_2.abs() > 0);
    EXPECT_TRUE(value_2 <= zero);
    EXPECT_FALSE(value_1 < 0);
    EXPECT_FALSE(value_1 <= 0);
    EXPECT_FALSE(value_2 >= zero);
    EXPECT_FALSE(value_1 <= 0);
    EXPECT_FALSE(value_1 > value_1);
    EXPECT_FALSE(value_2 < value_2);
    EXPECT_TRUE(value_1 >= value_1);
    EXPECT_TRUE(value_2 <= value_2);
  }
  {
    BigInteger value_1(398413209);
    BigInteger value_2(-38474);
    BigInteger zero(0);
    EXPECT_TRUE(value_1 >= value_2);
    EXPECT_TRUE(value_1 > value_2);
    EXPECT_TRUE(value_1 > value_2.abs());
    EXPECT_TRUE(value_1 >= value_2.abs());
    EXPECT_TRUE(value_1 > 0);
    EXPECT_TRUE(value_1 >= 0);
    EXPECT_TRUE(value_2 < 0);
    EXPECT_TRUE(value_2.abs() > 0);
    EXPECT_TRUE(value_2 <= zero);
    EXPECT_FALSE(value_1 < 0);
    EXPECT_FALSE(value_1 <= 0);
    EXPECT_FALSE(value_2 >= zero);
    EXPECT_FALSE(value_1 <= 0);
    EXPECT_FALSE(value_1 > value_1);
    EXPECT_FALSE(value_2 < value_2);
    EXPECT_TRUE(value_1 >= value_1);
    EXPECT_TRUE(value_2 <= value_2);
  }
  {
    BigInteger value_1 = BigInteger::FromString("-284212", 10);
    BigInteger value_2 = BigInteger::FromString("-294793", 10);
    EXPECT_TRUE(value_2 <= value_1);
    EXPECT_TRUE(value_1 >= value_2);
    EXPECT_TRUE(value_2 < value_1);
    EXPECT_TRUE(value_1 > value_2);
    EXPECT_TRUE(value_1 != value_2);
  }
  {
    BigInteger value_1 = BigInteger::FromString("-a312d9", 16);
    BigInteger value_2 = BigInteger::FromString("-10687193", 10);
    EXPECT_TRUE(value_2 <= value_1);
    EXPECT_TRUE(value_1 >= value_2);
    EXPECT_FALSE(value_2 < value_1);
    EXPECT_FALSE(value_1 > value_2);
    EXPECT_FALSE(value_1 != value_2);
  }
  {
    BigInteger value_1 = BigInteger::FromString("0", 16);
    BigInteger value_2 = BigInteger::FromString("-0", 10);
    EXPECT_TRUE(value_2 <= value_1);
    EXPECT_TRUE(value_1 >= value_2);
    EXPECT_FALSE(value_2 < value_1);
    EXPECT_FALSE(value_1 > value_2);
    EXPECT_FALSE(value_1 != value_2);
  }
  {
    BigInteger value_1 = BigInteger::FromString("00011111100111", 16);
    BigInteger value_2 =
        BigInteger::FromString("10001000100010001000100000000000100010001", 2);
    EXPECT_TRUE(value_2 <= value_1);
    EXPECT_TRUE(value_1 >= value_2);
    EXPECT_FALSE(value_2 < value_1);
    EXPECT_FALSE(value_1 > value_2);
    EXPECT_FALSE(value_1 != value_2);
  }
  {
    BigInteger value_1 = BigInteger::FromString("-00012736c", 16);
    BigInteger value_2 =
        BigInteger::FromString("0000z134d3c34r", 36);
    EXPECT_FALSE(value_2 <= value_1);
    EXPECT_FALSE(value_1 >= value_2);
    EXPECT_FALSE(value_2 < value_1);
    EXPECT_FALSE(value_1 > value_2);
    EXPECT_TRUE(value_1 != value_2);
  }
  {
    BigInteger value_1 = BigInteger::FromString("-2836431234134", 10);
    int64_t value_2 = -238479235;
    EXPECT_FALSE(value_1 == value_2);
    EXPECT_TRUE(value_1 <= value_2);
    EXPECT_FALSE(value_1 >= value_2);
    EXPECT_TRUE(value_1 < value_2);
    EXPECT_FALSE(value_1 > value_2);
    EXPECT_TRUE(value_1 != value_2);
  }
}

TEST(Test_2, StringProcessingChecking) {
  {
    std::string str_1 = "-a1513rdqi93600038hhbuqekrgkue3";
    std::string str_2 = "2384729364572354fae3f797297a623";
    EXPECT_EQ(str_1, BigInteger::FromString(str_1, 35).ToString(35));
    EXPECT_EQ(str_2, BigInteger::FromString(str_2, 16).ToString(16));
  }
}

TEST(Test_3, ModuloChecking) {
  BigInteger value = BigInteger::FromString("-92457", 10);
  BigInteger value_abs = value.abs();
  EXPECT_EQ(value_abs.ToString(10), "92457");
  value.Negate();
  EXPECT_TRUE(value == value_abs);
}

TEST(Test_4, SumAndSubtractChecking) {
  {
    BigInteger value_1 = BigInteger::FromString("-494", 10);
    BigInteger value_2 = BigInteger::FromString("-666", 10);
    BigInteger sum = value_1 + value_2;
    BigInteger subtract = value_1 - value_2;
    EXPECT_EQ(subtract.ToString(10), "172");
    EXPECT_EQ(sum.ToString(10), "-1160");
    value_1 += value_2;
    EXPECT_TRUE(sum == value_1);
  }
  {
    BigInteger value_1 = BigInteger::FromString("4940", 10);
    BigInteger value_2 = BigInteger::FromString("-6660", 10);
    BigInteger sum = value_1 + value_2;
    BigInteger subtract = value_1 - value_2;
    EXPECT_EQ(subtract.ToString(10), "11600");
    EXPECT_EQ(sum.ToString(10), "-1720");
    value_1 -= value_2;
    EXPECT_TRUE(subtract == value_1);
  }
  {
    BigInteger value_1 = BigInteger::FromString("0", 10);
    BigInteger value_2 = BigInteger::FromString("-066624870", 10);
    BigInteger sum = value_1 + value_2;
    BigInteger sum_2 = value_2 + value_1;
    BigInteger subtract = value_1 - value_2;
    BigInteger subtract_2 = value_2 - value_1;
    EXPECT_TRUE(sum_2 == -66624870);
    EXPECT_TRUE(subtract_2 == -66624870);
    EXPECT_EQ(subtract.ToString(10), "66624870");
    EXPECT_EQ(sum.ToString(10), "-66624870");
  }
  {
    BigInteger value_1 = BigInteger::FromString("0", 10);
    BigInteger value_2 = BigInteger::FromString("0", 10);
    BigInteger sum = value_1 + value_2;
    BigInteger subtract = value_1 - value_2;
    EXPECT_EQ(subtract.ToString(10), "0");
    EXPECT_EQ(sum.ToString(10), "0");
    EXPECT_TRUE(sum.Sign() == 0 && subtract.Sign() == 0);
  }
  {
    BigInteger value_1(228);
    int64_t value_2 = 228;
    BigInteger subtract = value_1 - value_2;
    BigInteger sum = value_1 + (-value_2);
    EXPECT_EQ(subtract.ToString(10), "0");
    EXPECT_EQ(sum.ToString(10), "0");
    EXPECT_TRUE(sum.Sign() == 0);
    EXPECT_TRUE(subtract.Sign() == 0);
  }
  {
    BigInteger value_1 = BigInteger::FromString("138474", 10);
    int64_t value_2 = -294762;
    BigInteger sum_1 = value_1 + value_2;
    BigInteger sum_2 = value_2 + value_1;
    BigInteger subtract_1 = value_1 - value_2;
    BigInteger subtract_2 = value_2 - value_1;
    EXPECT_EQ(subtract_1.ToString(10),
              std::to_string(138474 + 294762));
    EXPECT_EQ(subtract_2.ToString(10),
              std::to_string(-138474 - 294762));
    EXPECT_EQ(sum_1.ToString(10), std::to_string(138474 - 294762));
    EXPECT_EQ(sum_2.ToString(10), std::to_string(138474 - 294762));
  }
}

TEST(Test_5, MultiplyingAndDivisionChecking) {
  {
    BigInteger value_1 = BigInteger::FromString("401", 10);
    BigInteger value_2 = BigInteger::FromString("392", 10);
    int64_t value_3 = 392;
    BigInteger product = value_1 * value_2;
    EXPECT_EQ(product.ToString(10), "157192");
    EXPECT_TRUE(product == value_3 * value_1);
  }
  {
    BigInteger value_1 = BigInteger::FromString("0", 10);
    BigInteger value_2 = BigInteger::FromString("0238743", 10);
    BigInteger product = value_1 * value_2;
    BigInteger division = value_1 / value_2;
    EXPECT_EQ(product.ToString(10), "0");
    EXPECT_TRUE(product.Sign() == 0);
    EXPECT_ANY_THROW(value_2 / 0);
    value_1 /= value_2;
    EXPECT_TRUE(division == value_1);
  }
  {
    BigInteger value_1 = BigInteger::FromString("-4010", 10);
    BigInteger value_2 = BigInteger::FromString("3920001", 10);
    int64_t value_3 = 392;
    BigInteger product = value_1 * value_2;
    BigInteger division = value_1 / value_3;
    EXPECT_EQ(product.ToString(10), "-15719204010");
    EXPECT_EQ(division.ToString(10), "-10");
    EXPECT_TRUE(product.Sign() == -1);
    value_1 *= value_2;
    EXPECT_TRUE(product == value_1);
  }
  {
    BigInteger value_1(1859);
    BigInteger value_4(61);
    BigInteger value_5(-62);
    int64_t value_2 = 61;
    int64_t value_3 = -62;
    BigInteger subtract_1 = value_1 / value_4;
    BigInteger subtract_2 = value_1 / value_5;
    EXPECT_TRUE(subtract_1 == value_1 / value_2);
    EXPECT_TRUE(subtract_2 == value_1 / value_3);
  }
  {
    BigInteger value_1(-239847);
    BigInteger value_2(98273);
    EXPECT_TRUE(value_1 / value_2 == BigInteger(-239847 / 98273));
  }
}

TEST(Test_6, InputOutputTesting) {
  {
    std::stringstream testing_str;
    testing_str.flags(std::ios::hex);
    testing_str << "0x011111";
    BigInteger value;
    testing_str >> value;
    EXPECT_TRUE(value == 69905);

    testing_str.clear();
    testing_str.flags(std::ios::hex);
    testing_str << "000011111";
    testing_str >> value;
    EXPECT_TRUE(value == 69905);
  }
  {
    std::stringstream testing_str;
    testing_str.flags(std::ios::hex);
    testing_str << "-123524";
    BigInteger value;
    testing_str >> value;
    EXPECT_EQ(value, -1193252);

    testing_str.clear();
    testing_str << "-0x101";
    testing_str >> value;
    EXPECT_EQ(value, -257);
  }
  {
    std::stringstream testing_str;
    testing_str.flags(std::ios::dec);
    testing_str << "123524";
    BigInteger value;
    testing_str >> value;
    EXPECT_EQ(value, 123524);
  }
  {
    std::stringstream testing_str;
    testing_str.flags(std::ios::oct);
    testing_str << "1";
    BigInteger value;
    testing_str >> value;
    EXPECT_EQ(value, 1);
  }
}

TEST(Test_7, UnaryOperationsChecking) {
  {
    BigInteger value(888);
    BigInteger zero(0);
    EXPECT_TRUE(-zero == 0);
    EXPECT_TRUE(-value == -888);
    EXPECT_TRUE(-(-value) == 888);
    value *= zero;
    EXPECT_TRUE(value == 0);
  }
  {
    BigInteger value_1(999);
    value_1 += 1;
    EXPECT_TRUE(value_1 == 1000);
    value_1 /= -10;
    EXPECT_TRUE(value_1 == -100);
    value_1 -= -100;
    EXPECT_TRUE(value_1 == 0);
  }
  {
    BigInteger value(-1);
    ++value;
    EXPECT_TRUE(value == 0);
    BigInteger next_value = value++;
    EXPECT_TRUE(next_value == 0);
    EXPECT_TRUE(value == 1);
    next_value = --value;
    EXPECT_TRUE(next_value == 0);
    EXPECT_TRUE(value == 0);
    value--;
    EXPECT_TRUE(value == -1);
  }
  {
    BigInteger value(0);
    value = value - 1;
    EXPECT_TRUE(value == -1);
  }
}

TEST(Test_8, ModuleOperationChecking) {
  {
    uint32_t short_value = 0;
    BigInteger big_int(297562);
    EXPECT_ANY_THROW(big_int % short_value);
  }
  {
    uint32_t short_value = 1111119;
    BigInteger big_int(1111118);
    EXPECT_TRUE(big_int == big_int % short_value);
    EXPECT_TRUE(1 == -big_int % short_value);
  }
  {
    uint32_t short_value = UINT32_MAX;
    BigInteger big_int = BigInteger::FromString("18446744073709551615", 10);
    EXPECT_TRUE(0 == big_int % short_value);
    EXPECT_TRUE(0 == -big_int % short_value);
  }
}

TEST(Test_10, ToInt64Converting) {
  {
    BigInteger too_long_big_int =
        BigInteger::FromString("3864917362402141347868756865",
                               10);
    BigInteger still_too_long_big_int =
        BigInteger::FromString("-28194691286541826333789698656754874",
                               10);
    EXPECT_THROW(int64_t x(too_long_big_int),
                 std::exception);
    EXPECT_THROW(int64_t x(still_too_long_big_int),
                 std::exception);
  }
  {
    BigInteger not_long_big_int(1284912632);
    EXPECT_EQ(int64_t(not_long_big_int), 1284912632);
    EXPECT_EQ(int64_t(-not_long_big_int), -1284912632);
  }
  {
    BigInteger big_int(INT64_MAX);
    BigInteger other_big_int(INT64_MIN);
    EXPECT_EQ(int64_t(other_big_int + 1), INT64_MIN + 1);
    EXPECT_EQ(int64_t(big_int), INT64_MAX);

    // Because |other_big_int| must be less than INT64_MAX,
    // according to the problem.
    EXPECT_THROW(int64_t x(other_big_int),
                 std::exception);
  }
  {
    BigInteger zero(0);
    EXPECT_EQ(0, int64_t(zero));
  }
  {
    for (int64_t i = INT64_MIN + 1; i < INT64_MIN + 151; i++) {
      EXPECT_EQ(std::to_string(i),
                std::to_string(int64_t(BigInteger(i))));
    }
  }
}


}  // namespace big_num_arithmetic
