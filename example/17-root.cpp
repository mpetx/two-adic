
#include <iostream>

#include <two-adic/two-adic.hpp>

int main() {
  using n = two_adic::two_adic<2000>;
  n root { 7 };
  n prev { 0 };
  while (n::distance(root, prev) != 0) {
    prev = root;
    root = (root + root.inverse() * 17) >> 1;
  }
  std::cout << "sqrt(17) = " << root << std::endl;
  std::cout << "sqrt(17)^2 = " << root * root << std::endl;
}
