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
    if (fraction.is_zero()) {
      exponent = 0;
    } else {
      std::size_t val = fraction.valuation();;
      fraction = fraction >> val;
      exponent += val;
    }
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::operator+(two_adic const & x) const {
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
    two_adic result;
    result.fraction = fraction * x.fraction;
    result.exponent = exponent + x.exponent;
    result.normalize();
    return result;
  }

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::inverse() const {
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
    two_adic result { *this };
    result.exponent += offset;
    return result;
  }  

  template <std::size_t precision>
  two_adic<precision> two_adic<precision>::operator>>(std::size_t offset) const {
    two_adic result { *this };
    result.exponent -= offset;
    return result;
  }  

  template <std::size_t precision>
  double two_adic<precision>::norm() const {
    if (fraction.is_zero())
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
  std::ostream & operator<<(std::ostream & out, two_adic<precision> const & x) {
    out << x.fraction << "P" << x.exponent;
    return out;
  }
}

#endif
