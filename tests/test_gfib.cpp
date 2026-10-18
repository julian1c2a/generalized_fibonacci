#include "../include/gfib.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>

// Comprobaciones estáticas en tiempo de compilación (constexpr)
namespace test_constexpr {
  using namespace gfib;

  // Orden 0: Constante f(n) = 5
  constexpr std::array<int64_t, 1> c0{5};
  constexpr std::array<int64_t, 0> init0{};
  static_assert(compute_sequence<c0, init0>(0u) == 5);
  static_assert(compute_sequence<c0, init0>(10u) == 5);

  // Orden 2: Fibonacci estándar: x_n = 1*x_{n-1} + 1*x_{n-2} + 0
  // init = {0, 1} -> 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55...
  constexpr std::array<int64_t, 3> c_fib{1, 1, 0};
  constexpr std::array<int64_t, 2> init_fib{0, 1};

  // Valores iniciales directos
  static_assert(compute_sequence<c_fib, init_fib>(0u) == 0);
  static_assert(compute_sequence<c_fib, init_fib>(1u) == 1);

  // Precomputación estática con std::array (100% constexpr)
  constexpr auto table_fib = precompute_sequence_array<c_fib, init_fib, 11>();
  static_assert(table_fib[0] == 0);
  static_assert(table_fib[1] == 1);
  static_assert(table_fib[2] == 1);
  static_assert(table_fib[3] == 2);
  static_assert(table_fib[4] == 3);
  static_assert(table_fib[5] == 5);
  static_assert(table_fib[6] == 8);
  static_assert(table_fib[7] == 13);
  static_assert(table_fib[8] == 21);
  static_assert(table_fib[9] == 34);
  static_assert(table_fib[10] == 55);
}

int main() {
  using namespace gfib;
  std::cout << "--- Ejecutando tests de gfib.hpp ---\n";

  // 1. Verificación de secuencias de Orden 0, 1, 2, 3 y 4 (directo vs memoizado)
  {
    constexpr std::array<int64_t, 1> c0{2};
    constexpr std::array<int64_t, 0> i0{};
    MemoizedSequence<c0, i0> memo0;
    for (std::size_t n = 0; n <= 25; ++n) {
      assert((compute_sequence<c0, i0>(n) == 2));
      assert((memo0(n) == 2));
    }
    std::cout << "[OK] Orden 0 (secuencia constante) verificado.\n";

    // Orden 1: x_n = 3 * x_{n-1} - 1, x_0 = 1
    // n=0: 1
    // n=1: 3(1) - 1 = 2
    // n=2: 3(2) - 1 = 5
    // n=3: 3(5) - 1 = 14
    constexpr std::array<int64_t, 2> c1{3, -1};
    constexpr std::array<int64_t, 1> i1{1};
    MemoizedSequence<c1, i1> memo1;
    assert((compute_sequence<c1, i1>(0u) == 1));
    assert((compute_sequence<c1, i1>(1u) == 2));
    assert((compute_sequence<c1, i1>(2u) == 5));
    assert((compute_sequence<c1, i1>(3u) == 14));

    for (std::size_t n = 0; n <= 20; ++n) {
      assert((memo1(n) == compute_sequence<c1, i1>(n)));
    }
    std::cout << "[OK] Orden 1 verificado.\n";

    // Orden 2: Fibonacci clásico
    constexpr std::array<int64_t, 3> c2{1, 1, 0};
    constexpr std::array<int64_t, 2> i2{0, 1};
    MemoizedSequence<c2, i2> memo2;

    // Probar tanto dentro del rango precomputado como en la caché dinámica
    constexpr std::size_t precomputed_limit = MemoizedSequence<c2, i2>::PRECOMPUTED_SIZE;
    std::size_t test_max = precomputed_limit + 30;

    for (std::size_t n = 0; n <= test_max; ++n) {
      int64_t expected = compute_sequence<c2, i2>(n);
      assert((memo2(n) == expected));
    }
    std::cout << "[OK] Orden 2 (Fibonacci estándar, cache estática + dinámica) verificado.\n";

    // Orden 3: Tribonacci x_n = x_{n-1} + x_{n-2} + x_{n-3}, x_0=0, x_1=1, x_2=1
    // 0, 1, 1, 2, 4, 7, 13, 24, 44...
    constexpr std::array<int64_t, 4> c3{1, 1, 1, 0};
    constexpr std::array<int64_t, 3> i3{0, 1, 1};
    MemoizedSequence<c3, i3> memo3;
    assert((memo3(0) == 0));
    assert((memo3(1) == 1));
    assert((memo3(2) == 1));
    assert((memo3(3) == 2));
    assert((memo3(4) == 4));
    assert((memo3(5) == 7));
    assert((memo3(6) == 13));
    assert((memo3(7) == 24));
    assert((memo3(8) == 44));
    std::cout << "[OK] Orden 3 (Tribonacci) verificado.\n";
  }

  // 2. Verificación del método get_list y comportamiento de la caché
  {
    constexpr std::array<int64_t, 3> c2{1, 1, 0};
    constexpr std::array<int64_t, 2> i2{1, 1}; // 1, 1, 2, 3, 5, 8, 13, 21
    MemoizedSequence<c2, i2> memo;

    auto list_empty = memo.get_list(0);
    assert(list_empty.empty());

    auto list8 = memo.get_list(8);
    assert((list8.size() == 8));
    std::vector<int64_t> expected8 = {1, 1, 2, 3, 5, 8, 13, 21};
    assert((list8 == expected8));

    // Consulta fuera de orden / salto grande para forzar expansión de dynamic_cache_
    auto val40 = memo(40);
    assert((val40 == compute_sequence<c2, i2>(40u)));
    assert((memo.total_cached() >= 41));

    std::cout << "[OK] get_list y comportamiento de expansión de caché verificados.\n";
  }

  std::cout << "\n¡Todos los tests de gfib pasaron exitosamente!\n";
  return 0;
}
