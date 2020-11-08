#include "big_integer.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

namespace big_num_arithmetic {

int BigInteger::internal_base = 150;

BigInteger::BigInteger(int64_t short_number) {
  digits_.clear();
  if (short_number == INT64_MIN) {
    sign_ = -1;
    int64_t new_value = INT64_MAX;
    while (new_value) {
      digits_.push_back(new_value % internal_base);
      new_value /= internal_base;
    }
    digits_.at(0)++;
  } else if (short_number == 0) {
    sign_ = 0;
    digits_.push_back(0);
  } else {
    sign_ = (short_number < 0) ? -1 : 1;
    int64_t new_value = (short_number < 0) ? -short_number : short_number;
    while (new_value) {
      digits_.push_back(new_value % internal_base);
      new_value /= internal_base;
    }
  }
}

BigInteger::operator int64_t() const {
  std::string big_str = ((*this).abs()).ToString(10);
  std::string allowed_int64_str = "9223372036854775807";
  if (big_str.size() > allowed_int64_str.size() ||
     (big_str.size() == allowed_int64_str.size() &&
                                              big_str > allowed_int64_str)) {
    throw std::runtime_error("int64_t overflow");
  }
  int64_t short_number = std::stoll(big_str);
  if (sign_ > 0) {
    return short_number;
  } else {
    return -short_number;
  }
}

// ADDITIONAL FUNCTIONS

int BigInteger::Sign() const {
  return sign_;
}

void BigInteger::Negate() {
  sign_ = -sign_;
}

BigInteger BigInteger::negate() {
  sign_ = -sign_;
  return *this;
}

BigInteger BigInteger::abs() const {
  BigInteger value_abs;
  value_abs.sign_ = (sign_ < 0) ? 1 : sign_;
  value_abs.digits_ = digits_;
  return value_abs;
}

void BigInteger::Abs() {
  sign_ = (sign_ < 0) ? 1 : sign_;
}

// HELP-FUNCTIONS

int BigInteger::CharToInt(char sign) {
  if ((sign >= '0') && (sign <= '9')) {
    return (sign - '0');
  } else {
    if ((sign >= 'a') && (sign <= 'z')) {
      return (sign - 'a' + 10);
    }
  }
  return -1;
}

char BigInteger::IntToChar(int n) {
  if (n >= 0 && n <= 9) {
    return n + '0';
  }
  return n - 10 + 'a';
}

int BigInteger::NextDigit(std::vector<int>& current_num, int its_base,
                          int default_base = BigInteger::internal_base) {
  int temp = 0;
  for (int& i : current_num) {
    temp = temp * its_base + i;
    i = temp / default_base;
    temp %= default_base;
  }
  return temp;
}

bool IsZero(const std::vector<int>& array) {
  if (std::all_of(array.begin(), array.end(), [](int a) { return a == 0; })) {
    return true;
  }
  return false;
}

void BigInteger::CleanLeadZeroes() {
  size_t num_of_zeroes = 0;
  for (size_t i = 0; i < digits_.size(); ++i) {
    if (digits_.at(digits_.size() - i - 1) == 0) {
      num_of_zeroes++;
    } else {
      break;
    }
  }
  digits_.erase(digits_.end() - num_of_zeroes,
                digits_.end());
  if (digits_.empty()) {
    digits_.push_back(0);
  }
}

void BigInteger::ReverseDigits() {
  for (int i = 0; i < digits_.size() / 2; i++) {
    std::swap(digits_.at(i),
              digits_.at(digits_.size() - 1 - i));
  }
}

int BigInteger::GetDigit(const std::vector<int>& array_of_digits,
                         long long index) {
  return (index < array_of_digits.size()) ? array_of_digits.at(index) : 0;
}

// STRING PROCESSING

BigInteger BigInteger::FromString(const std::string& str, int base) {
  if ((base < 2) || (base > 36)) {
    throw std::logic_error("Invalid base");
  }
  for (long long i = (str.at(0) == '-') ? 1 : 0; i < str.size(); i++) {
    if (!((str[i] >= '0' && str[i] < IntToChar(base) && str[i] <= '9') ||
        (str[i] >= 'a' && str[i] < IntToChar(base) && str[i] <= 'z'))) {
      throw std::runtime_error("Invalid symbol at index " +
          std::to_string(i));
    }
  }

  BigInteger number;
  if (str.at(0) == '-') {
    number.sign_ = -1;
  } else if (str.at(0) != '-') {
    number.sign_ = 1;
  }

  std::vector<int> temp_array;
  for (long long i = (str.at(0) == '-') ? 1 : 0; i < str.size(); i++) {
    temp_array.push_back(CharToInt(str.at(i)));
  }
  do {
    number.digits_.push_back(NextDigit(temp_array, base));
  } while (!IsZero(temp_array));
  number.CleanLeadZeroes();

  if (number.digits_.at(number.digits_.size() - 1) == 0) {
    number.sign_ = 0;
  }
  return number;
}

std::string BigInteger::ToString(int base) const {
  if (base < 2 || base > 36) {
    throw std::logic_error("Invalid base");
  }
  std::vector<int> temp_array = digits_;
  for (long long i = 0; i < temp_array.size() / 2; i++) {
    std::swap(temp_array.at(i),
              temp_array.at(temp_array.size() - 1 - i));
  }
  std::vector<int> result;
  do {
    result.push_back(NextDigit(temp_array,
                               BigInteger::internal_base, base));
  } while (!IsZero(temp_array));

  if (result.at(result.size() - 1) == 0) {
    return "0";
  }

  std::string fin_str;
  if (sign_ == -1) {
    fin_str += '-';
  }
  for (long long i = result.size() - 1; i >= 0; i--) {
    fin_str += IntToChar(result.at(i));
  }
  return fin_str;
}

// COMPARING TWO BIG INTEGERS

bool BigInteger::operator==(const BigInteger& big_int_rhs) const {
  if (sign_ != big_int_rhs.sign_ ||
      digits_.size() != big_int_rhs.digits_.size()) {
    return false;
  }
  for (size_t i = 0; i < digits_.size(); i++) {
    if (digits_.at(i) != big_int_rhs.digits_.at(i)) {
      return false;
    }
  }
  return true;
}

bool BigInteger::operator<=(const BigInteger& big_int_rhs) const {
  if (sign_ < big_int_rhs.sign_) {
    return true;
  } else if (sign_ > big_int_rhs.sign_) {
    return false;
  } else if (digits_.size() != big_int_rhs.digits_.size()) {
    if (sign_ > 0) {
      return digits_.size() < big_int_rhs.digits_.size();
    }
    return digits_.size() > big_int_rhs.digits_.size();
  }

  for (long long i = digits_.size() - 1; i >= 0; i--) {
    if (sign_ * (digits_.at(i) - big_int_rhs.digits_.at(i)) < 0) {
      return true;
    } else if (sign_ * (digits_.at(i) - big_int_rhs.digits_.at(i))
        > 0) {
      return false;
    } else {
      continue;
    }
  }
  return true;
}

bool BigInteger::operator>=(const BigInteger& big_int_rhs) const {
  if (sign_ > big_int_rhs.sign_) {
    return true;
  } else if (sign_ < big_int_rhs.sign_) {
    return false;
  } else if (digits_.size() != big_int_rhs.digits_.size()) {
    if (sign_ > 0) {
      return big_int_rhs.digits_.size() < digits_.size();
    }
    return big_int_rhs.digits_.size() > digits_.size();
  }

  for (long long i = digits_.size() - 1; i >= 0; i--) {
    if (sign_ * (digits_.at(i) - big_int_rhs.digits_.at(i)) > 0) {
      return true;
    } else if (sign_ * (digits_.at(i) - big_int_rhs.digits_.at(i))
        < 0) {
      return false;
    } else {
      continue;
    }
  }
  return true;
}

bool BigInteger::operator<(const BigInteger& big_int_rhs) const {
  return !(*this >= big_int_rhs);
}

bool BigInteger::operator>(const BigInteger& big_int_rhs) const {
  return !(*this <= big_int_rhs);
}

bool BigInteger::operator!=(const BigInteger& big_int_rhs) const {
  return !((*this) == big_int_rhs);
}

// COMPARING BIG INTEGER AND SHORT NUMBER

bool BigInteger::operator==(int64_t short_number) const {
  return (*this) == BigInteger(short_number);
}

bool BigInteger::operator!=(int64_t short_number) const {
  return (*this) != BigInteger(short_number);
}

bool BigInteger::operator<=(int64_t short_number) const {
  return (*this) <= BigInteger(short_number);
}

bool BigInteger::operator<(int64_t short_number) const {
  return (*this) < BigInteger(short_number);
}

bool BigInteger::operator>(int64_t short_number) const {
  return (*this) > BigInteger(short_number);
}

bool BigInteger::operator>=(int64_t short_number) const {
  return (*this) >= BigInteger(short_number);
}

bool operator==(int64_t short_int, const BigInteger& big_int) {
  return big_int == short_int;
}

bool operator!=(int64_t short_int, const BigInteger& big_int) {
  return big_int != short_int;
}

bool operator<=(int64_t short_int, const BigInteger& big_int) {
  return big_int >= short_int;
}

bool operator<(int64_t short_int, const BigInteger& big_int) {
  return big_int > short_int;
}

bool operator>(int64_t short_int, const BigInteger& big_int) {
  return big_int < short_int;
}

bool operator>=(int64_t short_int, const BigInteger& big_int) {
  return big_int <= short_int;
}

// BINARY OPERATIONS

BigInteger BigInteger::UnsignedSum(const BigInteger& big_int_lhs,
                                   const BigInteger& big_int_rhs) {
  BigInteger sum;
  int temp = 0;
  for (long long i = 0;
       i < std::max(big_int_rhs.digits_.size(),
                    big_int_lhs.digits_.size());
       i++) {
    temp = temp + GetDigit(big_int_rhs.digits_, i)
        + GetDigit(big_int_lhs.digits_, i);
    sum.digits_.push_back(temp % internal_base);
    temp /= internal_base;
  }
  if (temp != 0) {
    sum.digits_.push_back(temp);
  }
  if (sum.digits_.at(sum.digits_.size() - 1) != 0) {
    if (big_int_lhs.sign_ == 0) {
      sum.sign_ = big_int_rhs.sign_;
    } else {
      sum.sign_ = big_int_lhs.sign_;
    }
  }
  return sum;
}

BigInteger BigInteger::UnsignedSubtract(const BigInteger& big_int_lhs,
                                        const BigInteger& big_int_rhs) {
  BigInteger subtract;
  size_t index = 0;
  int current_difference = 0;
  int temp = 0;
  while (index < big_int_rhs.digits_.size()) {
    current_difference =
        big_int_lhs.digits_.at(index) - big_int_rhs.digits_.at(index)
            - temp;
    if (current_difference < 0) {
      current_difference += internal_base;
      temp = 1;
    } else {
      temp = 0;
    }
    subtract.digits_.push_back(current_difference);
    ++index;
  }
  while (index < big_int_lhs.digits_.size()) {
    current_difference = big_int_lhs.digits_.at(index) - temp;
    if (current_difference < 0) {
      current_difference += internal_base;
    } else {
      temp = 0;
    }
    if ((big_int_lhs.digits_.size() - 1 == index)
        && (current_difference == 0)) {
      break;
    } else {
      subtract.digits_.push_back(current_difference);
    }
    ++index;
  }
  subtract.CleanLeadZeroes();
  if (subtract.digits_.at(subtract.digits_.size() - 1) != 0) {
    subtract.sign_ = big_int_lhs.sign_;
  }
  return subtract;
}

BigInteger BigInteger::operator+(const BigInteger& big_int_rhs) const {
  if (sign_ == big_int_rhs.sign_) {
    return UnsignedSum(*this, big_int_rhs);
  } else if ((*this).abs() >= big_int_rhs.abs()) {
    return UnsignedSubtract(*this, big_int_rhs);
  }
  return UnsignedSubtract(big_int_rhs, *this);
}

BigInteger BigInteger::operator-(const BigInteger& big_int_rhs) const {
  if (sign_ == 0) {
    BigInteger result = big_int_rhs;
    return result.negate();
  }
  if (big_int_rhs.sign_ == 0) {
    return (*this);
  }
  if (sign_ != big_int_rhs.sign_) {
    return UnsignedSum(*this, big_int_rhs);
  }
  if ((*this).abs() >= big_int_rhs.abs()) {
    return UnsignedSubtract(*this, big_int_rhs);
  }
  return UnsignedSubtract(big_int_rhs, *this).negate();
}


BigInteger BigInteger::operator*(const BigInteger& big_int_rhs) const {
  size_t first_size = big_int_rhs.digits_.size();
  size_t second_size = digits_.size();

  BigInteger product;
  product.sign_ = sign_ * big_int_rhs.sign_;
  product.digits_.resize(first_size + second_size);
  for (size_t i = 0; i < first_size; ++i) {
    for (size_t j = 0; j < second_size; ++j) {
      product.digits_.at(i + j) +=
          big_int_rhs.digits_.at(i) * digits_.at(j);
    }
    for (size_t j = 0; j < product.digits_.size(); ++j) {
      if (product.digits_.at(j) > internal_base - 1) {
        product.digits_.at(j + 1) +=
            product.digits_.at(j) / internal_base;
        product.digits_.at(j) %= internal_base;
      }
    }
  }
  product.CleanLeadZeroes();
  return product;
}

BigInteger BigInteger::PowerOfTen(long long power, const BigInteger& value) {
  BigInteger result;
  result.sign_ = 1;
  result.digits_.resize(power);
  for (int digit : value.digits_) {
    result.digits_.push_back(digit);
  }
  return result;
}

int BigInteger::GetShortDivision(const BigInteger& temp_division,
                                 const BigInteger& big_int_rhs) {
  int64_t left = 0;
  int64_t right = internal_base;
  int64_t middle = 0;
  int result;
  while (left <= right) {
    middle = (left + right) / 2;
    BigInteger temp = middle * big_int_rhs;
    if (temp_division >= temp) {
      result = middle;
      left = middle + 1;
    } else {
      right = middle - 1;
    }
  }
  return result;
}

BigInteger BigInteger::operator/(const BigInteger& big_int_rhs) const {
  if (IsZero(big_int_rhs.digits_)) {
    throw DivisionByZeroError{};
  }
  if (IsZero(digits_) ||
      (digits_.size() < big_int_rhs.digits_.size())) {
    return BigInteger(0);
  }
  BigInteger result;
  BigInteger division;

  division.sign_ = 1;
  division.digits_ = digits_;
  BigInteger
      current_big_rhs = PowerOfTen(digits_.size() -
          big_int_rhs.digits_.size(), big_int_rhs);
  for (long long i = digits_.size() - big_int_rhs.digits_.size(); i >= 0;
                                                                      i--) {
    int64_t digit = GetShortDivision(division, current_big_rhs);
    result.digits_.push_back(digit);

    division = division - current_big_rhs * digit;
    current_big_rhs.digits_.erase(current_big_rhs.digits_.begin());
  }
  result.ReverseDigits();
  result.CleanLeadZeroes();
  result.sign_ = sign_ * big_int_rhs.sign_;
  return result;
}

// OPERATIONS WITH SHORT NUMBERS

BigInteger operator+(int64_t short_number, const BigInteger& big_int) {
  BigInteger a(short_number);
  return a + big_int;
}

BigInteger operator-(int64_t short_number, const BigInteger& big_int) {
  return BigInteger(short_number) - big_int;
}

BigInteger BigInteger::operator+(int64_t short_number) const {
  BigInteger a(short_number);
  BigInteger res = (*this) + a;
  return res;
}

BigInteger BigInteger::operator-(int64_t short_number) const {
  BigInteger a(short_number);
  BigInteger res = (*this) - a;
  return res;
}

BigInteger BigInteger::operator*(int64_t short_number) const {
  return (*this) * BigInteger(short_number);
}

BigInteger operator*(int64_t short_number, const BigInteger& big_int) {
  return BigInteger(short_number) * big_int;
}

BigInteger BigInteger::operator/(int64_t short_number) const {
  if (short_number == 0) {
    throw DivisionByZeroError{};
  }
  BigInteger division;
  int64_t short_number_abs;
  if (short_number < 0) {
    short_number_abs = -short_number;
    division.sign_ = -sign_;
  } else {
    short_number_abs = short_number;
    division.sign_ = sign_;
  }
  int64_t reminder = 0;
  std::vector<int> temp_array = digits_;
  for (long long i = digits_.size() - 1; i >= 0; --i) {
    long long current_digit = temp_array.at(i) + reminder * internal_base;
    temp_array.at(i) = current_digit / short_number_abs;
    reminder = current_digit % short_number_abs;
  }
  division.digits_ = temp_array;
  division.CleanLeadZeroes();
  return division;
}

BigInteger operator/(int64_t short_int, const BigInteger& big_int) {
  if (big_int.sign_ == 0) {
    throw DivisionByZeroError{};
  }
  return BigInteger(short_int) / big_int;
}

void BigInteger::operator+=(const BigInteger& big_int_rhs) {
  (*this) = (*this) + big_int_rhs;
}

void BigInteger::operator-=(const BigInteger& big_int_rhs) {
  (*this) = (*this) - big_int_rhs;
}

void BigInteger::operator*=(const BigInteger& big_int_rhs) {
  (*this) = (*this) * big_int_rhs;
}

void BigInteger::operator/=(const BigInteger& big_int_rhs) {
  if (big_int_rhs == BigInteger(0)) {
    throw DivisionByZeroError{};
  }
  (*this) = *this / big_int_rhs;
}

void BigInteger::operator+=(int64_t short_number) {
  (*this) = (*this) + short_number;
}

void BigInteger::operator-=(int64_t short_number) {
  (*this) = (*this) - short_number;
}

void BigInteger::operator*=(int64_t short_number) {
  (*this) = (*this) * short_number;
}

void BigInteger::operator/=(int64_t short_number) {
  if (short_number == 0) {
    throw DivisionByZeroError{};
  }
  (*this) = (*this) / BigInteger(short_number);
}

BigInteger BigInteger::operator%(uint32_t short_number) const {
  int64_t signed_short = short_number;
  if (signed_short == 0) {
    throw DivisionByZeroError{};
  }
  BigInteger reduce = (*this) - ((*this) / signed_short) * signed_short;
  if (reduce >= 0) {
    return reduce;
  } else {
    return reduce + signed_short;
  }
}

// UNARY OPERATIONS

BigInteger BigInteger::operator-() const {
  BigInteger result = (*this);
  result.sign_ = -sign_;
  return result;
}

BigInteger& BigInteger::operator++() {
  (*this) += 1;
  return *this;
}

BigInteger BigInteger::operator++(int) {
  (*this) += 1;
  return (*this) - 1;
}

BigInteger& BigInteger::operator--() {
  (*this) -= 1;
  return *this;
}

BigInteger BigInteger::operator--(int) {
  (*this) -= 1;
  return (*this) + 1;
}

}  // namespace big_num_arithmetic

// STREAMS PROCESSING

std::istream& big_num_arithmetic::operator>>(std::istream& input,
                         big_num_arithmetic::BigInteger& big_int) {
  std::string temp;
  input >> temp;
  auto flag = input.flags();
  int base = 10;
  if (flag & std::ios::oct) {
    base = 8;
  } else if (flag & std::ios::hex) {
    base = 16;
  }

  int index = 0;
  if (base != 10) {
    if (temp.at(index) == '-') {
      index++;
    }
    if (temp.at(index) == '0' && index != temp.size() - 1) {
      int for_deleting = 1;
      if (temp.at(index + 1) == 'x') {
        for_deleting += 1;
      }
      temp.erase(index, for_deleting);
    }
  }
  big_int = big_num_arithmetic::BigInteger::FromString(temp, base);
  return input;
}

std::ostream& big_num_arithmetic::operator<<(std::ostream& output,
                         const big_num_arithmetic::BigInteger& big_int) {
  int base = 10;
  auto flag = output.flags();
  if (flag & std::ios::hex) {
    base = 16;
  } else if (flag & std::ios::oct) {
    base = 8;
  }
  big_num_arithmetic::BigInteger temp_value{big_int};
  std::string result{};
  if (temp_value.Sign() == -1) {
    result = "-";
    temp_value.Abs();
  }
  if (flag & std::ios::showbase) {
    if (base == 8) {
      result += "0";
    } else if (base == 16) {
      result += "0x";
    }
  }
  result += temp_value.ToString(base);
  return output << result;
}
