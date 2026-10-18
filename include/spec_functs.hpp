#ifndef SPEC_FUNCTS_HPP_INCLUDED
#define SPEC_FUNCTS_HPP_INCLUDED

#include <complex>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace spec_functs {

/* ==========================================================================
 * CONSTANTES MATEMÁTICAS EN ALTA PRECISIÓN (Sin cmath)
 * ========================================================================== */
namespace constants {
  inline constexpr double pi      = 3.141592653589793238462643383279502884197;
  inline constexpr double two_pi  = 6.283185307179586476925286766559005768394;
  inline constexpr double half_pi = 1.570796326794896619231321691639751442098;
  inline constexpr double e       = 2.718281828459045235360287471352662497757;
  inline constexpr double ln2     = 0.693147180559945309417232121458176568075;
  inline constexpr double inv_ln2 = 1.442695040888963407359924681001892137426;
  inline constexpr double ln10    = 2.302585092994045684017991454684364207601;
  inline constexpr double sqrt_2pi= 2.506628274631000502415765284811045253006;
} // namespace constants

// Trait para identificar std::complex
template <typename T>
struct is_complex : std::false_type {};

template <typename T>
struct is_complex<std::complex<T>> : std::true_type {};

template <typename T>
inline constexpr bool is_complex_v = is_complex<std::remove_cvref_t<T>>::value;

template <typename T>
concept ComplexLike = is_complex_v<T>;

/* ==========================================================================
 * UTILIDADES BÁSICAS (abs, floor, fmod, potencia entera)
 * ========================================================================== */

template <typename T>
constexpr T abs_val(T x) noexcept {
  if constexpr (ComplexLike<T>) {
    // Para std::complex: sqrt(r^2 + i^2) sin cmath
    auto r = x.real() < 0 ? -x.real() : x.real();
    auto i = x.imag() < 0 ? -x.imag() : x.imag();
    if (r == 0) return i;
    if (i == 0) return r;
    // Evitar desbordamiento
    if (r < i) { auto tmp = r; r = i; i = tmp; }
    auto q = i / r;
    // Aproximación de raíz para |z| usando Newton-Raphson
    double s = r * (1.0 + 0.5 * q * q);
    for (int it = 0; it < 5; ++it) {
      s = 0.5 * (s + (r * r + i * i) / s);
    }
    return static_cast<T>(s);
  } else {
    return x < T{0} ? -x : x;
  }
}

// Suelo (floor) para reales
template <std::floating_point T>
constexpr int64_t floor_int(T x) noexcept {
  auto i = static_cast<int64_t>(x);
  if (static_cast<T>(i) > x) {
    --i;
  }
  return i;
}

// Redondeo al entero más cercano
template <std::floating_point T>
constexpr int64_t round_int(T x) noexcept {
  return floor_int(x + T{0.5});
}

// Potencia entera rápida por exponenciación binaria: base^n
template <typename T>
constexpr T int_pow(T base, int64_t exp) noexcept {
  if (exp == 0) return T{1};
  if (exp < 0) return T{1} / int_pow(base, -exp);

  T result{1};
  T cur = base;
  while (exp > 0) {
    if (exp & 1) result = result * cur;
    cur = cur * cur;
    exp >>= 1;
  }
  return result;
}

// Multiplicación rápida por 2^k: x * 2^k
template <std::floating_point T>
constexpr T scale_by_2_pow(T x, int64_t k) noexcept {
  if (k == 0 || x == T{0}) return x;
  if (k > 0) {
    while (k >= 30) { x *= static_cast<T>(1 << 30); k -= 30; }
    return x * static_cast<T>(int64_t{1} << k);
  } else {
    int64_t neg_k = -k;
    while (neg_k >= 30) { x /= static_cast<T>(1 << 30); neg_k -= 30; }
    return x / static_cast<T>(int64_t{1} << neg_k);
  }
}

/* ==========================================================================
 * FUNCIONES TRIGONOMÉTRICAS AUXILIARES (sin, cos) MEDIANTE SERIES DE TAYLOR
 * Necesarias para la fórmula de reflexión de Euler de la función Gamma.
 * ========================================================================== */

// Reduce x a [-pi, pi]
template <std::floating_point T>
constexpr T reduce_angle_pi(T x) noexcept {
  T k = static_cast<T>(round_int(x / static_cast<T>(constants::two_pi)));
  return x - k * static_cast<T>(constants::two_pi);
}

template <std::floating_point T>
constexpr T sin_taylor(T x) noexcept {
  x = reduce_angle_pi(x);
  T term = x;
  T sum = x;
  const T x2 = x * x;
  for (int i = 1; i <= 12; ++i) {
    term = -term * x2 / static_cast<T>((2 * i) * (2 * i + 1));
    sum += term;
    if (term < T{1e-18} && term > T{-1e-18}) break;
  }
  return sum;
}

template <std::floating_point T>
constexpr T cos_taylor(T x) noexcept {
  x = reduce_angle_pi(x);
  T term = T{1};
  T sum = T{1};
  const T x2 = x * x;
  for (int i = 1; i <= 12; ++i) {
    term = -term * x2 / static_cast<T>((2 * i - 1) * (2 * i));
    sum += term;
    if (term < T{1e-18} && term > T{-1e-18}) break;
  }
  return sum;
}

/* ==========================================================================
 * EXPONENCIAL NATURAL (exp) Y DE CUALQUIER BASE (exp_base, pow)
 * ========================================================================== */

/**
 * @brief Exponencial natural e^x para números reales de punto flotante.
 * Algoritmo:
 *   1. Reducción de rango: x = k * ln(2) + r, con |r| <= ln(2)/2 approx 0.34657
 *   2. Serie de Taylor para e^r (convergencia en ~12 términos con precisión completa)
 *   3. e^x = 2^k * e^r
 */
template <std::floating_point T>
constexpr T exp_real(T x) noexcept {
  if (x == T{0}) return T{1};
  if (x < T{-708}) return T{0}; // Underflow para double IEEE-754
  if (x > T{709}) return std::numeric_limits<T>::infinity();

  // 1. Reducción de rango: x = k * ln(2) + r
  const int64_t k = round_int(x * static_cast<T>(constants::inv_ln2));
  const T r = x - static_cast<T>(k) * static_cast<T>(constants::ln2);

  // 2. Serie de Taylor de e^r: 1 + r + r^2/2! + ...
  T term = T{1};
  T sum = T{1};
  for (int i = 1; i <= 16; ++i) {
    term *= r / static_cast<T>(i);
    sum += term;
    if (term < T{1e-18} && term > T{-1e-18}) break;
  }

  // 3. Multiplicar por 2^k
  return scale_by_2_pow(sum, k);
}

/**
 * @brief Exponencial e^z para números complejos std::complex<T>.
 * e^(u + iv) = e^u * (cos(v) + i * sin(v))
 */
template <typename T>
constexpr std::complex<T> exp_complex(const std::complex<T>& z) noexcept {
  T eu = exp_real(z.real());
  T cos_v = cos_taylor(z.imag());
  T sin_v = sin_taylor(z.imag());
  return std::complex<T>(eu * cos_v, eu * sin_v);
}

/**
 * @brief Exponencial natural genérica e^x.
 */
template <typename T>
constexpr auto exp(const T& x) noexcept {
  if constexpr (ComplexLike<T>) {
    return exp_complex(x);
  } else if constexpr (std::floating_point<T>) {
    return exp_real(x);
  } else {
    return exp_real(static_cast<double>(x));
  }
}

/* ==========================================================================
 * LOGARITMO NATURAL (ln) Y EN CUALQUIER BASE (log_base)
 * ========================================================================== */

/**
 * @brief Logaritmo natural ln(x) para números reales x > 0.
 * Algoritmo:
 *   1. Reducción de rango: x = 2^k * m, con m en [1/sqrt(2), sqrt(2)]
 *   2. Cambio de variable: u = (m - 1) / (m + 1), |u| < 0.1716
 *   3. Serie de Gregory: ln(m) = 2 * u * sum_{j=0} u^(2j) / (2j + 1)
 *   4. ln(x) = k * ln(2) + ln(m)
 */
template <std::floating_point T>
constexpr T log_real(T x) noexcept {
  if (x <= T{0}) {
    if (x == T{0}) return -std::numeric_limits<T>::infinity();
    return std::numeric_limits<T>::quiet_NaN();
  }
  if (x == T{1}) return T{0};

  // 1. Reducción de rango a m in [0.7071, 1.4142]
  int64_t k = 0;
  while (x > static_cast<T>(1.41421356237309504880)) {
    x *= T{0.5};
    ++k;
  }
  while (x < static_cast<T>(0.70710678118654752440)) {
    x *= T{2.0};
    --k;
  }

  // 2. Transformación u = (x - 1) / (x + 1)
  const T u = (x - T{1}) / (x + T{1});
  const T u2 = u * u;

  // 3. Serie de Gregory: sum u^(2j) / (2j + 1)
  T term = u;
  T sum = u;
  for (int j = 1; j <= 12; ++j) {
    term *= u2;
    T add = term / static_cast<T>(2 * j + 1);
    sum += add;
    if (add < T{1e-18} && add > T{-1e-18}) break;
  }
  const T ln_m = T{2} * sum;

  // 4. ln(x) = k * ln(2) + ln(m)
  return static_cast<T>(k) * static_cast<T>(constants::ln2) + ln_m;
}

/**
 * @brief Logaritmo natural genérico ln(x).
 */
template <typename T>
constexpr auto log(const T& x) noexcept {
  if constexpr (std::floating_point<T>) {
    return log_real(x);
  } else {
    return log_real(static_cast<double>(x));
  }
}

/**
 * @brief Exponencial en cualquier base: base^x = exp(x * ln(base)).
 */
template <typename BaseT, typename ExpT>
constexpr auto pow(const BaseT& base, const ExpT& exponent) noexcept {
  using CommonFloat = std::common_type_t<double, BaseT, ExpT>;
  if (base == BaseT{0}) {
    if (exponent == ExpT{0}) return CommonFloat{1};
    if (exponent > ExpT{0}) return CommonFloat{0};
    return std::numeric_limits<CommonFloat>::infinity();
  }
  if (base < BaseT{0}) {
    // Si la potencia es entera, cálculo de signo exacto
    if constexpr (std::integral<ExpT>) {
      auto p = int_pow(base, exponent);
      return static_cast<CommonFloat>(p);
    } else {
      // Potencia no entera de número negativo genera NaN en los reales
      return std::numeric_limits<CommonFloat>::quiet_NaN();
    }
  }
  return exp(static_cast<CommonFloat>(exponent) * log(static_cast<CommonFloat>(base)));
}

/**
 * @brief Exponencial con base explícita: b^x
 */
template <typename BaseT, typename ExpT>
constexpr auto exp_base(const BaseT& base, const ExpT& x) noexcept {
  return pow(base, x);
}

/**
 * @brief Logaritmo en cualquier base b > 0 (b != 1): log_b(x) = ln(x) / ln(b).
 */
template <typename BaseT, typename ArgT>
constexpr auto log_base(const BaseT& base, const ArgT& x) noexcept {
  using CommonFloat = std::common_type_t<double, BaseT, ArgT>;
  return log(static_cast<CommonFloat>(x)) / log(static_cast<CommonFloat>(base));
}

/**
 * @brief Logaritmo decimal (base 10).
 */
template <typename T>
constexpr auto log10(const T& x) noexcept {
  return log(x) / static_cast<double>(constants::ln10);
}

/**
 * @brief Logaritmo binario (base 2).
 */
template <typename T>
constexpr auto log2(const T& x) noexcept {
  return log(x) * static_cast<double>(constants::inv_ln2);
}

/* ==========================================================================
 * FUNCIÓN GAMMA DE EULER: Gamma(z) Y ln(Gamma(z))
 * Implementada con la aproximación de Lanczos (g = 7, N = 9) y la fórmula
 * de reflexión de Euler para Re(z) < 0.5.
 * ========================================================================== */

namespace detail {

// Coeficientes de Lanczos para g = 7, n = 9 (precisión de 15-16 dígitos)
inline constexpr double lanczos_g = 7.0;
inline constexpr double lanczos_c[9] = {
    0.99999999999980993,
    676.5203681218851,
   -1259.1392167224028,
    771.32342877765313,
   -176.61502916214059,
    12.507343278686905,
   -0.1385710958365926,
    9.9843695780195716e-6,
    1.5056327351493116e-7
};

} // namespace detail

/**
 * @brief Función Gamma de Euler Gamma(z) para números reales.
 * Utiliza Lanczos para z >= 0.5 y la fórmula de reflexión:
 *   Gamma(1 - z) * Gamma(z) = pi / sin(pi * z) para z < 0.5.
 */
template <std::floating_point T>
constexpr T gamma_real(T z) noexcept {
  // Manejo de polos en enteros no positivos: 0, -1, -2, ...
  if (z <= T{0} && z == static_cast<T>(floor_int(z))) {
    return std::numeric_limits<T>::quiet_NaN();
  }

  // Factoriales exactos para enteros positivos pequeños (z <= 20)
  if (z > T{0} && z <= T{20} && z == static_cast<T>(floor_int(z))) {
    int64_t n = floor_int(z) - 1;
    T fact = T{1};
    for (int64_t i = 2; i <= n; ++i) {
      fact *= static_cast<T>(i);
    }
    return fact;
  }

  // 1. Fórmula de reflexión de Euler para z < 0.5:
  //    Gamma(z) = pi / (sin(pi * z) * Gamma(1 - z))
  if (z < T{0.5}) {
    T sin_val = sin_taylor(static_cast<T>(constants::pi) * z);
    return static_cast<T>(constants::pi) / (sin_val * gamma_real(T{1} - z));
  }

  // 2. Aproximación de Lanczos para z >= 0.5
  z -= T{1};
  T x = static_cast<T>(detail::lanczos_c[0]);
  for (std::size_t i = 1; i < 9; ++i) {
    x += static_cast<T>(detail::lanczos_c[i]) / (z + static_cast<T>(i));
  }

  T t = z + static_cast<T>(detail::lanczos_g) + T{0.5};
  // sqrt(2*pi) * t^(z + 0.5) * exp(-t) * x
  T p = pow(t, z + T{0.5});
  return static_cast<T>(constants::sqrt_2pi) * p * exp(-t) * x;
}

/**
 * @brief Logaritmo natural de la función Gamma: ln|Gamma(z)|.
 * Vital para cálculos de combinatoria, distribuciones y función Beta
 * sin desbordamiento numérico.
 */
template <std::floating_point T>
constexpr T lgamma_real(T z) noexcept {
  if (z <= T{0} && z == static_cast<T>(floor_int(z))) {
    return std::numeric_limits<T>::infinity();
  }

  // Factoriales exactos para enteros positivos pequeños (z <= 20)
  if (z > T{0} && z <= T{20} && z == static_cast<T>(floor_int(z))) {
    int64_t n = floor_int(z) - 1;
    T fact = T{1};
    for (int64_t i = 2; i <= n; ++i) {
      fact *= static_cast<T>(i);
    }
    return log(fact);
  }

  if (z < T{0.5}) {
    // ln|Gamma(z)| = ln(pi) - ln|sin(pi * z)| - ln|Gamma(1 - z)|
    T sin_val = abs_val(sin_taylor(static_cast<T>(constants::pi) * z));
    return log(static_cast<T>(constants::pi)) - log(sin_val) - lgamma_real(T{1} - z);
  }

  z -= T{1};
  T x = static_cast<T>(detail::lanczos_c[0]);
  for (std::size_t i = 1; i < 9; ++i) {
    x += static_cast<T>(detail::lanczos_c[i]) / (z + static_cast<T>(i));
  }

  T t = z + static_cast<T>(detail::lanczos_g) + T{0.5};
  return T{0.5} * log(static_cast<T>(constants::two_pi)) +
         (z + T{0.5}) * log(t) - t + log(x);
}

/**
 * @brief Función Gamma de Euler Gamma(z) genérica.
 */
template <typename T>
constexpr auto gamma(const T& z) noexcept {
  if constexpr (std::floating_point<T>) {
    return gamma_real(z);
  } else {
    return gamma_real(static_cast<double>(z));
  }
}

/**
 * @brief Logaritmo natural de Gamma: ln|Gamma(z)| genérico.
 */
template <typename T>
constexpr auto lgamma(const T& z) noexcept {
  if constexpr (std::floating_point<T>) {
    return lgamma_real(z);
  } else {
    return lgamma_real(static_cast<double>(z));
  }
}

/* ==========================================================================
 * FUNCIÓN BETA DE EULER: B(x, y) = Gamma(x) * Gamma(y) / Gamma(x + y)
 * ========================================================================== */

/**
 * @brief Función Beta de Euler: B(x, y) = Gamma(x) * Gamma(y) / Gamma(x + y).
 * Para evitar desbordamiento numérico (overflow) con argumentos moderados o grandes,
 * se calcula a través de exp(lgamma(x) + lgamma(y) - lgamma(x + y)).
 */
template <typename T, typename U>
constexpr auto beta(const T& x, const U& y) noexcept {
  using CommonFloat = std::common_type_t<double, T, U>;
  CommonFloat fx = static_cast<CommonFloat>(x);
  CommonFloat fy = static_cast<CommonFloat>(y);

  // Para argumentos pequeños positivos, cálculo directo
  if (fx > CommonFloat{0} && fx < CommonFloat{15} &&
      fy > CommonFloat{0} && fy < CommonFloat{15}) {
    return (gamma(fx) * gamma(fy)) / gamma(fx + fy);
  }

  // Para evitar desbordamiento o argumentos grandes: exp(lgamma(x) + lgamma(y) - lgamma(x+y))
  CommonFloat log_b = lgamma(fx) + lgamma(fy) - lgamma(fx + fy);
  return exp(log_b);
}

/**
 * @brief Logaritmo de la función Beta: ln B(x, y) = ln Gamma(x) + ln Gamma(y) - ln Gamma(x + y).
 */
template <typename T, typename U>
constexpr auto lbeta(const T& x, const U& y) noexcept {
  using CommonFloat = std::common_type_t<double, T, U>;
  CommonFloat fx = static_cast<CommonFloat>(x);
  CommonFloat fy = static_cast<CommonFloat>(y);
  return lgamma(fx) + lgamma(fy) - lgamma(fx + fy);
}

} // namespace spec_functs

#endif // SPEC_FUNCTS_HPP_INCLUDED
