#ifndef GFIB_HPP_INCLUDED
#define GFIB_HPP_INCLUDED

#include "type_traits.hpp"
#include <array>
#include <concepts>
#include <cstdint>
#include <span>
#include <vector>

namespace gfib {

using traits::complex;
using traits::is_complex;
using traits::is_complex_v;
using traits::ComplexNumber;
using traits::ComplexLike;
using traits::Arithmetic;
using traits::SemiringArithmetic;
using traits::complex_value_t;
using traits::to_floating_point_t;

// Función genérica para calcular el término n-ésimo con coeficientes y valores pasados por span.
// Soporta cualquier tipo aritmético (enteros, reales y complejos) sin requerir tipos estructurales de NTTP.
template <Arithmetic T, std::size_t Extent1 = std::dynamic_extent,
          std::size_t Extent2 = std::dynamic_extent, std::unsigned_integral N = std::size_t>
constexpr T compute_sequence(std::span<const T, Extent1> coeffs, std::span<const T, Extent2> initvals, N n) {
  const std::size_t order = initvals.size();
  const std::size_t init_count = order;

  if (static_cast<std::size_t>(n) < init_count) {
    return initvals[n];
  }

  if (order == 0) {
    return coeffs.empty() ? T{} : coeffs[0];
  }

  std::vector<T> sequence(std::max(static_cast<std::size_t>(n + 1), init_count));
  for (std::size_t i = 0; i < init_count; ++i) {
    sequence[i] = initvals[i];
  }

  for (std::size_t i = init_count; i <= static_cast<std::size_t>(n); ++i) {
    T next_val = coeffs[order]; // Término independiente
    for (std::size_t k = 0; k < order; ++k) {
      const std::size_t prev_idx = i - 1 - k;
      next_val += coeffs[k] * sequence[prev_idx];
    }
    sequence[i] = next_val;
  }

  return sequence[n];
}

// Sobrecarga concisa deducida en tiempo de compilación para tipos estructurales (C++20 NTTP)
template <auto coeffs, auto initvals, std::unsigned_integral N = std::size_t>
  requires(coeffs.size() == initvals.size() + 1) &&
          std::same_as<typename decltype(coeffs)::value_type,
                       typename decltype(initvals)::value_type> &&
          Arithmetic<typename decltype(coeffs)::value_type>
constexpr auto compute_sequence(N n) noexcept {
  return compute_sequence(std::span(coeffs), std::span(initvals), n);
}

// Plantilla con ORDER explícito y tipos genéricos
template <std::size_t ORDER, Arithmetic T, std::unsigned_integral N,
          std::array<T, ORDER + 1> coeffs, std::array<T, ORDER> initvals>
constexpr T compute_sequence(N n) noexcept {
  return compute_sequence<coeffs, initvals, N>(n);
}

// Generador constexpr de array precomputado para COUNT elementos
template <auto coeffs, auto initvals, std::size_t COUNT>
constexpr auto precompute_sequence_array() {
  using T = typename decltype(coeffs)::value_type;
  constexpr std::size_t ORDER = initvals.size();
  std::array<T, COUNT> arr{};

  for (std::size_t i = 0; i < COUNT; ++i) {
    if constexpr (ORDER == 0) {
      arr[i] = coeffs[0];
    } else if (i < ORDER) {
      arr[i] = initvals[i];
    } else {
      T next_val = static_cast<T>(coeffs[ORDER]);
      for (std::size_t k = 0; k < ORDER; ++k) {
        next_val += coeffs[k] * arr[i - 1 - k];
      }
      arr[i] = next_val;
    }
  }
  return arr;
}

// Functor con memoización híbrida:
// 1. Tabla estática constexpr para los primeros 10 * ORDER valores (coste cero en ejecución).
// 2. Cache dinámica con std::vector para cualquier valor n >= 10 * ORDER.
template <auto coeffs, auto initvals,
          std::size_t PRECOMPUTED_COUNT = (initvals.size() == 0 ? 10 : 10 * initvals.size())>
  requires(coeffs.size() == initvals.size() + 1) &&
          std::same_as<typename decltype(coeffs)::value_type,
                       typename decltype(initvals)::value_type> &&
          Arithmetic<typename decltype(coeffs)::value_type>
class MemoizedSequence {
public:
  using value_type = typename decltype(coeffs)::value_type;
  static constexpr std::size_t ORDER = initvals.size();
  static constexpr std::size_t PRECOMPUTED_SIZE = PRECOMPUTED_COUNT;

private:
  // Tabla precomputada 100% en tiempo de compilación
  static constexpr auto compile_time_cache_ =
      precompute_sequence_array<coeffs, initvals, PRECOMPUTED_SIZE>();

  // Cache dinámica para términos n >= PRECOMPUTED_SIZE
  std::vector<value_type> dynamic_cache_;

public:
  constexpr MemoizedSequence() = default;

  // Consulta el término n-ésimo (memoizado)
  value_type operator()(std::size_t n) {
    // 1. Si está en la tabla precomputada en compilación: O(1) directo sin asignaciones
    if (n < PRECOMPUTED_SIZE) {
      return compile_time_cache_[n];
    }

    if constexpr (ORDER == 0) {
      return coeffs[0];
    }

    // 2. Si ya está en la cache dinámica: O(1)
    const std::size_t dynamic_idx = n - PRECOMPUTED_SIZE;
    if (dynamic_idx < dynamic_cache_.size()) {
      return dynamic_cache_[dynamic_idx];
    }

    // 3. Extender la cache dinámica solo para los términos nuevos
    const std::size_t current_total = PRECOMPUTED_SIZE + dynamic_cache_.size();
    for (std::size_t i = current_total; i <= n; ++i) {
      value_type next_val = static_cast<value_type>(coeffs[ORDER]);
      for (std::size_t k = 0; k < ORDER; ++k) {
        const std::size_t prev_idx = i - 1 - k;
        const value_type prev_term =
            (prev_idx < PRECOMPUTED_SIZE)
                ? compile_time_cache_[prev_idx]
                : dynamic_cache_[prev_idx - PRECOMPUTED_SIZE];
        next_val += coeffs[k] * prev_term;
      }
      dynamic_cache_.push_back(next_val);
    }

    return dynamic_cache_.back();
  }

  // Devuelve una lista con los primeros 'count' términos
  std::vector<value_type> get_list(std::size_t count) {
    if (count == 0) return {};
    (*this)(count - 1); // asegura que estén calculados hasta count - 1

    std::vector<value_type> result;
    result.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
      result.push_back((*this)(i));
    }
    return result;
  }

  // Acceso a la tabla precomputada constexpr
  static constexpr const auto& precomputed_table() noexcept {
    return compile_time_cache_;
  }

  // Número total de términos cacheados (estáticos + dinámicos)
  std::size_t total_cached() const noexcept {
    return PRECOMPUTED_SIZE + dynamic_cache_.size();
  }
};

/**
 * @brief Generador con memoización dinámica para cualquier tipo aritmético (enteros, reales, complejos).
 * Útil cuando los coeficientes no se pasan por plantilla NTTP o son tipos no estructurales como std::complex.
 */
template <Arithmetic T>
class DynamicMemoizedSequence {
public:
  using value_type = T;

private:
  std::vector<T> coeffs_;
  std::vector<T> initvals_;
  std::vector<T> cache_;

public:
  DynamicMemoizedSequence(std::vector<T> coeffs, std::vector<T> initvals)
      : coeffs_(std::move(coeffs)), initvals_(std::move(initvals)), cache_(initvals_) {}

  DynamicMemoizedSequence(std::initializer_list<T> coeffs, std::initializer_list<T> initvals)
      : coeffs_(coeffs), initvals_(initvals), cache_(initvals_) {}

  value_type operator()(std::size_t n) {
    const std::size_t order = initvals_.size();
    if (n < cache_.size()) {
      return cache_[n];
    }
    if (order == 0) {
      return coeffs_.empty() ? T{} : coeffs_[0];
    }

    for (std::size_t i = cache_.size(); i <= n; ++i) {
      T next_val = coeffs_[order]; // término independiente
      for (std::size_t k = 0; k < order; ++k) {
        const std::size_t prev_idx = i - 1 - k;
        next_val += coeffs_[k] * cache_[prev_idx];
      }
      cache_.push_back(next_val);
    }

    return cache_[n];
  }

  std::vector<value_type> get_list(std::size_t count) {
    if (count == 0) return {};
    (*this)(count - 1);
    return std::vector<value_type>(cache_.begin(), cache_.begin() + count);
  }

  std::size_t total_cached() const noexcept {
    return cache_.size();
  }
};

} // namespace gfib

#endif // GFIB_HPP_INCLUDED
