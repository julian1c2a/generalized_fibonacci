#include "include/gfib.hpp"
#include <iostream>

int main() {
  using namespace gfib;
  constexpr std::array<std::int64_t, 1> coeffs_order_0{2};
  constexpr std::array<std::int64_t, 0> initvals_order_0{};
  constexpr std::array<std::int64_t, 2> coeffs_order_1{3, -1};
  constexpr std::array<std::int64_t, 1> initvals_order_1{1};
  constexpr std::array<std::int64_t, 3> coeffs_order_2{1, 1, 0};
  constexpr std::array<std::int64_t, 2> initvals_order_2{1, 1};

  // Orden 0: función constante f(n) = coef_0
  std::cout << "f(5) con orden 0 (constante): \n"
            << compute_sequence<0, std::int64_t, std::uint16_t, coeffs_order_0,
                                initvals_order_0>(0)
            << "\n"
            << compute_sequence<0, std::int64_t, std::uint16_t, coeffs_order_0,
                                initvals_order_0>(1)
            << "\n"
            << compute_sequence<0, std::int64_t, std::uint16_t, coeffs_order_0,
                                initvals_order_0>(2)
            << "\n"
            << compute_sequence<0, std::int64_t, std::uint16_t, coeffs_order_0,
                                initvals_order_0>(3)
            << "\n";
  // Orden 1: función f(n) = coef_1*f(n-1)+coef_0
  std::cout << "f(5) con orden 1 (depende de f(n-1) de forma afín): \n"
            << compute_sequence<1, std::int64_t, std::uint16_t, coeffs_order_1,
                                initvals_order_1>(0)
            << "\n" // 1
            << compute_sequence<1, std::int64_t, std::uint16_t, coeffs_order_1,
                                initvals_order_1>(1)
            << "\n" // 3*1-1 = 2
            << compute_sequence<1, std::int64_t, std::uint16_t, coeffs_order_1,
                                initvals_order_1>(2)
            << "\n" // 3*2-1 = 5
            << compute_sequence<1, std::int64_t, std::uint16_t, coeffs_order_1,
                                initvals_order_1>(3)
            << "\n"; // 3*5-1 = 14
  // Orden 2: función f(n) = coef_2*f(n-2)+coef_1*f(n-1)+coef_0
  //                       = 1*f(n-1)+1*f(n-2)+0
  std::cout << "f(5) con orden 2 (depende de f(n-1) y de f(n-2) fibonacci): \n"
            << compute_sequence<2, std::int64_t, std::uint16_t, coeffs_order_2,
                                initvals_order_2>(0)
            << "\n" // 1
            << compute_sequence<2, std::int64_t, std::uint16_t, coeffs_order_2,
                                initvals_order_2>(1)
            << "\n" // 1
            << compute_sequence<2, std::int64_t, std::uint16_t, coeffs_order_2,
                                initvals_order_2>(2)
            << "\n" // 1 + 1 = 2
            << compute_sequence<2, std::int64_t, std::uint16_t, coeffs_order_2,
                                initvals_order_2>(3)
            << "\n"; // 2 + 1 = 3

  return 0;
}
