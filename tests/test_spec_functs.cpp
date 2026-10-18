#include "../include/spec_functs.hpp"
#include <cassert>
#include <complex>
#include <iostream>

namespace test_compile_time {
  using namespace spec_functs;

  static_assert(constants::pi > 3.14159 && constants::pi < 3.14160);
  static_assert(int_pow(2, 10) == 1024);
  static_assert(int_pow(3, 4) == 81);
  static_assert(exp_real(0.0) == 1.0);
  static_assert(log_real(1.0) == 0.0);
}

int main() {
  using namespace spec_functs;
  std::cout << "--- Ejecutando tests de spec_functs.hpp ---\n";

  // 1. Exponencial natural (exp) y compleja
  {
    assert(abs_val(exp(0.0) - 1.0) < 1e-15);
    assert(abs_val(exp(1.0) - constants::e) < 1e-14);
    assert(abs_val(exp(-1.0) - (1.0 / constants::e)) < 1e-14);
    assert(abs_val(exp(2.5) - 12.182493960703473) < 1e-13);
    assert(abs_val(exp(-5.0) - 0.006737946999085467) < 1e-14);

    // Identidad de Euler: e^(i * pi) = -1 => e^(i * pi) + 1 == 0
    std::complex<double> i_pi(0.0, constants::pi);
    auto e_ipi = exp(i_pi);
    assert(abs_val(e_ipi.real() - (-1.0)) < 1e-14);
    assert(abs_val(e_ipi.imag()) < 1e-14);

    std::cout << "[OK] Exponencial natural y compleja (identidad de Euler e^(i*pi) = -1) verificada.\n";
  }

  // 2. Logaritmo natural (log)
  {
    assert(abs_val(log(1.0)) < 1e-15);
    assert(abs_val(log(constants::e) - 1.0) < 1e-14);
    assert(abs_val(log(2.0) - constants::ln2) < 1e-14);
    assert(abs_val(log(10.0) - constants::ln10) < 1e-14);

    // Identidad inversa: log(exp(x)) == x
    for (double x : {-3.2, -1.0, 0.0, 0.5, 2.7, 5.1}) {
      assert(abs_val(log(exp(x)) - x) < 1e-12);
    }

    std::cout << "[OK] Logaritmo natural y comprobacion de identidad inversa log(exp(x)) == x verificada.\n";
  }

  // 3. Potencias y Exponenciales en base arbitraria
  {
    assert(abs_val(pow(2.0, 10.0) - 1024.0) < 1e-12);
    assert(abs_val(pow(10.0, 3.0) - 1000.0) < 1e-12);
    assert(abs_val(pow(4.0, 0.5) - 2.0) < 1e-14);
    assert(abs_val(exp_base(3.0, 4.0) - 81.0) < 1e-12);

    std::cout << "[OK] Potencias y exponenciales de base arbitraria verificadas.\n";
  }

  // 4. Logaritmos en bases arbitrarias (log_base, log10, log2)
  {
    assert(abs_val(log10(1000.0) - 3.0) < 1e-14);
    assert(abs_val(log2(1024.0) - 10.0) < 1e-14);
    assert(abs_val(log_base(3.0, 81.0) - 4.0) < 1e-13);
    assert(abs_val(log_base(2.0, 0.125) - (-3.0)) < 1e-14);

    std::cout << "[OK] Logaritmos en bases 10, 2 y base arbitraria verificados.\n";
  }

  // 5. Función Gamma de Euler (gamma) y Log-Gamma (lgamma)
  {
    // Factoriales enteros: Gamma(n) = (n - 1)!
    assert(abs_val(gamma(1.0) - 1.0) < 1e-14);
    assert(abs_val(gamma(2.0) - 1.0) < 1e-14);
    assert(abs_val(gamma(3.0) - 2.0) < 1e-14);
    assert(abs_val(gamma(4.0) - 6.0) < 1e-13);
    assert(abs_val(gamma(5.0) - 24.0) < 1e-12);
    assert(abs_val(gamma(6.0) - 120.0) < 1e-11);

    // Semienteros: Gamma(1/2) = sqrt(pi)
    double sqrt_pi = 1.772453850905516027;
    assert(abs_val(gamma(0.5) - sqrt_pi) < 1e-11);

    // Gamma(3/2) = 0.5 * sqrt(pi)
    assert(abs_val(gamma(1.5) - (0.5 * sqrt_pi)) < 1e-11);

    // Argumento negativo por fórmula de reflexión: Gamma(-1/2) = -2 * sqrt(pi)
    assert(abs_val(gamma(-0.5) - (-2.0 * sqrt_pi)) < 1e-11);

    // lgamma
    assert(abs_val(lgamma(5.0) - log(24.0)) < 1e-12);

    std::cout << "[OK] Funcion Gamma de Euler (factoriales, semienteros y reflexion negativa) verificada.\n";
  }

  // 6. Función Beta de Euler (beta y lbeta)
  {
    // B(1, 1) = 1
    assert(abs_val(beta(1.0, 1.0) - 1.0) < 1e-14);

    // B(2, 3) = Gamma(2)*Gamma(3)/Gamma(5) = 1*2/24 = 1/12
    assert(abs_val(beta(2.0, 3.0) - (1.0 / 12.0)) < 1e-14);

    // Simetría: B(x, y) == B(y, x)
    assert(abs_val(beta(2.5, 4.2) - beta(4.2, 2.5)) < 1e-14);

    // B(1/2, 1/2) = Gamma(1/2)^2 / Gamma(1) = pi
    assert(abs_val(beta(0.5, 0.5) - constants::pi) < 1e-11);

    // lbeta
    assert(abs_val(exp(lbeta(2.0, 3.0)) - (1.0 / 12.0)) < 1e-14);

    std::cout << "[OK] Funcion Beta de Euler (valores exactos, simetria y lbeta) verificada.\n";
  }

  std::cout << "\n¡Todos los tests de spec_functs pasaron exitosamente!\n";
  return 0;
}
