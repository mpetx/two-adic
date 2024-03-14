
#include <iostream>

#include <two-adic/two-adic.hpp>

template <typename T, typename P>
bool assert_near(T const & result, T const & expected, double d, P const & print_expr) {
  if (T::distance(result, expected) <= d)
    return true;
  else {
    std::cout << " x ";
    print_expr(std::cout);
    std::cout << " = " << result
	      << " (expected " << expected << ")\n";
    return false;
  }
}

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

void test_two_adic_addition() {
  std::cout << "test_two_adic_addition" << std::endl;
  bool ok = true;
  for (int i = -150; i <= 150; ++i) {
    for (int j = -150; j <= 150; ++j) {
      two_adic::two_adic<64> lhs { i };
      two_adic::two_adic<64> rhs { j };
      two_adic::two_adic<64> result { lhs + rhs };
      two_adic::two_adic<64> expected { i + j };
      ok = assert_near(result, expected, 0.0001, [i, j](std::ostream & out) {
	out << i << " + " << j;
      }) && ok;
    }
  }
  if (ok)
    std::cout << " OK\n";
}

void test_two_adic_negation() {
  std::cout << "test_two_adic_negation" << std::endl;
  bool ok = true;
  for (int i = -150; i <= 150; ++i) {
      two_adic::two_adic<64> operand { i };
      two_adic::two_adic<64> result { -operand + operand };
      two_adic::two_adic<64> expected { 0 };
      ok = assert_near(result, expected, 0.0001, [i](std::ostream & out) {
	out << "-" << i << " + " << i;
      }) && ok;
  }
  if (ok)
    std::cout << " OK\n";
}

void test_two_adic_multiplication() {
  std::cout << "test_two_adic_multiplication" << std::endl;
  bool ok = true;
  for (int i = -150; i <= 150; ++i) {
    for (int j = -150; j <= 150; ++j) {
      two_adic::two_adic<64> lhs { i };
      two_adic::two_adic<64> rhs { j };
      two_adic::two_adic<64> result { lhs * rhs };
      two_adic::two_adic<64> expected { i * j };
      ok = assert_near(result, expected, 0.0001, [i, j](std::ostream & out) {
	out << i << " * " << j;
      }) && ok;
    }
  }
  if (ok)
    std::cout << " OK\n";
}

void test_two_adic_inverse() {
  std::cout << "test_two_adic_inverse" << std::endl;
  bool ok = true;
  for (int i = -150; i <= 150; ++i) {
    if (i == 0)
      continue;
    two_adic::two_adic<64> operand { i };
    two_adic::two_adic<64> result { operand.inverse() * operand };
    two_adic::two_adic<64> expected { 1 };
    ok = assert_near(result, expected, 0.0001, [i](std::ostream & out) {
      out << i << ".inverse() * " << i;
    }) && ok;
  }
  if (ok)
    std::cout << " OK\n";
}

int main() {
  test_two_adic_addition();
  test_two_adic_negation();
  test_two_adic_multiplication();
  test_two_adic_inverse();
  std::cout << std::flush;
}
