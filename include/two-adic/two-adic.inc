#ifndef TWO_ADIC_TWO_ADIC_INC_2024_03_13_438041F1_6E93_4398_AB79_342F9E411B3C
#define TWO_ADIC_TWO_ADIC_INC_2024_03_13_438041F1_6E93_4398_AB79_342F9E411B3C

#include <cmath>

namespace two_adic {

  template <std::size_t precision>
  two_adic<precision>::two_adic()
    : fraction { 0u },
      exponent { 0 } {
  }

  template <std::size_t precision>
  two_adic<precision>::~two_adic() {
  }

  template <std::size_t precision>
  template <typename I>
  two_adic<precision>::two_adic(I value)
    : two_adic { } {
    if (value == 0)
      return;
    else if (value < 0) {
      two_adic x { static_cast<uint64_t>(-value) };
      *this = -x;
    } else {
      fraction = static_cast<uint64_t>(value);
      exponent = 0;
      normalize();
    }
  }

  template <std::size_t precision>
  void two_adic<precision>::normalize() {
    if (is_nan())
      return;
    else if (fraction.is_zero()) {
      exponent = 0;
    } else {
      std::size_t val = fraction.valuation();
      if (0 + exponent + val <= max_exponent) {
	fraction = fraction >> val;
	exponent += val;
      } else {
	fraction = 0u;
	exponent = 0;
      }
    }
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::operator+(two_adic const & x) const {
    if (is_nan() || x.is_nan())
      return nan();
    else if (fraction.is_zero())
      return x;
    else if (x.fraction.is_zero())
      return *this;
    two_adic result;
    if (exponent <= x.exponent) {
      result.fraction = fraction + (x.fraction << (x.exponent - exponent));
      result.exponent = exponent;
    } else {
      result.fraction = x.fraction + (fraction << (exponent - x.exponent));
      result.exponent = x.exponent;
    }
    result.normalize();
    return result;
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::operator-() const {
    if (is_nan())
      return *this;
    two_adic result;
    result.fraction = (~fraction) + 1u;
    result.exponent = exponent;
    result.normalize();
    return result;
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::operator-(two_adic const & x) const {
    return *this + (-x);
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::operator*(two_adic const & x) const {
    if (is_nan() || x.is_nan())
      return nan();
    int exponent_sum = 0 + exponent + x.exponent;
    if (exponent_sum < min_exponent)
      return nan();
    else if (max_exponent < exponent_sum)
      return two_adic { };
    two_adic result;
    result.fraction = fraction * x.fraction;
    result.exponent = static_cast<exponent_type>(exponent_sum);
    result.normalize();
    return result;
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::inverse() const {
    if (is_nan() || fraction.is_zero())
      return nan();
    two_adic fract { *this };
    fract.exponent = 0;
    two_adic result { fract };
    two_adic two { 2u };
    std::size_t iter = static_cast<std::size_t>(std::log2(precision)) + 2;
    for (std::size_t i = 0; i < iter; ++i)
      result = result * (two - fract * result);
    result.exponent = -exponent;
    return result;
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::operator/(two_adic const & x) const {
    return *this * x.inverse();
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::operator<<(std::size_t offset) const {
    if (is_nan() || fraction.is_zero())
      return *this;
    else if (offset > 0 + max_exponent - exponent)
      return two_adic { };
    two_adic result { *this };
    result.exponent += offset;
    return result;
  }  

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::operator>>(std::size_t offset) const {
    if (is_nan() || fraction.is_zero())
      return *this;
    else if (0 - min_exponent + exponent < offset)
      return nan();
    two_adic result { *this };
    result.exponent -= offset;
    return result;
  }  

  template <std::size_t precision>
  double two_adic<precision>::norm() const {
    if (is_nan())
      return std::nan("");
    else if (fraction.is_zero())
      return 0;
    else
      return std::pow(0.5, exponent);
  }

  template <std::size_t precision>
  double two_adic<precision>::distance(two_adic const & x, two_adic const & y) {
    return (y - x).norm();
  }

  template <std::size_t precision>
  two_adic<precision> & two_adic<precision>::operator+=(two_adic const & x) {
    *this = *this + x;
    return *this;
  }

  template <std::size_t precision>
  two_adic<precision> & two_adic<precision>::operator-=(two_adic const & x) {
    *this = *this - x;
    return *this;
  }

  template <std::size_t precision>
  two_adic<precision> & two_adic<precision>::operator*=(two_adic const & x) {
    *this = *this * x;
    return *this;
  }

  template <std::size_t precision>
  two_adic<precision> & two_adic<precision>::operator/=(two_adic const & x) {
    *this = *this / x;
    return *this;
  }

  template <std::size_t precision>
  two_adic<precision> & two_adic<precision>::operator<<=(std::size_t offset) {
    *this = *this << offset;
    return *this;
  }

  template <std::size_t precision>
  two_adic<precision> & two_adic<precision>::operator>>=(std::size_t offset) {
    *this = *this >> offset;
    return *this;
  }

  template <std::size_t precision>
  bool two_adic<precision>::is_nan() const {
    return exponent == nan_exponent;
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::nan() {
    two_adic result;
    result.exponent = nan_exponent;
    return result;
  }
  
  template <std::size_t precision>
  std::ostream & operator<<(std::ostream & out, two_adic<precision> const & x) {
    if (x.is_nan())
      out << "nan";
    else
      out << x.fraction << "P" << x.exponent;
    return out;
  }
}

#endif
