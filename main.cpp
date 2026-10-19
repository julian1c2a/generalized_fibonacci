#include "include/gfib.hpp"
#include <iostream>

constexpr std::array<std::int64_t, 1> coeffs_order_0{2};
constexpr std::array<std::int64_t, 0> initvals_order_0{};
constexpr std::array<std::int64_t, 2> coeffs_order_1{3, -1};
constexpr std::array<std::int64_t, 1> initvals_order_1{1};
constexpr std::array<std::int64_t, 3> coeffs_order_2{1, 1, 0};
constexpr std::array<std::int64_t, 2> initvals_order_2{1, 1};
constexpr std::array<std::int64_t, 4> coeffs_order_3{0, 1, 1, 0};
constexpr std::array<std::int64_t, 3> initvals_order_3{1, 1, 1};
constexpr std::array<std::int64_t, 5> coeffs_order_4{1, 2, 1, -1, -1};
constexpr std::array<std::int64_t, 4> initvals_order_4{1, 1, 1, 1};

// Define un generador para cualquier orden:
template <auto coeffs, auto initvals>
constexpr auto make_fib =
    [](auto n) { return gfib::compute_sequence<coeffs, initvals>(n); };

// Creas la función específica para la secuencia que quieras:
constexpr auto fib_0 = make_fib<coeffs_order_0, initvals_order_0>;
constexpr auto fib_1 = make_fib<coeffs_order_1, initvals_order_1>;
constexpr auto fib_2 = make_fib<coeffs_order_2, initvals_order_2>;
constexpr auto fib_3 = make_fib<coeffs_order_3, initvals_order_3>;
constexpr auto fib_4 = make_fib<coeffs_order_4, initvals_order_4>;

void show_fib(auto func, std::size_t n) {
  std::cout << "\n (";
  for (std::size_t i = 0; i <= n; ++i) {
    std::cout << func(i);
    if (i != n)
      std::cout << ", ";
  }
  std::cout << ")\n";
}

int main() {
  using namespace gfib;

  show_fib(fib_0, 10);
  show_fib(fib_1, 10);
  show_fib(fib_2, 10);
  show_fib(fib_3, 10);
  show_fib(fib_4, 10);

  // Creas la instancia del generador:
  gfib::MemoizedSequence<coeffs_order_0, initvals_order_0> memo_0;
  gfib::MemoizedSequence<coeffs_order_1, initvals_order_1> memo_1;
  gfib::MemoizedSequence<coeffs_order_2, initvals_order_2> memo_2;
  gfib::MemoizedSequence<coeffs_order_3, initvals_order_3> memo_3;
  gfib::MemoizedSequence<coeffs_order_4, initvals_order_4> memo_4;

  return 0;
}
