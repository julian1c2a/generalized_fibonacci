#include "../include/spec_functs.hpp"
#include <cassert>
#include <complex>
#include <iostream>

namespace test_compile_time {
  using namespace spec_functs;

  static_assert(constants::pi > 3.14159 && constants::pi < 3.14160);
  static_assert(constants::inv_pi > 0.318309 && constants::inv_pi < 0.318310);
  static_assert(constants::sqrt3 > 1.732050 && constants::sqrt3 < 1.732051);
  static_assert(constants::phi > 1.618033 && constants::phi < 1.618034);
  static_assert(constants::sqrt_half_pi > 1.253314 && constants::sqrt_half_pi < 1.253315);
  static_assert(constants::ln_2 == constants::ln2);
  static_assert(constants::ln_10 == constants::ln10);
  static_assert(constants::log10_10 == 1.0L);
  static_assert(constants::log2_2 == 1.0L);
  static_assert(constants::log2_4 == 2.0L);
  static_assert(constants::log2_8 == 3.0L);
  static_assert(int_pow(2, 10) == 1024);
  static_assert(int_pow(3, 4) == 81);
  static_assert(exp_real(0.0) == 1.0);
  static_assert(log_real(1.0) == 0.0);
  static_assert(sqrt_real(0.0) == 0.0);
  static_assert(sqrt_real(4.0) == 2.0);
  static_assert(sqrt_real(9.0) == 3.0);
  static_assert(sin(0.0) == 0.0);
  static_assert(cos(0.0) == 1.0);
  static_assert(tan(0.0) == 0.0);
  static_assert(sinh(0.0) == 0.0);
  static_assert(cosh(0.0) == 1.0);
  static_assert(tanh(0.0) == 0.0);
  static_assert(asin(0.0) == 0.0);
  static_assert(acos(1.0) == 0.0);
  static_assert(atan(0.0) == 0.0);
  static_assert(asinh(0.0) == 0.0);
  static_assert(acosh(1.0) == 0.0);
  static_assert(atanh(0.0) == 0.0);
  static_assert(constants::euler_gamma > 0.577215 && constants::euler_gamma < 0.577216);
  static_assert(constants::egamma == constants::euler_gamma);
  static_assert(constants::euler_mascheroni == constants::euler_gamma);
  static_assert(ceil(3.2) == 4.0);
  static_assert(ceil(3.0) == 3.0);
  static_assert(ceil(-3.2) == -3.0);
  static_assert(floor(3.8) == 3.0);
  static_assert(floor(-3.2) == -4.0);
  static_assert(trunc(3.8) == 3.0);
  static_assert(trunc(-3.8) == -3.0);
  static_assert(round(3.2) == 3.0);
  static_assert(round(3.7) == 4.0);
  static_assert(round(-3.2) == -3.0);
  static_assert(round(-3.7) == -4.0);
  static_assert(ceil_int(3.2) == 4);
  static_assert(floor_int(3.8) == 3);
  static_assert(trunc_int(-3.8) == -3);
  static_assert(round_int(3.7) == 4);
  static_assert(frac(3.25) == 0.25);
  static_assert(frac_defect(3.25) == 0.25);
  static_assert(frac_excess(3.25) == 0.75);
  static_assert(frac_round(3.25) == 0.25);
  static_assert(frac_round(3.75) == -0.25);
  static_assert(frac_trunc(-3.75) == -0.75);
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

  // 2. Logaritmo natural (log) y complejo
  {
    assert(abs_val(log(1.0)) < 1e-15);
    assert(abs_val(log(constants::e) - 1.0) < 1e-14);
    assert(abs_val(log(2.0) - constants::ln2) < 1e-14);
    assert(abs_val(log(10.0) - constants::ln10) < 1e-14);

    // Identidad inversa: log(exp(x)) == x
    for (double x : {-3.2, -1.0, 0.0, 0.5, 2.7, 5.1}) {
      assert(abs_val(log(exp(x)) - x) < 1e-12);
    }

    // Logaritmo complejo: ln(-1) = i * pi
    std::complex<double> neg_one(-1.0, 0.0);
    auto ln_neg_one = log(neg_one);
    assert(abs_val(ln_neg_one.real()) < 1e-14);
    assert(abs_val(ln_neg_one.imag() - constants::pi) < 1e-14);

    std::cout << "[OK] Logaritmo natural y comprobacion de identidad inversa log(exp(x)) == x verificada.\n";
  }

  // 3. Raíz cuadrada (sqrt) real y compleja
  {
    assert(abs_val(sqrt(0.0)) < 1e-15);
    assert(abs_val(sqrt(4.0) - 2.0) < 1e-15);
    assert(abs_val(sqrt(9.0) - 3.0) < 1e-15);
    assert(abs_val(sqrt(2.0) - constants::sqrt2) < 1e-14);
    assert(abs_val(sqrt(0.5) - constants::inv_sqrt2) < 1e-14);
    assert(abs_val(sqrt(1e12) - 1e6) < 1e-6);

    // Complejo: sqrt(-1) = i
    std::complex<double> c_neg_one(-1.0, 0.0);
    auto sqrt_i = sqrt(c_neg_one);
    assert(abs_val(sqrt_i.real()) < 1e-14);
    assert(abs_val(sqrt_i.imag() - 1.0) < 1e-14);

    // Complejo: sqrt(i) = (1 + i) / sqrt(2)
    std::complex<double> c_i(0.0, 1.0);
    auto sqrt_c_i = sqrt(c_i);
    assert(abs_val(sqrt_c_i.real() - constants::inv_sqrt2) < 1e-14);
    assert(abs_val(sqrt_c_i.imag() - constants::inv_sqrt2) < 1e-14);

    std::cout << "[OK] Raiz cuadrada real y compleja (incluyendo sqrt(-1) = i y sqrt(i)) verificada.\n";
  }

  // 4. Potencias y Exponenciales en base arbitraria
  {
    assert(abs_val(pow(2.0, 10.0) - 1024.0) < 1e-12);
    assert(abs_val(pow(10.0, 3.0) - 1000.0) < 1e-12);
    assert(abs_val(pow(4.0, 0.5) - 2.0) < 1e-14);
    assert(abs_val(exp_base(3.0, 4.0) - 81.0) < 1e-12);

    std::cout << "[OK] Potencias y exponenciales de base arbitraria verificadas.\n";
  }

  // 5. Logaritmos en bases arbitrarias (log_base, log10, log2)
  {
    assert(abs_val(log10(1000.0) - 3.0) < 1e-14);
    assert(abs_val(log2(1024.0) - 10.0) < 1e-14);
    assert(abs_val(log_base(3.0, 81.0) - 4.0) < 1e-13);
    assert(abs_val(log_base(2.0, 0.125) - (-3.0)) < 1e-14);

    std::cout << "[OK] Logaritmos en bases 10, 2 y base arbitraria verificados.\n";
  }

  // 6. Funciones Trigonométricas (sin, cos, tan, cot, cotan)
  {
    // Valores exactos y notables
    assert(abs_val(sin(0.0)) < 1e-15);
    assert(abs_val(cos(0.0) - 1.0) < 1e-15);
    assert(abs_val(tan(0.0)) < 1e-15);

    assert(abs_val(sin(constants::half_pi) - 1.0) < 1e-14);
    assert(abs_val(cos(constants::half_pi)) < 1e-14);
    assert(abs_val(cot(constants::half_pi)) < 1e-14);
    assert(abs_val(cotan(constants::half_pi)) < 1e-14);

    assert(abs_val(sin(constants::pi)) < 1e-14);
    assert(abs_val(cos(constants::pi) - (-1.0)) < 1e-14);

    assert(abs_val(sin(constants::pi / 6.0) - 0.5) < 1e-14);
    assert(abs_val(cos(constants::pi / 3.0) - 0.5) < 1e-14);

    assert(abs_val(sin(constants::pi / 4.0) - constants::inv_sqrt2) < 1e-14);
    assert(abs_val(cos(constants::pi / 4.0) - constants::inv_sqrt2) < 1e-14);
    assert(abs_val(tan(constants::pi / 4.0) - 1.0) < 1e-14);
    assert(abs_val(cot(constants::pi / 4.0) - 1.0) < 1e-14);
    assert(abs_val(cotan(constants::pi / 4.0) - 1.0) < 1e-14);

    // Identidad fundamental: sin^2(x) + cos^2(x) == 1
    for (double x : {-7.5, -2.1, 0.123, 1.45, 3.14, 10.0, 100.0}) {
      double s = sin(x);
      double c = cos(x);
      assert(abs_val((s * s + c * c) - 1.0) < 1e-14);
    }

    // Identidad tan(x) * cot(x) == 1
    for (double x : {0.3, 0.7, 1.1, 2.2, -0.9}) {
      assert(abs_val(tan(x) * cot(x) - 1.0) < 1e-14);
      assert(abs_val(tan(x) * cotan(x) - 1.0) < 1e-14);
    }

    // Trigonométricas complejas: sin(i * y) = i * sinh(y), cos(i * y) = cosh(y)
    double y = 1.25;
    std::complex<double> iy(0.0, y);
    auto sin_iy = sin(iy);
    auto cos_iy = cos(iy);
    assert(abs_val(sin_iy.real()) < 1e-14);
    assert(abs_val(sin_iy.imag() - sinh(y)) < 1e-14);
    assert(abs_val(cos_iy.real() - cosh(y)) < 1e-14);
    assert(abs_val(cos_iy.imag()) < 1e-14);

    std::cout << "[OK] Funciones trigonometricas (sin, cos, tan, cot, cotan) y relaciones complejas verificadas.\n";
  }

  // 7. Funciones Hiperbólicas (sinh, cosh, tanh, coth, cotanh)
  {
    assert(abs_val(sinh(0.0)) < 1e-15);
    assert(abs_val(cosh(0.0) - 1.0) < 1e-15);
    assert(abs_val(tanh(0.0)) < 1e-15);

    // Identidad fundamental: cosh^2(x) - sinh^2(x) == 1
    for (double x : {-3.5, -1.2, -0.05, 0.0, 0.05, 1.2, 3.5}) {
      double ch = cosh(x);
      double sh = sinh(x);
      assert(abs_val((ch * ch - sh * sh) - 1.0) < 1e-12);
    }

    // Identidad tanh(x) * coth(x) == 1
    for (double x : {-2.5, -0.8, 0.4, 1.7, 3.0}) {
      assert(abs_val(tanh(x) * coth(x) - 1.0) < 1e-14);
      assert(abs_val(tanh(x) * cotanh(x) - 1.0) < 1e-14);
    }

    // Hiperbólicas complejas: sinh(i * x) = i * sin(x), cosh(i * x) = cos(x)
    double theta = 0.85;
    std::complex<double> itheta(0.0, theta);
    auto sinh_itheta = sinh(itheta);
    auto cosh_itheta = cosh(itheta);
    assert(abs_val(sinh_itheta.real()) < 1e-14);
    assert(abs_val(sinh_itheta.imag() - sin(theta)) < 1e-14);
    assert(abs_val(cosh_itheta.real() - cos(theta)) < 1e-14);
    assert(abs_val(cosh_itheta.imag()) < 1e-14);

    std::cout << "[OK] Funciones hiperbolicas (sinh, cosh, tanh, coth, cotanh) y relaciones complejas verificadas.\n";
  }

  // 8. Inversas Trigonométricas (asin, arcsin, acos, arccos, atan, arctan, atan2, acot, arccot, arcotan)
  {
    // asin y arcsin
    assert(abs_val(asin(0.0)) < 1e-15);
    assert(abs_val(arcsin(0.0)) < 1e-15);
    assert(abs_val(asin(1.0) - constants::half_pi) < 1e-14);
    assert(abs_val(asin(-1.0) - (-constants::half_pi)) < 1e-14);
    assert(abs_val(asin(0.5) - (constants::pi / 6.0)) < 1e-14);
    assert(abs_val(arcsin(constants::inv_sqrt2) - (constants::pi / 4.0)) < 1e-14);

    // Inversa sin(asin(x)) == x
    for (double x : {-0.99, -0.7, -0.3, 0.0, 0.3, 0.7, 0.99}) {
      assert(abs_val(sin(asin(x)) - x) < 1e-14);
      assert(abs_val(sin(arcsin(x)) - x) < 1e-14);
    }

    // acos y arccos
    assert(abs_val(acos(1.0)) < 1e-15);
    assert(abs_val(arccos(1.0)) < 1e-15);
    assert(abs_val(acos(0.0) - constants::half_pi) < 1e-14);
    assert(abs_val(acos(-1.0) - constants::pi) < 1e-14);
    assert(abs_val(acos(0.5) - (constants::pi / 3.0)) < 1e-14);
    assert(abs_val(arccos(constants::inv_sqrt2) - (constants::pi / 4.0)) < 1e-14);

    // Inversa cos(acos(x)) == x
    for (double x : {-0.99, -0.7, -0.3, 0.0, 0.3, 0.7, 0.99}) {
      assert(abs_val(cos(acos(x)) - x) < 1e-14);
      assert(abs_val(cos(arccos(x)) - x) < 1e-14);
    }

    // atan, arctan y atan2
    assert(abs_val(atan(0.0)) < 1e-15);
    assert(abs_val(arctan(0.0)) < 1e-15);
    assert(abs_val(atan(1.0) - (constants::pi / 4.0)) < 1e-14);
    assert(abs_val(arctan(-1.0) - (-constants::pi / 4.0)) < 1e-14);

    for (double x : {-50.0, -2.5, -0.4, 0.0, 0.4, 2.5, 50.0}) {
      assert(abs_val(tan(atan(x)) - x) < 1e-13);
      assert(abs_val(tan(arctan(x)) - x) < 1e-13);
    }

    // atan2 en 4 cuadrantes
    assert(abs_val(atan2(0.0, 1.0)) < 1e-15);
    assert(abs_val(atan2(1.0, 1.0) - (constants::pi / 4.0)) < 1e-14);
    assert(abs_val(atan2(1.0, 0.0) - constants::half_pi) < 1e-14);
    assert(abs_val(atan2(1.0, -1.0) - (3.0 * constants::pi / 4.0)) < 1e-14);
    assert(abs_val(atan2(0.0, -1.0) - constants::pi) < 1e-14);
    assert(abs_val(atan2(-1.0, -1.0) - (-3.0 * constants::pi / 4.0)) < 1e-14);
    assert(abs_val(atan2(-1.0, 0.0) - (-constants::half_pi)) < 1e-14);
    assert(abs_val(atan2(-1.0, 1.0) - (-constants::pi / 4.0)) < 1e-14);

    // acot, arccot y arcotan
    assert(abs_val(acot(0.0) - constants::half_pi) < 1e-14);
    assert(abs_val(arccot(1.0) - (constants::pi / 4.0)) < 1e-14);
    assert(abs_val(arcotan(-1.0) - (3.0 * constants::pi / 4.0)) < 1e-14);

    for (double x : {-10.0, -1.5, 0.2, 1.5, 10.0}) {
      assert(abs_val(cot(acot(x)) - x) < 1e-13);
      assert(abs_val(cotan(arccot(x)) - x) < 1e-13);
      assert(abs_val(cot(arcotan(x)) - x) < 1e-13);
    }

    // Inversas complejas: asin(sin(z)) == z para z en región principal
    std::complex<double> z1(0.3, 0.4);
    auto asin_sin_z1 = asin(sin(z1));
    assert(abs_val(asin_sin_z1.real() - z1.real()) < 1e-13);
    assert(abs_val(asin_sin_z1.imag() - z1.imag()) < 1e-13);

    auto acos_cos_z1 = acos(cos(z1));
    assert(abs_val(acos_cos_z1.real() - z1.real()) < 1e-13);
    assert(abs_val(acos_cos_z1.imag() - z1.imag()) < 1e-13);

    auto atan_tan_z1 = atan(tan(z1));
    assert(abs_val(atan_tan_z1.real() - z1.real()) < 1e-13);
    assert(abs_val(atan_tan_z1.imag() - z1.imag()) < 1e-13);

    std::cout << "[OK] Inversas trigonometricas (asin, acos, atan, atan2, acot y aliases) reales y complejas verificadas.\n";
  }

  // 9. Inversas Hiperbólicas (asinh, arcsinh, acosh, arccosh, atanh, arctanh, acoth, arccoth, arcotanh)
  {
    // asinh y arcsinh
    assert(abs_val(asinh(0.0)) < 1e-15);
    assert(abs_val(arcsinh(0.0)) < 1e-15);

    for (double x : {-25.0, -3.2, -0.01, 0.0, 0.01, 3.2, 25.0}) {
      assert(abs_val(asinh(sinh(x)) - x) < 1e-12);
      assert(abs_val(arcsinh(sinh(x)) - x) < 1e-12);
    }

    // acosh y arccosh (para x >= 1)
    assert(abs_val(acosh(1.0)) < 1e-15);
    assert(abs_val(arccosh(1.0)) < 1e-15);

    for (double x : {0.0, 0.5, 1.2, 3.8, 12.0}) {
      assert(abs_val(acosh(cosh(x)) - x) < 1e-12);
      assert(abs_val(arccosh(cosh(x)) - x) < 1e-12);
    }

    // atanh y arctanh (para |x| < 1)
    assert(abs_val(atanh(0.0)) < 1e-15);
    assert(abs_val(arctanh(0.0)) < 1e-15);

    for (double x : {-0.95, -0.5, -0.01, 0.0, 0.01, 0.5, 0.95}) {
      assert(abs_val(atanh(tanh(x)) - x) < 1e-12);
      assert(abs_val(arctanh(tanh(x)) - x) < 1e-12);
    }

    // acoth, arccoth y arcotanh (para |x| > 1)
    for (double x : {-5.0, -1.8, -0.4, 0.4, 1.8, 5.0}) {
      double coth_x = coth(x);
      assert(abs_val(acoth(coth_x) - x) < 1e-12);
      assert(abs_val(arccoth(coth_x) - x) < 1e-12);
      assert(abs_val(arcotanh(coth_x) - x) < 1e-12);
    }

    // Inversas hiperbólicas complejas
    std::complex<double> z2(0.4, 0.2);
    auto asinh_sinh_z2 = asinh(sinh(z2));
    assert(abs_val(asinh_sinh_z2.real() - z2.real()) < 1e-13);
    assert(abs_val(asinh_sinh_z2.imag() - z2.imag()) < 1e-13);

    auto atanh_tanh_z2 = atanh(tanh(z2));
    assert(abs_val(atanh_tanh_z2.real() - z2.real()) < 1e-13);
    assert(abs_val(atanh_tanh_z2.imag() - z2.imag()) < 1e-13);

    std::cout << "[OK] Inversas hiperbolicas (asinh, acosh, atanh, acoth y aliases) reales y complejas verificadas.\n";
  }

  // 10. Función Gamma de Euler (gamma) y Log-Gamma (lgamma)
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

  // 11. Función Beta de Euler (beta y lbeta)
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

  // 12. Constantes matemáticas en alta precisión (50 dígitos) y constante de Euler
  {
    assert(abs_val(constants::euler_gamma - 0.57721566490153286060L) < 1e-15);
    assert(abs_val(constants::egamma - constants::euler_gamma) < 1e-18);
    assert(abs_val(constants::euler_mascheroni - constants::euler_gamma) < 1e-18);

    // Relaciones algebraicas exactas para todos los bits de long double
    assert(abs_val(constants::pi * constants::inv_pi - 1.0L) < 1e-18);
    assert(abs_val(constants::two_pi - 2.0L * constants::pi) < 1e-18);
    assert(abs_val(constants::half_pi - constants::pi / 2.0L) < 1e-18);
    assert(abs_val(constants::sqrt2 * constants::sqrt2 - 2.0L) < 1e-18);
    assert(abs_val(constants::inv_sqrt2 * constants::sqrt2 - 1.0L) < 1e-18);
    assert(abs_val(constants::sqrt_half_pi * constants::sqrt_half_pi - constants::half_pi) < 1e-18);
    assert(abs_val(constants::sqrt_half_pi * 2.0L - constants::sqrt_2pi) < 1e-18);
    assert(abs_val(constants::sqrt3 * constants::sqrt3 - 3.0L) < 1e-18);
    // Identidad del número áureo: phi^2 - phi - 1 == 0
    assert(abs_val(constants::phi * constants::phi - constants::phi - 1.0L) < 1e-18);

    // Relación con derivada de Gamma en 1: -Gamma'(1) == gamma_Euler
    // (Gamma(1 - h) - Gamma(1 + h)) / (2h) approx gamma_Euler para h = 1e-5
    double h = 1e-5;
    double approx_gamma = (gamma(1.0 - h) - gamma(1.0 + h)) / (2.0 * h);
    assert(abs_val(approx_gamma - constants::euler_gamma) < 1e-10);

    // Constantes Logarítmicas Naturales (ln_2 .. ln_10) y sus relaciones exactas
    assert(abs_val(constants::ln_4 - 2.0L * constants::ln_2) < 1e-18);
    assert(abs_val(constants::ln_6 - (constants::ln_2 + constants::ln_3)) < 1e-18);
    assert(abs_val(constants::ln_8 - 3.0L * constants::ln_2) < 1e-18);
    assert(abs_val(constants::ln_9 - 2.0L * constants::ln_3) < 1e-18);
    assert(abs_val(constants::ln_10 - (constants::ln_2 + constants::ln_5)) < 1e-18);
    assert(abs_val(constants::ln_2 * constants::inv_ln_2 - 1.0L) < 1e-18);
    assert(abs_val(constants::ln_10 * constants::inv_ln_10 - 1.0L) < 1e-18);

    // Constantes Logarítmicas Decimales Base 10 (log10_2 .. log10_20)
    assert(abs_val(constants::log10_2 - constants::ln_2 / constants::ln_10) < 1e-18);
    assert(abs_val(constants::log10_3 - constants::ln_3 / constants::ln_10) < 1e-18);
    assert(abs_val(constants::log10_4 - 2.0L * constants::log10_2) < 1e-18);
    assert(abs_val(constants::log10_6 - (constants::log10_2 + constants::log10_3)) < 1e-18);
    assert(abs_val(constants::log10_8 - 3.0L * constants::log10_2) < 1e-18);
    assert(abs_val(constants::log10_9 - 2.0L * constants::log10_3) < 1e-18);
    assert(constants::log10_10 == 1.0L);
    assert(abs_val(constants::log10_12 - (constants::log10_3 + 2.0L * constants::log10_2)) < 1e-18);
    assert(abs_val(constants::log10_15 - (constants::log10_3 + constants::log10_5)) < 1e-18);
    assert(abs_val(constants::log10_20 - (1.0L + constants::log10_2)) < 1e-18);

    // Constantes Logarítmicas Binarias Base 2 (log2_2 .. log2_10)
    assert(constants::log2_2 == 1.0L);
    assert(constants::log2_4 == 2.0L);
    assert(constants::log2_8 == 3.0L);
    assert(abs_val(constants::log2_3 - constants::ln_3 / constants::ln_2) < 1e-18);
    assert(abs_val(constants::log2_6 - (1.0L + constants::log2_3)) < 1e-18);
    assert(abs_val(constants::log2_9 - 2.0L * constants::log2_3) < 1e-18);
    assert(abs_val(constants::log2_10 - (1.0L + constants::log2_5)) < 1e-18);

    std::cout << "[OK] Constantes matematicas en alta precision (50 digitos, relaciones exactas) verificadas.\n";
  }

  // 13. Redondeos optimizados (ceil, floor, trunc, round) y parte fraccionaria (frac)
  {
    // ceil
    assert(ceil(3.0) == 3.0);
    assert(ceil(3.2) == 4.0);
    assert(ceil(3.8) == 4.0);
    assert(ceil(-3.0) == -3.0);
    assert(ceil(-3.2) == -3.0);
    assert(ceil(-3.8) == -3.0);
    assert(ceil(0.0) == 0.0);

    // floor
    assert(floor(3.0) == 3.0);
    assert(floor(3.2) == 3.0);
    assert(floor(3.8) == 3.0);
    assert(floor(-3.0) == -3.0);
    assert(floor(-3.2) == -4.0);
    assert(floor(-3.8) == -4.0);

    // trunc
    assert(trunc(3.8) == 3.0);
    assert(trunc(-3.8) == -3.0);
    assert(trunc(0.5) == 0.0);
    assert(trunc(-0.5) == 0.0);

    // round (simétrico, half away from zero)
    assert(round(3.2) == 3.0);
    assert(round(3.7) == 4.0);
    assert(round(3.5) == 4.0);
    assert(round(-3.2) == -3.0);
    assert(round(-3.7) == -4.0);
    assert(round(-3.5) == -4.0);

    // Versiones enteras
    assert(ceil_int(4.1) == 5);
    assert(floor_int(4.9) == 4);
    assert(trunc_int(-4.9) == -4);
    assert(round_int(4.5) == 5);
    assert(round_int(-4.5) == -5);

    // Números grandes (>= 2^52 en double, camino rápido O(1))
    double big_val = 4503599627370496.0; // 2^52
    assert(ceil(big_val) == big_val);
    assert(floor(big_val) == big_val);
    assert(trunc(big_val) == big_val);
    assert(round(big_val) == big_val);
    assert(frac(big_val) == 0.0);

    // Complejos
    std::complex<double> z(3.2, -4.7);
    auto c_ceil = ceil(z);
    assert(c_ceil.real() == 4.0 && c_ceil.imag() == -4.0);
    auto c_floor = floor(z);
    assert(c_floor.real() == 3.0 && c_floor.imag() == -5.0);
    auto c_round = round(z);
    assert(c_round.real() == 3.0 && c_round.imag() == -5.0);
    auto c_frac = frac(z);
    assert(abs_val(c_frac.real() - 0.2) < 1e-14);
    assert(abs_val(c_frac.imag() - 0.3) < 1e-14);

    // frac: defecto, exceso, redondeo y truncamiento
    assert(abs_val(frac(3.25) - 0.25) < 1e-15);
    assert(abs_val(frac_defect(3.25) - 0.25) < 1e-15);
    assert(abs_val(frac_excess(3.25) - 0.75) < 1e-15);
    // Identidad para no enteros: defect + excess == 1.0
    assert(abs_val(frac_defect(3.25) + frac_excess(3.25) - 1.0) < 1e-15);
    assert(abs_val(frac_defect(7.82) + frac_excess(7.82) - 1.0) < 1e-14);

    // Para enteros exactos, ambos son 0
    assert(frac_defect(5.0) == 0.0);
    assert(frac_excess(5.0) == 0.0);

    // frac_round y round_remainder: parte restante respecto al redondeo
    // En 3.25: round(3.25) = 3.0. Resto = 3.25 - 3.0 = +0.25 (redondeo por defecto, sobra 0.25)
    assert(abs_val(frac_round(3.25) - 0.25) < 1e-15);
    assert(abs_val(round_remainder(3.25) - 0.25) < 1e-15);

    // En 3.75: round(3.75) = 4.0. Resto = 3.75 - 4.0 = -0.25 (redondeo por exceso, faltó 0.25)
    assert(abs_val(frac_round(3.75) - (-0.25)) < 1e-15);
    assert(abs_val(round_remainder(3.75) - (-0.25)) < 1e-15);

    // En 3.0: exacto
    assert(frac_round(3.0) == 0.0);

    // FracMode configurable
    assert(abs_val(frac(3.75, FracMode::Defect) - 0.75) < 1e-15);
    assert(abs_val(frac(3.75, FracMode::Excess) - 0.25) < 1e-15);
    assert(abs_val(frac(3.75, FracMode::Round) - (-0.25)) < 1e-15);
    assert(abs_val(frac(3.75, FracMode::Trunc) - 0.75) < 1e-15);

    // Descomposición completa de redondeo
    auto d1 = decompose_rounding(3.25);
    assert(d1.direction == RoundingDirection::Defect);
    assert(d1.rounded == 3.0);
    assert(abs_val(d1.remainder - 0.25) < 1e-15);
    assert(abs_val(d1.defect - 0.25) < 1e-15);
    assert(abs_val(d1.excess - 0.75) < 1e-15);

    auto d2 = decompose_rounding(3.75);
    assert(d2.direction == RoundingDirection::Excess);
    assert(d2.rounded == 4.0);
    assert(abs_val(d2.remainder - (-0.25)) < 1e-15);
    assert(abs_val(d2.defect - 0.75) < 1e-15);
    assert(abs_val(d2.excess - 0.25) < 1e-15);

    auto d3 = decompose_rounding(4.0);
    assert(d3.direction == RoundingDirection::Exact);
    assert(d3.remainder == 0.0);

    std::cout << "[OK] Redondeos optimizados (ceil, floor, trunc, round) y parte fraccionaria (frac) verificados.\n";
  }

  std::cout << "\n¡Todos los tests de spec_functs pasaron exitosamente!\n";
  return 0;
}
