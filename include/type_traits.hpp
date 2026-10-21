#ifndef GFIB_TYPE_TRAITS_HPP_INCLUDED
#define GFIB_TYPE_TRAITS_HPP_INCLUDED

#include <complex>
#include <concepts>
#include <type_traits>
#include <utility>

namespace gfib::traits {

/**
 * @brief Alias de plantilla para números complejos restringido a tipos de coma flotante.
 * Por defecto, el tipo flotante es double: complex<> o complex<double>.
 * Permite especializarse como complex<float>, complex<double>, complex<long double>, etc.
 */
template <std::floating_point T = double>
using complex = std::complex<T>;

/**
 * @brief Trait primario para identificar si un tipo es una especialización de std::complex.
 */
template <typename T>
struct is_complex : std::false_type {};

template <typename T>
struct is_complex<std::complex<T>> : std::true_type {};

template <typename T>
inline constexpr bool is_complex_v = is_complex<std::remove_cvref_t<T>>::value;

/**
 * @brief Concepto que modela tipos complejos (std::complex o alias derivados).
 */
template <typename T>
concept ComplexNumber = is_complex_v<T>;

/**
 * @brief Alias para el concepto ComplexNumber (usado en spec_functs).
 */
template <typename T>
concept ComplexLike = ComplexNumber<T>;

/**
 * @brief Extractor del tipo de valor base (componente real) de un tipo escalar o complejo.
 */
template <typename T>
struct complex_value {
  using type = std::remove_cvref_t<T>;
};

template <typename T>
struct complex_value<std::complex<T>> {
  using type = T;
};

template <typename T>
using complex_value_t = typename complex_value<std::remove_cvref_t<T>>::type;

/**
 * @brief Mapea un tipo (escalar o complejo) a su correspondiente tipo flotante de trabajo.
 * Si el tipo base ya es flotante, se preserva; de lo contrario (por ejemplo, enteros),
 * se utiliza FloatFallback (por defecto double).
 */
template <typename T, std::floating_point FloatFallback = double>
struct to_floating_point {
private:
  using Base = complex_value_t<T>;
public:
  using type = std::conditional_t<std::floating_point<Base>, Base, FloatFallback>;
};

template <typename T, std::floating_point FloatFallback = double>
using to_floating_point_t = typename to_floating_point<T, FloatFallback>::type;

/**
 * @brief Deducción natural del tipo resultante al evaluar un polinomio de coeficientes CoeffT con argumento ArgT.
 */
template <typename CoeffT, typename ArgT>
using eval_result_t = decltype(std::declval<CoeffT>() + std::declval<CoeffT>() * std::declval<ArgT>());

/**
 * @brief Concepto para tipos que admiten operaciones de semianillo (suma y multiplicación).
 * Suficiente para secuencias lineales recurrentes (secuencias de Fibonacci generalizadas).
 */
template <typename T>
concept SemiringArithmetic = std::integral<T> || std::floating_point<T> || ComplexNumber<T> ||
  requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
  };

/**
 * @brief Concepto para tipos que admiten operaciones aritméticas completas (+, -, *, /).
 * Incluye enteros, números de punto flotante, números complejos y clases numéricas personalizadas.
 */
template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T> || ComplexNumber<T> ||
  requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
  };

} // namespace gfib::traits

namespace traits = gfib::traits;

#endif // GFIB_TYPE_TRAITS_HPP_INCLUDED
