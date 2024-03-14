
#include <iostream>

#include <two-adic/two-adic.hpp>

template <typename T, typename P>
bool assert_equal(T const & result, T const & expected, P const & print_expr) {
  if (result == expected)
    return true;
  else {
    std::cout << " x ";
    print_expr(std::cout);
    std::cout << " = " << result
	      << " (expected " << expected << ")\n";
    return false;
  }
}

void test_nat_addition() {
  std::cout << "test_nat_addition" << std::endl;
  bool ok = true;
  for (std::uint32_t i = 0; i <= 300; ++i) {
    for (std::uint32_t j = 0; j <= 300; ++j) {
      two_adic::nat<8> lhs { i };
      two_adic::nat<8> rhs { j };
      two_adic::nat<8> result { lhs + rhs };
      two_adic::nat<8> expected { i + j };
      ok = assert_equal(result, expected, [i, j](std::ostream & out) {
	out << i << " + " << j;
      }) && ok;
    }
  }
  if (ok)
    std::cout << " OK\n";
}

void test_nat_multiplication() {
  std::cout << "test_nat_multiplication" << std::endl;
  bool ok = true;
  for (std::uint32_t i = 0; i <= 300; ++i) {
    for (std::uint32_t j = 0; j <= 300; ++j) {
      two_adic::nat<8> lhs { i };
      two_adic::nat<8> rhs { j };
      two_adic::nat<8> result { lhs * rhs };
      two_adic::nat<8> expected { i * j };
      ok = assert_equal(result, expected, [i, j](std::ostream & out) {
	out << i << " * " << j;
      }) && ok;
    }
  }
  if (ok)
    std::cout << " OK\n";
}

void test_nat_left_bit_shift() {
  std::cout << "test_nat_left_bit_shift" << std::endl;
  bool ok = true;
  for (std::uint32_t i = 0; i <= 300; ++i) {
    for (std::size_t j = 0; j <= 16; ++j) {
      two_adic::nat<8> lhs { i };
      two_adic::nat<8> result { lhs << j };
      two_adic::nat<8> expected { i << j };
      ok = assert_equal(result, expected, [i, j](std::ostream & out) {
	out << i << " << " << j;
      }) && ok;
    }
  }
  if (ok)
    std::cout << " OK\n";
}

void test_nat_right_bit_shift() {
  std::cout << "test_nat_right_bit_shift" << std::endl;
  bool ok = true;
  for (std::uint32_t i = 0; i <= 300; ++i) {
    for (std::size_t j = 0; j <= 16; ++j) {
      two_adic::nat<8> lhs { i };
      two_adic::nat<8> result { lhs >> j };
      two_adic::nat<8> expected { i >> j };
      ok = assert_equal(result, expected, [i, j](std::ostream & out) {
	out << i << " >> " << j;
      }) && ok;
    }
  }
  if (ok)
    std::cout << " OK\n";
}

void test_nat_is_zero() {
  std::cout << "test_nat_is_zero" << std::endl;
  bool ok = true;
  for (std::uint32_t i = 0; i <= 300; ++i) {
    two_adic::nat<8> operand { i };
    bool result = operand.is_zero();
    bool expected = i == 0;
    ok = assert_equal(result, expected, [i](std::ostream & out) {
      out << i << ".is_zero()";
    }) && ok;
  }
  if (ok)
    std::cout << " OK\n";
}

void test_nat_equal() {
  std::cout << "test_nat_equal" << std::endl;
  bool ok = true;
  for (std::uint32_t i = 0; i <= 300; ++i) {
    for (std::uint32_t j = 0; j <= 300; ++j) {
      two_adic::nat<8> lhs { i };
      two_adic::nat<8> rhs { j };
      bool result = lhs == rhs;
      bool expected = i == j;
      ok = assert_equal(result, expected, [i, j](std::ostream & out) {
	out << i << " == " << j;
      }) && ok;
    }
  }
  if (ok)
    std::cout << " OK\n";
}

void test_nat_bit_flip() {
  std::cout << "test_nat_bif_flip" << std::endl;
  bool ok = true;
  for (std::uint32_t i = 0; i <= 300; ++i) {
    two_adic::nat<4> operand { i };
    two_adic::nat<4> result { ~operand };
    two_adic::nat<4> expected { ~i };
    ok = assert_equal(result, expected, [i](std::ostream & out) {
      out << "~" << i;
    }) && ok;
  }
  if (ok)
    std::cout << " OK\n";
}

std::size_t expected_valuation(std::uint32_t i) {
  std::size_t val = 0;
  while (i != 0 && ((i & 1) == 0)) {
    ++val;
    i >>= 1;
  }
  return val;
}

void test_nat_valuation() {
  std::cout << "test_nat_valuation" << std::endl;
  bool ok = true;
  for (std::uint32_t i = 1; i <= 300; ++i) {
    two_adic::nat<8> operand { i };
    std::size_t result = operand.valuation();
    std::size_t expected = expected_valuation(i);
    ok = assert_equal(result, expected, [i](std::ostream & out) {
      out << i << ".valuation()";
    }) && ok;
  }
  if (ok)
    std::cout << " OK\n";
}

int main() {
  test_nat_addition();
  test_nat_multiplication();
  test_nat_left_bit_shift();
  test_nat_right_bit_shift();
  test_nat_is_zero();
  test_nat_equal();
  test_nat_bit_flip();
  test_nat_valuation();
  std::cout << std::flush;
}
