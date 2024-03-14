#ifndef TWO_ADIC_NAT_INC_2024_03_13_F6EF6AFC_64D7_4DCE_ABA9_E7D51A18AD11
#define TWO_ADIC_NAT_INC_2024_03_13_F6EF6AFC_64D7_4DCE_ABA9_E7D51A18AD11

#include <limits>

namespace two_adic {

  template <std::size_t size>
  nat<size>::nat()
    : buffer { 0 } {
  }

  template <std::size_t size>
  nat<size>::~nat() {
  }

  template <std::size_t size>
  template <typename U>
  nat<size>::nat(U value)
    : nat { } {
    static_assert(std::numeric_limits<U>::is_integer && !std::numeric_limits<U>::is_signed, "U must be an unsigned integer type.");
    std::size_t i = 0;
    while (value != 0 && i < size) {
      buffer[i] = value & 0xff;
      value >>= 8;
      ++i;
    }
  }

  template <std::size_t size>
  nat<size> nat<size>::operator+(nat const & n) const {
    nat result;
    std::uint8_t carry = 0;
    for (std::size_t i = 0; i < size; ++i) {
      int sum = 0 + buffer[i] + n.buffer[i] + carry;
      result.buffer[i] = static_cast<std::uint8_t>(sum & 0xff);
      carry = static_cast<std::uint8_t>(sum >> 8);
    }
    return result;
  }

  template <std::size_t size>
  nat<size> nat<size>::operator*(nat const & n) const {
    nat result;
    nat lhs { *this };
    nat rhs { n };
    while (!rhs.is_zero()) {
      if ((rhs.buffer[0] & 1) != 0) {
	result = result + lhs;
      }
      rhs = rhs >> 1;
      lhs = lhs << 1;
    }
    return result;
  }

  template <std::size_t size>
  std::uint8_t nat<size>::get_byte_at(std::size_t n) const {
    std::size_t big_n = n / 8;
    std::size_t small_n = n % 8;
    std::uint8_t lower_byte = big_n < size ? buffer[big_n] : 0;
    std::uint8_t upper_byte = big_n + 1 < size ? buffer[big_n + 1] : 0;
    return (upper_byte << (8 - small_n)) | (lower_byte >> small_n);
  }

  template <std::size_t size>
  std::uint8_t nat<size>::get_byte_at_n(std::size_t n) const {
    if (n < 8)
      return buffer[0] << n;
    else
      return 0;
  }

  template <std::size_t size>
  nat<size> nat<size>::operator>>(std::size_t offset) const {
    nat result { *this };
    for (std::size_t i = 0; i < size; ++i) {
      result.buffer[i] = get_byte_at(8 * i + offset);
    }
    return result;
  }

  template <std::size_t size>
  nat<size> nat<size>::operator<<(std::size_t shift) const {
    nat result { *this };
    for (std::size_t i = size; i > 0; --i) {
      if (8 * (i - 1) >= shift)
	result.buffer[i - 1] = get_byte_at(8 * (i - 1) - shift);
      else
	result.buffer[i - 1] = get_byte_at_n(shift - 8 * (i - 1));
    }
    return result;
  }

  template <std::size_t size>
  bool nat<size>::is_zero() const {
    for (std::size_t i = 0; i < size; ++i) {
      if (buffer[i] != 0)
	return false;
    }
    return true;
  }

  template <std::size_t size>
  std::size_t nat<size>::valuation() const {
    std::size_t result = 0;
    for (std::size_t i = 0; i < size; ++i) {
      std::uint8_t byte = buffer[i];
      if (byte == 0) {
	result += 8;
      } else {
	while ((byte & 1) == 0) {
	  ++result;
	  byte >>= 1;
	}
	break;
      }
    }
    return result;
  }

  template <std::size_t size>
  bool nat<size>::operator==(nat const & n) const {
    for (std::size_t i = 0; i < size; ++i) {
      if (buffer[i] != n.buffer[i])
	return false;
    }
    return true;
  }

  inline void print_byte_with_fill(std::ostream & out, std::uint8_t byte) {
    for (std::uint8_t mask = 0b1000'0000; mask != 0; mask >>= 1) {
      if ((byte & mask) == 0)
	out << '0';
      else
	out << '1';
    }
  }

  inline void print_byte_without_fill(std::ostream & out, std::uint8_t byte) {
    bool head = true;
    for (std::uint8_t mask = 0b1000'0000; mask != 0; mask >>= 1) {
      if ((byte & mask) == 0) {
	if (!head)
	  out << '0';
      } else {
	head = false;
	out << '1';
      }
    }
  }
  
  template <std::size_t size>
  std::ostream & operator<<(std::ostream & out, nat<size> const & n) {
    std::size_t i = size;
    while (i > 0 && n.buffer[i - 1] == 0)
      --i;
    if (i == 0) {
      out << '0';
      return out;
    }
    print_byte_without_fill(out, n.buffer[i - 1]);
    --i;
    for (; i > 0; --i) {
      print_byte_with_fill(out, n.buffer[i - 1]);
    }
    return out;
  }

  template <std::size_t size>
  nat<size> nat<size>::operator~() const {
    nat result { *this };
    for (std::size_t i = 0; i < size; ++i) {
      result.buffer[i] = ~(result.buffer[i]);
    }
    return result;
  }
  
}

#endif
