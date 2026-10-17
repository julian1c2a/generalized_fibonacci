#ifndef GFIB_HPP_INCLUDED
#define GFIB_HPP_INCLUDED

#include <array>
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace gfib {

template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

// Sobrecarga concisa deducida (C++20)
template <auto coeffs, auto initvals, std::integral N = std::size_t>
  requires (coeffs.size() == initvals.size() + 1) &&
           std::same_as<typename decltype(coeffs)::value_type,
                        typename decltype(initvals)::value_type> &&
           Arithmetic<typename decltype(coeffs)::value_type>
constexpr auto compute_sequence(N n) noexcept {
  constexpr std::size_t ORDER = initvals.size();
  using T = typename decltype(coeffs)::value_type;
  constexpr std::size_t init_count = ORDER;

  if (n < 0) {
    return T{};
  }

  // Retornar directamente si n está en valores iniciales
  if (static_cast<std::size_t>(n) < init_count) {
    return initvals[n];
  }

  // Orden 0: función constante
  if constexpr (ORDER == 0) {
    return coeffs[0];
  }

  // Calcular iterativamente para n >= init_count
  std::vector<T> sequence(
      std::max(static_cast<std::size_t>(n + 1), init_count));

  for (size_t i = 0; i < static_cast<size_t>(init_count); ++i) {
    if (i <= static_cast<std::size_t>(n)) {
      sequence[i] = initvals[i];
    }
  }

  // Iterar desde init_count hasta n para generar términos secuenciales
  for (std::size_t i = init_count; i <= static_cast<std::size_t>(n); ++i) {
    T next_val = static_cast<T>(coeffs[ORDER]); // Término independiente

    for (size_t k = 0; k < ORDER; ++k) {
      const size_t prev_idx = static_cast<size_t>(i - 1 - k);
      next_val += coeffs[k] * sequence[prev_idx];
    }

    sequence[i] = next_val;
  }

  return sequence[n];
}

// Plantilla con ORDER explícito y tipos genéricos
template <std::size_t ORDER, Arithmetic T, std::unsigned_integral N,
          std::array<T, ORDER + 1> coeffs,
          std::array<T, ORDER> initvals>
constexpr T compute_sequence(N n) noexcept {
  return compute_sequence<coeffs, initvals, N>(n);
}

} // namespace gfib

#endif // GFIB_HPP_INCLUDED
