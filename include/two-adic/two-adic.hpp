#ifndef TWO_ADIC_TWO_ADIC_HPP_2024_03_13_DED3B56D_431A_44AE_9FB6_0AB317A77A2D
#define TWO_ADIC_TWO_ADIC_HPP_2024_03_13_DED3B56D_431A_44AE_9FB6_0AB317A77A2D

#include <iostream>

#include <two-adic/nat.hpp>

namespace two_adic {

  template <std::size_t precision>
  class two_adic {

    static std::size_t constexpr nat_size = (precision / 8) + (precision % 8 != 0);
    using fraction_type = nat<nat_size>;
    using exponent_type = int16_t;

    fraction_type fraction;
    exponent_type exponent;

    two_adic();

    void normalize();
    
  public:

    two_adic(two_adic const &) = default;
    two_adic(two_adic &&) = default;
    two_adic & operator=(two_adic const &) = default;
    two_adic & operator=(two_adic &&) = default;
    ~two_adic();

    template <typename I>
    two_adic(I);

    two_adic operator+(two_adic const &) const;
    two_adic operator-() const;
    two_adic operator-(two_adic const &) const;
    two_adic operator*(two_adic const &) const;
    two_adic inverse() const;
    two_adic operator/(two_adic const &) const;
    two_adic operator<<(std::size_t) const;
    two_adic operator>>(std::size_t) const;

    double norm() const;

    static double distance(two_adic const &, two_adic const &);

    two_adic & operator+=(two_adic const &);
    two_adic & operator-=(two_adic const &);
    two_adic & operator*=(two_adic const &);
    two_adic & operator/=(two_adic const &);
    two_adic & operator<<=(std::size_t);
    two_adic & operator>>=(std::size_t);
    
    template <std::size_t precision2>
    friend std::ostream & operator<<(std::ostream &, two_adic<precision2> const &);
  };
  
}

#include <two-adic/two-adic.inc>

#endif
