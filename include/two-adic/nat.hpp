#ifndef TWO_ADIC_NAT_HPP_2024_03_13_5562CA4B_0655_4E26_90A4_121EB08B14D8
#define TWO_ADIC_NAT_HPP_2024_03_13_5562CA4B_0655_4E26_90A4_121EB08B14D8

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>

namespace two_adic {

  template <std::size_t size>
  class nat {

    std::array<std::uint8_t, size> buffer;

    nat();

    std::uint8_t get_byte_at(std::size_t) const;
    std::uint8_t get_byte_at_n(std::size_t) const;
    
  public:

    nat(nat const &) = default;
    nat(nat &&) = default;
    nat & operator=(nat const &) = default;
    nat & operator=(nat &&) = default;
    ~nat();
    
    template <typename U>
    nat(U);

    nat operator+(nat const &) const;
    nat operator*(nat const &) const;
    nat operator<<(std::size_t) const;
    nat operator>>(std::size_t) const;
    bool is_zero() const;
    std::size_t valuation() const;

    bool operator==(nat const &) const;
    
    template <std::size_t size2>
    friend std::ostream & operator<<(std::ostream &, nat<size2> const &);
    
  };
  
}

#include <two-adic/nat.inc>

#endif
