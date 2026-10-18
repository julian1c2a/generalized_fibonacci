#include "../include/poly.hpp"
#include <cassert>
#include <iostream>

// Comprobaciones estáticas en tiempo de compilación (constexpr)
namespace test_constexpr {
  using namespace poly;

  // P(x) = 3 + 2x + x^2
  constexpr StaticPoly<int64_t, 2> p({3, 2, 1});

  // P(2) = 3 + 2*2 + 2^2 = 11
  static_assert(p.eval(2) == 11);
  static_assert(p(2) == 11);

  // Estrin P(2) = 11
  static_assert(p.eval_estrin(2) == 11);

  // Derivada P'(x) = 2 + 2x => P'(2) = 6
  constexpr auto p_and_dp = p.eval_with_derivative(2);
  static_assert(p_and_dp.first == 11);
  static_assert(p_and_dp.second == 6);

  // Derivada simbólica: P'(x)
  constexpr auto dp = p.derivative();
  static_assert(dp[0] == 2 && dp[1] == 2);
  static_assert(dp(2) == 6);

  // Multiplicación estática: (1 + x) * (1 + x) = 1 + 2x + x^2
  constexpr StaticPoly<int64_t, 1> lin({1, 1});
  constexpr auto sq = lin * lin;
  static_assert(sq[0] == 1 && sq[1] == 2 && sq[2] == 1);

  // Potencia estática: (1 + x)^3 = 1 + 3x + 3x^2 + x^3
  constexpr auto cube = lin.pow<3>();
  static_assert(cube[0] == 1 && cube[1] == 3 && cube[2] == 3 && cube[3] == 1);
}

int main() {
  using namespace poly;
  std::cout << "--- Ejecutando tests de poly.hpp ---\n";

  // 1. Test Horner, Estrin y Derivadas con DynamicPoly
  {
    // Q(x) = 5 - 4x + 3x^2 - 2x^3 + x^4
    DynamicPoly<double> q({5.0, -4.0, 3.0, -2.0, 1.0});
    double x = 2.5;

    double v_horner = q.eval(x);
    double v_estrin = q.eval_estrin(x);
    auto [val, dval] = q.eval_with_derivative(x);

    assert(std::abs(v_horner - v_estrin) < 1e-12);
    assert(std::abs(v_horner - val) < 1e-12);

    // Derivada formal: Q'(x) = -4 + 6x - 6x^2 + 4x^3
    auto dq = q.derivative();
    double dq_val = dq.eval(x);
    assert(std::abs(dval - dq_val) < 1e-12);

    // Derivadas sucesivas con Ruffini-Horner
    auto all_ders = q.eval_derivatives(x, 4);
    assert(std::abs(all_ders[0] - val) < 1e-12);
    assert(std::abs(all_ders[1] - dval) < 1e-12);

    std::cout << "[OK] Horner, Estrin y derivadas evaluados correctamente.\n";
  }

  // 2. Test de operaciones algebraicas (Suma, Producto, División, Resto)
  {
    // A(x) = 2x^3 + 4x^2 - 5x + 3 => {3, -5, 4, 2}
    // B(x) = x + 2                => {2, 1}
    DynamicPoly<int64_t> A({3, -5, 4, 2});
    DynamicPoly<int64_t> B({2, 1});

    auto Q = A / B;
    auto R = A % B;

    // Verificamos que A == Q * B + R
    auto reconstructed = (Q * B) + R;
    assert(reconstructed.size() == A.size());
    for (std::size_t i = 0; i < A.size(); ++i) {
      assert(reconstructed[i] == A[i]);
    }
    std::cout << "[OK] Division euclidea y modulo de polinomios verificados.\n";
  }

  // 3. Test de potenciación binaria de polinomios P(x)^k
  {
    DynamicPoly<int64_t> binom({2, 1}); // 2 + x
    auto p4 = binom.pow(4);             // (2 + x)^4 = 16 + 32x + 24x^2 + 8x^3 + x^4

    assert(p4.size() == 5);
    assert(p4[0] == 16);
    assert(p4[1] == 32);
    assert(p4[2] == 24);
    assert(p4[3] == 8);
    assert(p4[4] == 1);
    std::cout << "[OK] Exponenciacion binaria (P(x)^k) verificada.\n";
  }

  // 4. Test de potenciación modular y algoritmo de Fiduccia para Fibonacci
  {
    // Polinomio característico de Fibonacci: x^2 - x - 1 = 0
    // En orden ascendente: {-1, -1, 1}
    DynamicPoly<int64_t> char_poly({-1, -1, 1});

    // x en orden ascendente: {0, 1}
    DynamicPoly<int64_t> x_poly({0, 1});

    // x^n mod (x^2 - x - 1) = F_{n-1} + F_n * x (para base F_0 = 0, F_1 = 1)
    // Para n = 10: F_9 = 34, F_10 = 55
    auto rem = x_poly.pow_mod(10, char_poly);

    assert(rem[0] == 34); // F_9
    assert(rem[1] == 55); // F_10

    std::cout << "[OK] Potenciacion modular x^10 mod (x^2 - x - 1) = "
              << rem[0] << " + " << rem[1] << "*x (Fibonacci F_9=" << rem[0]
              << ", F_10=" << rem[1] << ").\n";
  }

  std::cout << "\n¡Todos los tests pasaron exitosamente!\n";
  return 0;
}
