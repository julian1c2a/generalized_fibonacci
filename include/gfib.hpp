#ifndef GFIB_HPP_INCLUDED
#define GFIB_HPP_INCLUDED

#include <type_traits>
#include <concepts>
#include <array>
#include <vector>
#include <cstdint>

namespace gfib {

template<typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

// Plantilla principal con ORDER, n como tipo uint gen�rico y tipo de datos T
template<std::size_t ORDER, Arithmetic T, std::unsigned_integral N, std::array<T,ORDER+1> coefficients, std::array<T,ORDER> initial_values>
constexpr T compute_sequence(N n) noexcept{
    constexpr std::size_t init_count = ORDER;

    // Retornar directamente si n está en valores iniciales
    if (n < init_count) {
        return initial_values[n];
    }

    // Orden 0: función constante
    if constexpr (ORDER == 0) {
        return coefficients[0];
    }

    // Calcular iterativamente para n >= init_count
    std::vector<T> sequence(std::max(static_cast<std::size_t>(n + 1), init_count));

    for (size_t i = 0; i < static_cast<size_t>(init_count); ++i) {
        if (static_cast<N>(i) <= n) {
            sequence[i] = initial_values[i];
        }
    }

    // Iterar desde init_count hasta n para generar términos secuenciales
    for (N i = init_count; i <= n; ++i) {
        T next_val = static_cast<T>(coefficients[ORDER]); // Término independiente

        for (size_t k = 0; k < ORDER; ++k) {
            const size_t prev_idx = static_cast<size_t>(n - i + k);
            next_val += coefficients[k] * sequence[prev_idx];
        }

        sequence[i] = next_val;
    }

    return sequence[n];
}

} // namespace gfib


#endif // GFIB_HPP_INCLUDED
