#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H_

#include <string>
#include <vector>

namespace big_num_arithmetic {

struct DivisionByZeroError {};

class BigInteger {
 public:
  static int internal_base;

  // CREATION
  BigInteger() = default;
  explicit BigInteger(int64_t);

  // TO INT64_T CONVERTING
  explicit operator int64_t() const;

  // STRING PROCESSING
  static BigInteger FromString(const std::string&, int);
  std::string ToString(int) const;

  // ADDITIONAL FUNCTIONS
  int Sign() const;
  void Negate();
  void Abs();

  // COMPARING
  bool operator==(const BigInteger&) const;
  bool operator<=(const BigInteger&) const;
  bool operator<(const BigInteger&) const;
  bool operator>(const BigInteger&) const;
  bool operator>=(const BigInteger&) const;
  bool operator!=(const BigInteger&) const;

  bool operator==(int64_t) const;
  bool operator!=(int64_t) const;
  bool operator<=(int64_t) const;
  bool operator<(int64_t) const;
  bool operator>(int64_t) const;
  bool operator>=(int64_t) const;
  friend bool operator==(int64_t, const BigInteger&);
  friend bool operator!=(int64_t, const BigInteger&);
  friend bool operator<=(int64_t, const BigInteger&);
  friend bool operator<(int64_t, const BigInteger&);
  friend bool operator>(int64_t, const BigInteger&);
  friend bool operator>=(int64_t, const BigInteger&);

  // UNARY OPERATORS
  BigInteger operator-() const;
  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger& operator--();
  BigInteger operator--(int);

  // MORE OPERATIONS
  void operator+=(const BigInteger&);
  void operator-=(const BigInteger&);
  void operator*=(const BigInteger&);
  void operator/=(const BigInteger&);

  void operator+=(int64_t);
  void operator-=(int64_t);
  void operator*=(int64_t);
  void operator/=(int64_t);

  // OPERATIONS
  BigInteger operator+(const BigInteger&) const;
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  BigInteger operator/(const BigInteger&) const;

  BigInteger operator+(int64_t) const;
  BigInteger operator-(int64_t) const;
  BigInteger operator*(int64_t) const;
  BigInteger operator/(int64_t) const;
  BigInteger operator%(uint32_t) const;
  friend BigInteger operator+(int64_t, const BigInteger&);
  friend BigInteger operator-(int64_t, const BigInteger&);
  friend BigInteger operator*(int64_t, const BigInteger&);
  friend BigInteger operator/(int64_t, const BigInteger&);

  // STREAMS PROCESSING
  friend std::istream& operator>>(std::istream&, BigInteger&);
  friend std::ostream& operator<<(std::ostream& os,
                                  const BigInteger& fraction);

  BigInteger abs() const;
  BigInteger negate();

 private:
  int sign_{0};
  std::vector<int> digits_;

  void CleanLeadZeroes();
  void ReverseDigits();
  static char IntToChar(int);
  static int CharToInt(char);
  static int NextDigit(std::vector<int>&, int, int);
  static int GetDigit(const std::vector<int>&, long long);
  static BigInteger PowerOfTen(long long, const BigInteger&);

  // This function divides big_integer on short_number,
  // where short_number < internal_base.
  static int GetShortDivision(const BigInteger&, const BigInteger&);

  // Next function return sum of two big integers with the same sign.
  // I.e. it will return -(|LHS| + |RHS|), if LHS <= 0, RHS <= 0 and
  // (|LHS| + |RHS|), if LHS >= 0, RHS >= 0 respectively.
  static BigInteger UnsignedSum(const BigInteger&, const BigInteger&);

  // This one is has the same idea. As in previous one, I use it
  // only for |LHS| >= |RHS|, where LHS * RHS >= 0.
  // The function returns (|LHS| - |RHS|), if LHS >= 0, RHS >= 0 and
  // -(|LHS| - |RHS|), if LHS <= 0, RHS <= 0 respectively.
  static BigInteger UnsignedSubtract(const BigInteger&, const BigInteger&);
};

}  // namespace big_num_arithmetic

#endif  // BIG_INTEGER_H_
