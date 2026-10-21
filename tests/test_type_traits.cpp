#include "../include/type_traits.hpp"
#include <cassert>
#include <complex>
#include <concepts>
#include <iostream>
#include <type_traits>

namespace test_compile_time {
  using namespace gfib::traits;

  // 1. Verificación del alias template complex
  static_assert(std::same_as<complex<>, std::complex<double>>);
  static_assert(std::same_as<complex<double>, std::complex<double>>);
  static_assert(std::same_as<complex<float>, std::complex<float>>);
  static_assert(std::same_as<complex<long double>, std::complex<long double>>);

  // 2. Trait is_complex e is_complex_v
  static_assert(is_complex_v<std::complex<double>>);
  static_assert(is_complex_v<std::complex<float>>);
  static_assert(is_complex_v<std::complex<int>>);
  static_assert(is_complex_v<complex<double>>);
  static_assert(is_complex_v<complex<float>>);
  static_assert(is_complex_v<const complex<double>&>);
  static_assert(is_complex_v<volatile complex<float>>);
  static_assert(!is_complex_v<double>);
  static_assert(!is_complex_v<int>);
  static_assert(!is_complex_v<float>);

  // 3. Conceptos ComplexNumber y ComplexLike
  static_assert(ComplexNumber<std::complex<double>>);
  static_assert(ComplexNumber<complex<float>>);
  static_assert(ComplexLike<std::complex<double>>);
  static_assert(ComplexLike<complex<float>>);
  static_assert(!ComplexNumber<int>);
  static_assert(!ComplexLike<double>);

  // 4. Trait complex_value_t
  static_assert(std::same_as<complex_value_t<std::complex<float>>, float>);
  static_assert(std::same_as<complex_value_t<complex<double>>, double>);
  static_assert(std::same_as<complex_value_t<std::complex<int>>, int>);
  static_assert(std::same_as<complex_value_t<double>, double>);
  static_assert(std::same_as<complex_value_t<int>, int>);

  // 5. Trait to_floating_point_t
  static_assert(std::same_as<to_floating_point_t<float>, float>);
  static_assert(std::same_as<to_floating_point_t<double>, double>);
  static_assert(std::same_as<to_floating_point_t<int>, double>);
  static_assert(std::same_as<to_floating_point_t<int, float>, float>);
  static_assert(std::same_as<to_floating_point_t<std::complex<int>>, double>);
  static_assert(std::same_as<to_floating_point_t<std::complex<int>, float>, float>);
  static_assert(std::same_as<to_floating_point_t<complex<float>>, float>);
  static_assert(std::same_as<to_floating_point_t<complex<double>>, double>);

  // 6. Conceptos de Aritmética
  static_assert(Arithmetic<int>);
  static_assert(Arithmetic<float>);
  static_assert(Arithmetic<double>);
  static_assert(Arithmetic<std::complex<double>>);
  static_assert(Arithmetic<complex<float>>);
  static_assert(SemiringArithmetic<int>);
  static_assert(SemiringArithmetic<complex<double>>);

  // 7. eval_result_t
  static_assert(std::same_as<eval_result_t<double, double>, double>);
  static_assert(std::same_as<eval_result_t<int, double>, double>);
  static_assert(std::same_as<eval_result_t<std::complex<double>, double>, std::complex<double>>);
} // namespace test_compile_time

int main() {
  using namespace gfib::traits;
  std::cout << "--- Ejecutando tests de type_traits.hpp ---\n";

  // Verificación de instancias de complex
  complex<> def_c(1.0, 2.0);
  assert(def_c.real() == 1.0 && def_c.imag() == 2.0);
  static_assert(std::same_as<decltype(def_c), std::complex<double>>);

  complex<float> float_c(3.0f, -4.0f);
  assert(float_c.real() == 3.0f && float_c.imag() == -4.0f);
  static_assert(std::same_as<decltype(float_c), std::complex<float>>);

  complex<long double> ld_c(5.0L, 6.0L);
  assert(ld_c.real() == 5.0L && ld_c.imag() == 6.0L);
  static_assert(std::same_as<decltype(ld_c), std::complex<long double>>);

  std::cout << "[OK] template <std::floating_point T = double> complex verificado.\n";
  std::cout << "[OK] is_complex, ComplexNumber, ComplexLike verificados.\n";
  std::cout << "[OK] complex_value_t y to_floating_point_t verificados.\n";
  std::cout << "[OK] Arithmetic y SemiringArithmetic verificados.\n";
  std::cout << "[OK] eval_result_t verificado.\n";

  std::cout << "\n¡Todos los tests de type_traits pasaron exitosamente!\n";
  return 0;
}
