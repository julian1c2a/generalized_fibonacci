#ifndef POLY_HPP_INCLUDED
#define POLY_HPP_INCLUDED

#include "type_traits.hpp"
#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <span>
#include <type_traits>
#include <utility>
#include <vector>

namespace poly {

using traits::complex;
using traits::is_complex;
using traits::is_complex_v;
using traits::ComplexNumber;
using traits::ComplexLike;
using traits::Arithmetic;
using traits::eval_result_t;
using traits::complex_value_t;
using traits::to_floating_point_t;

/* ==========================================================================
 * ALGORITMOS DE EVALUACIÓN SOBRE SPANS (Zero-overhead, Constexpr)
 * Los coeficientes se ordenan en sentido ascendente:
 *   coeffs[i] corresponde al coeficiente de x^i
 *   P(x) = coeffs[0] + coeffs[1]*x + ... + coeffs[n]*x^n
 * ========================================================================== */

/**
 * @brief Evalúa un polinomio usando la Regla de Horner clásica.
 * Mínimo número de multiplicaciones y sumas secuenciales: O(n).
 */
template <typename T, typename U>
constexpr auto eval_horner(std::span<const T> coeffs, const U& x) {
  using ResultType = eval_result_t<T, U>;
  if (coeffs.empty()) {
    return ResultType{0};
  }

  std::size_t i = coeffs.size() - 1;
  ResultType result = static_cast<ResultType>(coeffs[i]);
  while (i > 0) {
    --i;
    result = result * x + static_cast<ResultType>(coeffs[i]);
  }
  return result;
}

/**
 * @brief Evalúa un polinomio y su primera derivada simultáneamente en x.
 * Utiliza la variante de Horner para cálculo conjunto:
 *   P(x) y P'(x) en un único recorrido con O(n) operaciones.
 * @return std::pair<ResultType, ResultType> con {P(x), P'(x)}.
 */
template <typename T, typename U>
constexpr auto eval_horner_with_derivative(std::span<const T> coeffs, const U& x) {
  using ResultType = eval_result_t<T, U>;
  if (coeffs.empty()) {
    return std::pair<ResultType, ResultType>{ResultType{0}, ResultType{0}};
  }
  if (coeffs.size() == 1) {
    return std::pair<ResultType, ResultType>{static_cast<ResultType>(coeffs[0]), ResultType{0}};
  }

  std::size_t i = coeffs.size() - 1;
  ResultType p = static_cast<ResultType>(coeffs[i]);
  ResultType dp = ResultType{0};

  while (i > 0) {
    --i;
    dp = dp * x + p;
    p = p * x + static_cast<ResultType>(coeffs[i]);
  }

  return std::pair<ResultType, ResultType>{p, dp};
}

/**
 * @brief Evalúa el polinomio y sus derivadas hasta el orden max_order usando el
 * algoritmo de Ruffini-Horner (divisiones sintéticas sucesivas).
 * @return std::vector<ResultType> con [P(x), P'(x), P''(x), ..., P^(k)(x)]
 */
template <typename T, typename U>
constexpr auto eval_horner_all_derivatives(std::span<const T> coeffs, const U& x,
                                          std::size_t max_order) {
  using ResultType = eval_result_t<T, U>;
  if (coeffs.empty()) {
    return std::vector<ResultType>{};
  }

  const std::size_t n = coeffs.size();
  const std::size_t orders = std::min(max_order + 1, n);

  // Copia de coeficientes como tabla de trabajo
  std::vector<ResultType> b(n);
  for (std::size_t i = 0; i < n; ++i) {
    b[i] = static_cast<ResultType>(coeffs[i]);
  }

  // Esquema de Horner repetido:
  // Al final de la k-ésima pasada, b[k] contiene P^(k)(x) / k!
  for (std::size_t k = 0; k < orders; ++k) {
    for (std::size_t j = n - 1; j > k; --j) {
      b[j - 1] += b[j] * x;
    }
  }

  // Multiplicar por k! para obtener P^(k)(x)
  std::vector<ResultType> derivatives(orders);
  ResultType factorial = ResultType{1};
  for (std::size_t k = 0; k < orders; ++k) {
    if (k > 0) {
      factorial = factorial * ResultType(k);
    }
    derivatives[k] = b[k] * factorial;
  }

  return derivatives;
}

namespace detail {

template <typename T, typename U>
constexpr auto eval_estrin_recursive(std::span<const T> coeffs, const U& x) {
  using ResultType = eval_result_t<T, U>;
  const std::size_t n = coeffs.size();

  if (n == 0) return ResultType{0};
  if (n == 1) return static_cast<ResultType>(coeffs[0]);
  if (n == 2) return static_cast<ResultType>(coeffs[0]) + static_cast<ResultType>(coeffs[1]) * x;

  // Reducción por pares en árbol logarítmico
  const std::size_t half = (n + 1) / 2;
  std::vector<ResultType> reduced;
  reduced.reserve(half);

  for (std::size_t i = 0; i < n; i += 2) {
    if (i + 1 < n) {
      reduced.push_back(static_cast<ResultType>(coeffs[i]) +
                        static_cast<ResultType>(coeffs[i + 1]) * x);
    } else {
      reduced.push_back(static_cast<ResultType>(coeffs[i]));
    }
  }

  const auto x2 = x * x;
  return eval_estrin_recursive(std::span<const ResultType>(reduced), x2);
}

} // namespace detail

/**
 * @brief Evalúa un polinomio usando el Esquema de Estrin.
 * Reduce la profundidad del árbol de dependencias a O(log n), favoreciendo
 * la ejecución paralela en el procesador (ILP) y vectorización SIMD.
 */
template <typename T, typename U>
constexpr auto eval_estrin(std::span<const T> coeffs, const U& x) {
  return detail::eval_estrin_recursive(coeffs, x);
}

/* ==========================================================================
 * OPERACIONES BÁSICAS Y ALGORITMOS ALGEBRAICOS (CONVOLUCIÓN, DIV/MOD)
 * ========================================================================== */

/**
 * @brief Multiplicación (convolución directa) de dos secuencias de coeficientes.
 */
template <typename T>
constexpr std::vector<T> poly_multiply(std::span<const T> a, std::span<const T> b) {
  if (a.empty() || b.empty()) {
    return {};
  }
  std::vector<T> result(a.size() + b.size() - 1, T{0});
  for (std::size_t i = 0; i < a.size(); ++i) {
    if (a[i] == T{0}) continue;
    for (std::size_t j = 0; j < b.size(); ++j) {
      result[i + j] += a[i] * b[j];
    }
  }
  return result;
}

/**
 * @brief Elimina ceros no significativos a la derecha del vector de coeficientes.
 */
template <typename T>
constexpr void poly_trim(std::vector<T>& coeffs) {
  while (coeffs.size() > 1 && coeffs.back() == T{0}) {
    coeffs.pop_back();
  }
  if (coeffs.size() == 1 && coeffs.back() == T{0}) {
    // Mantener al menos un coeficiente [0] para el polinomio nulo
  }
}

/**
 * @brief División euclídea de polinomios: a = q * b + r con deg(r) < deg(b).
 * Devuelve pair{q, r}. Requiere que el coeficiente principal de b sea invertible.
 */
template <typename T>
constexpr std::pair<std::vector<T>, std::vector<T>>
poly_divmod(std::span<const T> a, std::span<const T> b) {
  std::vector<T> num(a.begin(), a.end());
  poly_trim(num);

  std::vector<T> den(b.begin(), b.end());
  poly_trim(den);

  if (den.empty() || (den.size() == 1 && den[0] == T{0})) {
    // División por cero polinomial
    return {{}, {}};
  }

  if (num.size() < den.size()) {
    return {{T{0}}, num};
  }

  const std::size_t deg_a = num.size() - 1;
  const std::size_t deg_b = den.size() - 1;
  const std::size_t deg_q = deg_a - deg_b;

  std::vector<T> q(deg_q + 1, T{0});
  const T lead_b = den.back();

  for (std::size_t i = deg_q + 1; i > 0; --i) {
    const std::size_t q_idx = i - 1;
    const std::size_t num_idx = deg_b + q_idx;
    const T coeff = num[num_idx] / lead_b;
    q[q_idx] = coeff;

    for (std::size_t j = 0; j <= deg_b; ++j) {
      num[q_idx + j] -= coeff * den[j];
    }
  }

  poly_trim(num);
  poly_trim(q);
  return {q, num};
}

/**
 * @brief Resto de la división euclídea: a mod b.
 */
template <typename T>
constexpr std::vector<T> poly_mod(std::span<const T> a, std::span<const T> b) {
  return poly_divmod(a, b).second;
}

/* ==========================================================================
 * POTENCIACIÓN: BINARY EXPONENTIATION (SQUARE-AND-MULTIPLY)
 * ========================================================================== */

/**
 * @brief Potenciación binaria clásica: P(x)^k.
 * Complejidad O(log k * M(d)).
 */
template <typename T, std::integral ExpType>
constexpr std::vector<T> poly_pow(std::span<const T> base, ExpType exp) {
  if (exp < 0) {
    return {};
  }
  if (exp == 0) {
    return {T{1}};
  }
  if (base.empty()) {
    return {T{0}};
  }

  std::vector<T> result = {T{1}};
  std::vector<T> current(base.begin(), base.end());
  auto uexp = static_cast<std::make_unsigned_t<ExpType>>(exp);

  while (uexp > 0) {
    if (uexp & 1) {
      result = poly_multiply<T>(result, current);
    }
    uexp >>= 1;
    if (uexp > 0) {
      current = poly_multiply<T>(current, current);
    }
  }

  poly_trim(result);
  return result;
}

/**
 * @brief Potenciación modular binaria: (base(x)^exp) mod mod_poly(x).
 * Esencial para el algoritmo de Fiduccia y cálculo en O(d^2 log k) del término
 * k-ésimo en recurrencias lineales (generalized Fibonacci).
 */
template <typename T, std::integral ExpType>
constexpr std::vector<T> poly_pow_mod(std::span<const T> base, ExpType exp,
                                      std::span<const T> mod_poly) {
  if (exp < 0) {
    return {};
  }
  if (exp == 0) {
    std::vector<T> one = {T{1}};
    return poly_mod<T>(one, mod_poly);
  }

  std::vector<T> result = {T{1}};
  std::vector<T> current = poly_mod<T>(base, mod_poly);
  auto uexp = static_cast<std::make_unsigned_t<ExpType>>(exp);

  while (uexp > 0) {
    if (uexp & 1) {
      result = poly_multiply<T>(result, current);
      result = poly_mod<T>(result, mod_poly);
    }
    uexp >>= 1;
    if (uexp > 0) {
      current = poly_multiply<T>(current, current);
      current = poly_mod<T>(current, mod_poly);
    }
  }

  poly_trim(result);
  return result;
}

/* ==========================================================================
 * ESTRUCTURAS DE POLINOMIOS (ESTÁTICA Y DINÁMICA)
 * ========================================================================== */

// Declaración adelantada
template <Arithmetic T>
class DynamicPoly;

/**
 * @brief Polinomio de tamaño y grado estático fijo en tiempo de compilación.
 * Almacenado en std::array<T, Degree + 1>, 100% constexpr y sin asignación dinámica.
 */
template <Arithmetic T, std::size_t Degree>
class StaticPoly {
public:
  using value_type = T;
  static constexpr std::size_t max_degree = Degree;
  static constexpr std::size_t coefficient_count = Degree + 1;

private:
  std::array<T, coefficient_count> coeffs_{};

public:
  // Constructores
  constexpr StaticPoly() = default;

  constexpr explicit StaticPoly(const std::array<T, coefficient_count>& arr)
      : coeffs_(arr) {}

  constexpr StaticPoly(std::initializer_list<T> list) {
    std::size_t i = 0;
    for (const auto& val : list) {
      if (i < coefficient_count) {
        coeffs_[i++] = val;
      }
    }
  }

  // Grado teórico máximo del contenedor
  [[nodiscard]] constexpr std::size_t degree_bound() const noexcept {
    return Degree;
  }

  // Grado real del polinomio (índice del último coeficiente no nulo)
  [[nodiscard]] constexpr std::size_t degree() const noexcept {
    for (std::size_t i = coefficient_count; i > 0; --i) {
      if (coeffs_[i - 1] != T{0}) {
        return i - 1;
      }
    }
    return 0;
  }

  [[nodiscard]] constexpr std::size_t size() const noexcept {
    return coefficient_count;
  }

  [[nodiscard]] constexpr const T* data() const noexcept {
    return coeffs_.data();
  }

  [[nodiscard]] constexpr T* data() noexcept {
    return coeffs_.data();
  }

  [[nodiscard]] constexpr std::span<const T> span() const noexcept {
    return std::span<const T>(coeffs_.data(), coefficient_count);
  }

  // Acceso a coeficientes
  [[nodiscard]] constexpr const T& operator[](std::size_t idx) const noexcept {
    return coeffs_[idx];
  }

  [[nodiscard]] constexpr T& operator[](std::size_t idx) noexcept {
    return coeffs_[idx];
  }

  // Evaluaciones con diferentes métodos
  template <typename U>
  [[nodiscard]] constexpr auto eval(const U& x) const {
    return eval_horner(span(), x);
  }

  template <typename U>
  [[nodiscard]] constexpr auto operator()(const U& x) const {
    return eval(x);
  }

  template <typename U>
  [[nodiscard]] constexpr auto eval_estrin(const U& x) const {
    return ::poly::eval_estrin(span(), x);
  }

  template <typename U>
  [[nodiscard]] constexpr auto eval_with_derivative(const U& x) const {
    return eval_horner_with_derivative(span(), x);
  }

  template <typename U>
  [[nodiscard]] constexpr auto eval_derivatives(const U& x, std::size_t max_order) const {
    return eval_horner_all_derivatives(span(), x, max_order);
  }

  // Operaciones estáticas de suma y resta
  template <std::size_t OtherDegree>
  constexpr auto operator+(const StaticPoly<T, OtherDegree>& other) const {
    constexpr std::size_t MaxD = (Degree > OtherDegree ? Degree : OtherDegree);
    StaticPoly<T, MaxD> result{};
    for (std::size_t i = 0; i <= Degree; ++i) {
      result[i] += coeffs_[i];
    }
    for (std::size_t i = 0; i <= OtherDegree; ++i) {
      result[i] += other[i];
    }
    return result;
  }

  template <std::size_t OtherDegree>
  constexpr auto operator-(const StaticPoly<T, OtherDegree>& other) const {
    constexpr std::size_t MaxD = (Degree > OtherDegree ? Degree : OtherDegree);
    StaticPoly<T, MaxD> result{};
    for (std::size_t i = 0; i <= Degree; ++i) {
      result[i] += coeffs_[i];
    }
    for (std::size_t i = 0; i <= OtherDegree; ++i) {
      result[i] -= other[i];
    }
    return result;
  }

  // Multiplicación estática: el grado del resultado es Degree + OtherDegree
  template <std::size_t OtherDegree>
  constexpr StaticPoly<T, Degree + OtherDegree>
  operator*(const StaticPoly<T, OtherDegree>& other) const {
    StaticPoly<T, Degree + OtherDegree> result{};
    for (std::size_t i = 0; i <= Degree; ++i) {
      if (coeffs_[i] == T{0}) continue;
      for (std::size_t j = 0; j <= OtherDegree; ++j) {
        result[i + j] += coeffs_[i] * other[j];
      }
    }
    return result;
  }

  constexpr StaticPoly<T, Degree>& operator*=(const T& scalar) noexcept {
    for (auto& c : coeffs_) c *= scalar;
    return *this;
  }

  // Potencia estática: P(x)^Exp
  template <std::size_t Exp>
  constexpr auto pow() const {
    if constexpr (Exp == 0) {
      StaticPoly<T, 0> res{T{1}};
      return res;
    } else if constexpr (Exp == 1) {
      return *this;
    } else {
      auto half = this->template pow<Exp / 2>();
      auto sq = half * half;
      if constexpr (Exp % 2 == 1) {
        return sq * (*this);
      } else {
        return sq;
      }
    }
  }

  // Derivada formal como nuevo polinomio estático
  constexpr auto derivative() const {
    if constexpr (Degree == 0) {
      return StaticPoly<T, 0>{T{0}};
    } else {
      StaticPoly<T, Degree - 1> res{};
      for (std::size_t i = 1; i <= Degree; ++i) {
        res[i - 1] = coeffs_[i] * T(i);
      }
      return res;
    }
  }
};

/**
 * @brief Polinomio de tamaño y grado dinámico en tiempo de ejecución.
 * Almacenado en std::vector<T>. Admite operaciones de grado arbitrario, división
 * y potenciación modular.
 */
template <Arithmetic T>
class DynamicPoly {
public:
  using value_type = T;

private:
  std::vector<T> coeffs_;

public:
  constexpr DynamicPoly() : coeffs_{T{0}} {}

  constexpr explicit DynamicPoly(std::size_t size, const T& default_val = T{0})
      : coeffs_(size > 0 ? size : 1, default_val) {
    trim();
  }

  constexpr DynamicPoly(std::initializer_list<T> list)
      : coeffs_(list.begin(), list.end()) {
    if (coeffs_.empty()) coeffs_.push_back(T{0});
    trim();
  }

  constexpr explicit DynamicPoly(std::vector<T> coeffs)
      : coeffs_(std::move(coeffs)) {
    if (coeffs_.empty()) coeffs_.push_back(T{0});
    trim();
  }

  constexpr explicit DynamicPoly(std::span<const T> s)
      : coeffs_(s.begin(), s.end()) {
    if (coeffs_.empty()) coeffs_.push_back(T{0});
    trim();
  }

  // Conversión desde StaticPoly
  template <std::size_t Deg>
  constexpr explicit DynamicPoly(const StaticPoly<T, Deg>& sp)
      : coeffs_(sp.data(), sp.data() + sp.size()) {
    trim();
  }

  constexpr void trim() {
    poly_trim(coeffs_);
  }

  [[nodiscard]] constexpr std::size_t degree() const noexcept {
    for (std::size_t i = coeffs_.size(); i > 0; --i) {
      if (coeffs_[i - 1] != T{0}) {
        return i - 1;
      }
    }
    return 0;
  }

  [[nodiscard]] constexpr std::size_t size() const noexcept {
    return coeffs_.size();
  }

  [[nodiscard]] constexpr const T* data() const noexcept {
    return coeffs_.data();
  }

  [[nodiscard]] constexpr T* data() noexcept {
    return coeffs_.data();
  }

  [[nodiscard]] constexpr std::span<const T> span() const noexcept {
    return std::span<const T>(coeffs_.data(), coeffs_.size());
  }

  [[nodiscard]] constexpr const std::vector<T>& raw_coeffs() const noexcept {
    return coeffs_;
  }

  [[nodiscard]] constexpr const T& operator[](std::size_t idx) const noexcept {
    return coeffs_[idx];
  }

  [[nodiscard]] constexpr T& operator[](std::size_t idx) {
    if (idx >= coeffs_.size()) {
      coeffs_.resize(idx + 1, T{0});
    }
    return coeffs_[idx];
  }

  // Evaluaciones
  template <typename U>
  [[nodiscard]] constexpr auto eval(const U& x) const {
    return eval_horner(span(), x);
  }

  template <typename U>
  [[nodiscard]] constexpr auto operator()(const U& x) const {
    return eval(x);
  }

  template <typename U>
  [[nodiscard]] constexpr auto eval_estrin(const U& x) const {
    return ::poly::eval_estrin(span(), x);
  }

  template <typename U>
  [[nodiscard]] constexpr auto eval_with_derivative(const U& x) const {
    return eval_horner_with_derivative(span(), x);
  }

  template <typename U>
  [[nodiscard]] constexpr auto eval_derivatives(const U& x, std::size_t max_order) const {
    return eval_horner_all_derivatives(span(), x, max_order);
  }

  // Operadores algebraicos
  constexpr DynamicPoly& operator+=(const DynamicPoly& other) {
    if (other.coeffs_.size() > coeffs_.size()) {
      coeffs_.resize(other.coeffs_.size(), T{0});
    }
    for (std::size_t i = 0; i < other.coeffs_.size(); ++i) {
      coeffs_[i] += other.coeffs_[i];
    }
    trim();
    return *this;
  }

  constexpr DynamicPoly& operator-=(const DynamicPoly& other) {
    if (other.coeffs_.size() > coeffs_.size()) {
      coeffs_.resize(other.coeffs_.size(), T{0});
    }
    for (std::size_t i = 0; i < other.coeffs_.size(); ++i) {
      coeffs_[i] -= other.coeffs_[i];
    }
    trim();
    return *this;
  }

  constexpr DynamicPoly& operator*=(const T& scalar) {
    for (auto& c : coeffs_) c *= scalar;
    trim();
    return *this;
  }

  friend constexpr DynamicPoly operator+(DynamicPoly a, const DynamicPoly& b) {
    a += b;
    return a;
  }

  friend constexpr DynamicPoly operator-(DynamicPoly a, const DynamicPoly& b) {
    a -= b;
    return a;
  }

  friend constexpr DynamicPoly operator*(const DynamicPoly& a, const DynamicPoly& b) {
    return DynamicPoly(poly_multiply<T>(a.span(), b.span()));
  }

  friend constexpr DynamicPoly operator/(const DynamicPoly& a, const DynamicPoly& b) {
    return DynamicPoly(poly_divmod<T>(a.span(), b.span()).first);
  }

  friend constexpr DynamicPoly operator%(const DynamicPoly& a, const DynamicPoly& b) {
    return DynamicPoly(poly_divmod<T>(a.span(), b.span()).second);
  }

  // Potenciación binaria P(x)^k
  template <std::integral ExpType>
  [[nodiscard]] constexpr DynamicPoly pow(ExpType exp) const {
    return DynamicPoly(poly_pow<T>(span(), exp));
  }

  // Potenciación modular binaria P(x)^exp mod M(x)
  template <std::integral ExpType>
  [[nodiscard]] constexpr DynamicPoly pow_mod(ExpType exp, const DynamicPoly& mod_poly) const {
    return DynamicPoly(poly_pow_mod<T>(span(), exp, mod_poly.span()));
  }

  // Derivada formal
  [[nodiscard]] constexpr DynamicPoly derivative() const {
    if (coeffs_.size() <= 1) {
      return DynamicPoly({T{0}});
    }
    std::vector<T> res(coeffs_.size() - 1);
    for (std::size_t i = 1; i < coeffs_.size(); ++i) {
      res[i - 1] = coeffs_[i] * T(i);
    }
    return DynamicPoly(std::move(res));
  }
};

} // namespace poly

#endif // POLY_HPP_INCLUDED
