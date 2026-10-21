#ifndef SPEC_FUNCTS_HPP_INCLUDED
#define SPEC_FUNCTS_HPP_INCLUDED

#include "type_traits.hpp"
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
// Constantes matemáticas con 50 dígitos de precisión decimal (exactas para float, double,
// long double de 80 bits x87 y 128 bits IEEE binary128).
inline constexpr long double pi = 3.14159265358979323846264338327950288419716939937511L;
inline constexpr long double two_pi = 6.28318530717958647692528676655900576839433879875021L;
inline constexpr long double half_pi = 1.57079632679489661923132169163975144209858469968755L;
inline constexpr long double inv_pi = 0.31830988618379067153776752674502872406891929148091L;
inline constexpr long double e = 2.71828182845904523536028747135266249775724709369996L;
inline constexpr long double sqrt_2pi = 2.50662827463100050241576528481104525300698674060994L;
inline constexpr long double sqrt_half_pi = 1.25331413731550025120788264240552262650349337030497L;
inline constexpr long double sqrt2 = 1.41421356237309504880168872420969807856967187537695L;
inline constexpr long double inv_sqrt2 = 0.70710678118654752440084436210484903928483593768847L;
inline constexpr long double sqrt3 = 1.73205080756887729352744634150587236694280525381038L;
inline constexpr long double phi = 1.61803398874989484820458683436563811772030917980576L;
inline constexpr long double euler_gamma = 0.5772156649015328606065120900824024310421593359399235988058L;
inline constexpr long double egamma = euler_gamma;
inline constexpr long double euler_mascheroni = euler_gamma;

// --- Constantes Logarítmicas Naturales (ln_2 .. ln_10) ---
inline constexpr long double ln_2 = 0.69314718055994530941723212145817656807550013436026L;
inline constexpr long double ln_3 = 1.09861228866810969139524523692252570464749055782275L;
inline constexpr long double ln_4 = 1.38629436111989061883446424291635313615100026872051L;
inline constexpr long double ln_5 = 1.60943791243410037460075933322618763952560135426852L;
inline constexpr long double ln_6 = 1.79175946922805500081247735838070227272299069218300L;
inline constexpr long double ln_7 = 1.94591014905531330510535274344317972963708472958186L;
inline constexpr long double ln_8 = 2.07944154167983592825169636437452970422650040308077L;
inline constexpr long double ln_9 = 2.19722457733621938279049047384505140929498111564550L;
inline constexpr long double ln_10 = 2.30258509299404568401799145468436420760110148862877L;
inline constexpr long double ln2 = ln_2;
inline constexpr long double ln10 = ln_10;
inline constexpr long double inv_ln2 = 1.44269504088896340735992468100189213742664595415299L;
inline constexpr long double inv_ln_2 = inv_ln2;
inline constexpr long double inv_ln10 = 0.43429448190325182765112891891660508229439700580367L;
inline constexpr long double inv_ln_10 = inv_ln10;

// --- Constantes Logarítmicas Decimales Base 10 (log10_2 .. log10_20) ---
inline constexpr long double log10_2 = 0.30102999566398119521373889472449302676818988146211L;
inline constexpr long double log10_3 = 0.47712125471966243729502790325511530920012886419070L;
inline constexpr long double log10_4 = 0.60205999132796239042747778944898605353637976292422L;
inline constexpr long double log10_5 = 0.69897000433601880478626110527550697323181011853789L;
inline constexpr long double log10_6 = 0.77815125038364363250876679797960833596831874565280L;
inline constexpr long double log10_7 = 0.84509804001425683071221625859263619348357239632397L;
inline constexpr long double log10_8 = 0.90308998699194358564121668417347908030456964438633L;
inline constexpr long double log10_9 = 0.95424250943932487459005580651023061840025772838139L;
inline constexpr long double log10_10 = 1.0L;
inline constexpr long double log10_11 = 1.04139268515822504075019997124302424170670219046645L;
inline constexpr long double log10_12 = 1.07918124604762482772250569270410136273650862711491L;
inline constexpr long double log10_13 = 1.11394335230683676920650515794232843082972918838707L;
inline constexpr long double log10_14 = 1.14612803567823802592595515331712922025176227778607L;
inline constexpr long double log10_15 = 1.17609125905568124208128900853062228243193898272859L;
inline constexpr long double log10_16 = 1.20411998265592478085495557889797210707275952584843L;
inline constexpr long double log10_17 = 1.23044892137827392854016989432833703000756737842505L;
inline constexpr long double log10_18 = 1.25527250510330606980379470123472364516844760984350L;
inline constexpr long double log10_19 = 1.27875360095282896153633347575692931795112933739450L;
inline constexpr long double log10_20 = 1.30102999566398119521373889472449302676818988146211L;

// --- Constantes Logarítmicas Binarias Base 2 (log2_2 .. log2_10) ---
inline constexpr long double log2_2 = 1.0L;
inline constexpr long double log2_3 = 1.58496250072115618145373894394781650875981440769248L;
inline constexpr long double log2_4 = 2.0L;
inline constexpr long double log2_5 = 2.32192809488736234787031942948939017586483139302458L;
inline constexpr long double log2_6 = 2.58496250072115618145373894394781650875981440769248L;
inline constexpr long double log2_7 = 2.80735492205760410744196931723183080864102662596614L;
inline constexpr long double log2_8 = 3.0L;
inline constexpr long double log2_9 = 3.16992500144231236290747788789563301751962881538496L;
inline constexpr long double log2_10 = 3.32192809488736234787031942948939017586483139302458L;
} // namespace constants

// Traits comunes importados desde type_traits.hpp
using traits::complex;
using traits::is_complex;
using traits::is_complex_v;
using traits::ComplexNumber;
using traits::ComplexLike;
using traits::complex_value_t;
using traits::to_floating_point_t;

/* ==========================================================================
 * UTILIDADES BÁSICAS (floor, ceil, trunc, round, potencia entera, escalado)
 * ========================================================================== */

// Suelo (floor) para reales (entero)
template <std::floating_point T> constexpr int64_t floor_int(T x) noexcept {
  auto i = static_cast<int64_t>(x);
  if (static_cast<T>(i) > x) {
    --i;
  }
  return i;
}

// Techo (ceil) para reales (entero)
template <std::floating_point T> constexpr int64_t ceil_int(T x) noexcept {
  auto i = static_cast<int64_t>(x);
  if (static_cast<T>(i) < x) {
    ++i;
  }
  return i;
}

// Truncamiento para reales (hacia cero, entero)
template <std::floating_point T> constexpr int64_t trunc_int(T x) noexcept {
  return static_cast<int64_t>(x);
}

// Redondeo al entero más cercano (entero)
template <std::floating_point T> constexpr int64_t round_int(T x) noexcept {
  if (x >= T{0}) {
    return floor_int(x + T{0.5});
  } else {
    return ceil_int(x - T{0.5});
  }
}

// Potencia entera rápida por exponenciación binaria: base^n
template <typename T> constexpr T int_pow(T base, int64_t exp) noexcept {
  if (exp == 0)
    return T{1};
  if (exp < 0)
    return T{1} / int_pow(base, -exp);

  T result{1};
  T cur = base;
  while (exp > 0) {
    if (exp & 1)
      result = result * cur;
    cur = cur * cur;
    exp >>= 1;
  }
  return result;
}

// Multiplicación rápida por 2^k: x * 2^k
template <std::floating_point T>
constexpr T scale_by_2_pow(T x, int64_t k) noexcept {
  if (k == 0 || x == T{0})
    return x;
  if (k > 0) {
    while (k >= 30) {
      x *= static_cast<T>(1 << 30);
      k -= 30;
    }
    return x * static_cast<T>(int64_t{1} << k);
  } else {
    int64_t neg_k = -k;
    while (neg_k >= 30) {
      x /= static_cast<T>(1 << 30);
      neg_k -= 30;
    }
    return x / static_cast<T>(int64_t{1} << neg_k);
  }
}

/* ==========================================================================
 * REDONDEOS OPTIMIZADOS (ceil, floor, trunc, round) Y PARTE FRACCIONARIA (frac)
 * ========================================================================== */

/**
 * @brief Techo (ceil) optimizado en alta precisión para reales.
 * Optimización:
 * 1. Detección inmediata de NaN.
 * 2. Camino rápido O(1): si |x| >= 2^(mantissa_bits) (2^52 en double, 2^23 en float),
 *    el número ya no tiene bits fraccionarios representables en formato IEEE-754
 *    o es infinito, por lo que se retorna x directamente, evitando desbordamientos
 *    de conversión entera y llamadas a instrucciones de redondeo.
 * 3. Para |x| < 2^(mantissa_bits), cabe exactamente en int64_t sin desbordar.
 */
template <std::floating_point T> constexpr T ceil_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();

  const T no_fraction_limit =
      scale_by_2_pow(T{1}, std::numeric_limits<T>::digits - 1);
  if (x >= no_fraction_limit || x <= -no_fraction_limit)
    return x;

  auto i = static_cast<int64_t>(x);
  if (static_cast<T>(i) < x) {
    ++i;
  }
  // Conservar signo de -0.0 para x in (-1.0, 0.0]
  if (i == 0 && x < T{0})
    return -T{0};
  return static_cast<T>(i);
}

/**
 * @brief Suelo (floor) optimizado en alta precisión para reales.
 */
template <std::floating_point T> constexpr T floor_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();

  const T no_fraction_limit =
      scale_by_2_pow(T{1}, std::numeric_limits<T>::digits - 1);
  if (x >= no_fraction_limit || x <= -no_fraction_limit)
    return x;

  auto i = static_cast<int64_t>(x);
  if (static_cast<T>(i) > x) {
    --i;
  }
  return static_cast<T>(i);
}

/**
 * @brief Truncamiento (hacia cero) optimizado para reales.
 */
template <std::floating_point T> constexpr T trunc_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();

  const T no_fraction_limit =
      scale_by_2_pow(T{1}, std::numeric_limits<T>::digits - 1);
  if (x >= no_fraction_limit || x <= -no_fraction_limit)
    return x;

  return static_cast<T>(static_cast<int64_t>(x));
}

/**
 * @brief Redondeo al entero más cercano simétrico respecto a cero.
 */
template <std::floating_point T> constexpr T round_real(T x) noexcept {
  if (x >= T{0}) {
    return floor_real(x + static_cast<T>(0.5));
  } else {
    return ceil_real(x - static_cast<T>(0.5));
  }
}

// Modos de cálculo de la parte fraccionaria / resto
enum class FracMode {
  Defect, // Por defecto: x - floor(x), en [0, 1)
  Excess, // Por exceso: ceil(x) - x, distancia al entero superior, en [0, 1)
  Round,  // Respecto al redondeo: x - round(x), en [-0.5, 0.5]
  Trunc   // Truncado hacia cero: x - trunc(x), en (-1, 1)
};

// Dirección del redondeo
enum class RoundingDirection {
  Exact,  // Sin resto (x es entero exacto)
  Defect, // Redondeo por defecto (x > round(x), resto positivo sobrante)
  Excess  // Redondeo por exceso (x < round(x), resto negativo excedente)
};

// Descomposición detallada del redondeo y partes fraccionarias
template <std::floating_point T> struct RoundingDecomposition {
  T value;                     // Valor original x
  T rounded;                   // Entero redondeado (round)
  T floor_val;                 // Entero por defecto (floor)
  T ceil_val;                  // Entero por exceso (ceil)
  T remainder;                 // Resto del redondeo: x - rounded en [-0.5, 0.5]
  T defect;                    // Fracción por defecto: x - floor en [0, 1)
  T excess;                    // Fracción por exceso: ceil - x en [0, 1)
  RoundingDirection direction; // Dirección del redondeo
};

template <std::floating_point T>
constexpr T frac_defect_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  const T no_fraction_limit =
      scale_by_2_pow(T{1}, std::numeric_limits<T>::digits - 1);
  if (x >= no_fraction_limit || x <= -no_fraction_limit)
    return T{0};

  T fl = floor_real(x);
  T res = x - fl;
  if (res >= static_cast<T>(1) || res < T{0})
    return T{0};
  return res;
}

template <std::floating_point T>
constexpr T frac_excess_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  const T no_fraction_limit =
      scale_by_2_pow(T{1}, std::numeric_limits<T>::digits - 1);
  if (x >= no_fraction_limit || x <= -no_fraction_limit)
    return T{0};

  T cl = ceil_real(x);
  T res = cl - x;
  if (res >= static_cast<T>(1) || res < T{0})
    return T{0};
  return res;
}

template <std::floating_point T>
constexpr T frac_round_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  const T no_fraction_limit =
      scale_by_2_pow(T{1}, std::numeric_limits<T>::digits - 1);
  if (x >= no_fraction_limit || x <= -no_fraction_limit)
    return T{0};

  return x - round_real(x);
}

template <std::floating_point T>
constexpr T frac_trunc_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  const T no_fraction_limit =
      scale_by_2_pow(T{1}, std::numeric_limits<T>::digits - 1);
  if (x >= no_fraction_limit || x <= -no_fraction_limit)
    return T{0};

  return x - trunc_real(x);
}

template <std::floating_point T>
constexpr RoundingDecomposition<T> decompose_rounding(T x) noexcept {
  RoundingDecomposition<T> res{};
  res.value = x;
  res.rounded = round_real(x);
  res.floor_val = floor_real(x);
  res.ceil_val = ceil_real(x);
  res.defect = frac_defect_real(x);
  res.excess = frac_excess_real(x);
  res.remainder = frac_round_real(x);

  if (res.remainder == T{0}) {
    res.direction = RoundingDirection::Exact;
  } else if (res.remainder > T{0}) {
    res.direction = RoundingDirection::Defect;
  } else {
    res.direction = RoundingDirection::Excess;
  }
  return res;
}

// Wrappers genéricos (reales y complejos)
template <std::floating_point FloatFallback = double, typename T>
constexpr auto ceil(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return complex<ValT>(ceil_real(x.real()), ceil_real(x.imag()));
    } else {
      return complex<FloatFallback>(ceil_real(static_cast<FloatFallback>(x.real())),
                                    ceil_real(static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return ceil_real(x);
  } else {
    return ceil_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto floor(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return complex<ValT>(floor_real(x.real()), floor_real(x.imag()));
    } else {
      return complex<FloatFallback>(floor_real(static_cast<FloatFallback>(x.real())),
                                    floor_real(static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return floor_real(x);
  } else {
    return floor_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto trunc(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return complex<ValT>(trunc_real(x.real()), trunc_real(x.imag()));
    } else {
      return complex<FloatFallback>(trunc_real(static_cast<FloatFallback>(x.real())),
                                    trunc_real(static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return trunc_real(x);
  } else {
    return trunc_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto round(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return complex<ValT>(round_real(x.real()), round_real(x.imag()));
    } else {
      return complex<FloatFallback>(round_real(static_cast<FloatFallback>(x.real())),
                                    round_real(static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return round_real(x);
  } else {
    return round_real(static_cast<FloatFallback>(x));
  }
}

// Parte fraccionaria configurable
template <std::floating_point FloatFallback = double, typename T>
constexpr auto frac(const T &x, FracMode mode = FracMode::Defect) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return complex<ValT>(frac(x.real(), mode), frac(x.imag(), mode));
    } else {
      return complex<FloatFallback>(frac(static_cast<FloatFallback>(x.real()), mode),
                                    frac(static_cast<FloatFallback>(x.imag()), mode));
    }
  } else if constexpr (std::floating_point<T>) {
    switch (mode) {
    case FracMode::Defect:
      return frac_defect_real(x);
    case FracMode::Excess:
      return frac_excess_real(x);
    case FracMode::Round:
      return frac_round_real(x);
    case FracMode::Trunc:
      return frac_trunc_real(x);
    default:
      return frac_defect_real(x);
    }
  } else {
    return FloatFallback{0};
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto frac_defect(const T &x) noexcept {
  return frac<FloatFallback>(x, FracMode::Defect);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto frac_excess(const T &x) noexcept {
  return frac<FloatFallback>(x, FracMode::Excess);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto frac_round(const T &x) noexcept {
  return frac<FloatFallback>(x, FracMode::Round);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto frac_trunc(const T &x) noexcept {
  return frac<FloatFallback>(x, FracMode::Trunc);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto round_remainder(const T &x) noexcept {
  return frac<FloatFallback>(x, FracMode::Round);
}

/* ==========================================================================
 * RAÍZ CUADRADA (sqrt) EN ALTA PRECISIÓN (Sin cmath)
 * ========================================================================== */

/**
 * @brief Raíz cuadrada real sqrt(x) con reducción de rango y método de Newton-Raphson.
 */
template <std::floating_point T> constexpr T sqrt_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x < T{0})
    return std::numeric_limits<T>::quiet_NaN();
  if (x == T{0})
    return T{0};
  if (x > std::numeric_limits<T>::max())
    return std::numeric_limits<T>::infinity();

  // Reducción de rango x = 4^k * m con m en [0.5, 2.0]
  int64_t k = 0;
  while (x > static_cast<T>(1e16)) {
    x *= static_cast<T>(1.0 / 4294967296.0 / 4294967296.0); // 4^-32
    k += 32;
  }
  while (x < static_cast<T>(1e-16)) {
    x *= static_cast<T>(4294967296.0 * 4294967296.0); // 4^32
    k -= 32;
  }
  while (x > static_cast<T>(2.0)) {
    x *= static_cast<T>(0.25);
    ++k;
  }
  while (x < static_cast<T>(0.5)) {
    x *= static_cast<T>(4.0);
    --k;
  }

  // Aproximación inicial lineal para m in [0.5, 2.0]
  T s = static_cast<T>(0.5) * x + static_cast<T>(0.5);
  // Iteraciones de Newton-Raphson para doblar precisión por paso
  for (int i = 0; i < 6; ++i) {
    s = static_cast<T>(0.5) * (s + x / s);
  }

  return scale_by_2_pow(s, k);
}

// Valor absoluto genérico (reales y complejos)
template <typename T> constexpr auto abs_val(T x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    ValT u = x.real() < ValT{0} ? -x.real() : x.real();
    ValT v = x.imag() < ValT{0} ? -x.imag() : x.imag();
    if (u == ValT{0})
      return v;
    if (v == ValT{0})
      return u;
    if (u > v) {
      ValT q = v / u;
      return u * sqrt_real(ValT{1} + q * q);
    } else {
      ValT q = u / v;
      return v * sqrt_real(ValT{1} + q * q);
    }
  } else {
    return x < T{0} ? -x : x;
  }
}

/**
 * @brief Raíz cuadrada de números complejos complex<T>.
 */
template <std::floating_point T = double>
constexpr complex<T> sqrt_complex(const complex<T> &z) noexcept {
  T u = z.real();
  T v = z.imag();
  if (u == T{0} && v == T{0})
    return z;

  T au = u < T{0} ? -u : u;
  T av = v < T{0} ? -v : v;
  T mag;
  if (au == T{0}) {
    mag = av;
  } else if (av == T{0}) {
    mag = au;
  } else if (au > av) {
    T q = av / au;
    mag = au * sqrt_real(T{1} + q * q);
  } else {
    T q = au / av;
    mag = av * sqrt_real(T{1} + q * q);
  }

  T real_part;
  T imag_part;
  if (u >= T{0}) {
    real_part = sqrt_real(static_cast<T>(0.5) * (mag + u));
    imag_part = v / (static_cast<T>(2) * real_part);
  } else {
    imag_part = sqrt_real(static_cast<T>(0.5) * (mag - u));
    if (v < T{0})
      imag_part = -imag_part;
    real_part = v / (static_cast<T>(2) * imag_part);
  }
  return complex<T>(real_part, imag_part);
}

/**
 * @brief Raíz cuadrada genérica: sqrt(x)
 */
template <std::floating_point FloatFallback = double, typename T>
constexpr auto sqrt(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return sqrt_complex(x);
    } else {
      return sqrt_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                 static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return sqrt_real(x);
  } else {
    return sqrt_real(static_cast<FloatFallback>(x));
  }
}

/* ==========================================================================
 * ARCOTANGENTE REAL (atan, atan2) AUXILIAR
 * ========================================================================== */

namespace detail {

template <std::floating_point T> constexpr T atan_taylor_small(T z) noexcept {
  T term = z;
  T sum = z;
  const T z2 = z * z;
  for (int i = 1; i <= 12; ++i) {
    term = -term * z2;
    T add = term / static_cast<T>(2 * i + 1);
    sum += add;
    if (add < static_cast<T>(1e-19) && add > static_cast<T>(-1e-19))
      break;
  }
  return sum;
}

} // namespace detail

template <std::floating_point T> constexpr T atan_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x == T{0})
    return T{0};

  bool neg = (x < T{0});
  T ax = neg ? -x : x;

  T res;
  if (ax > static_cast<T>(1)) {
    // atan(x) = pi/2 - atan(1/x)
    T inv_x = static_cast<T>(1) / ax;
    T y1 = inv_x /
           (static_cast<T>(1) + sqrt_real(static_cast<T>(1) + inv_x * inv_x));
    T y2 = y1 / (static_cast<T>(1) + sqrt_real(static_cast<T>(1) + y1 * y1));
    res = static_cast<T>(constants::half_pi) -
          static_cast<T>(4) * detail::atan_taylor_small(y2);
  } else {
    // Reducción doble de ángulo medio: atan(x) = 4 * atan(y2)
    T y1 = ax / (static_cast<T>(1) + sqrt_real(static_cast<T>(1) + ax * ax));
    T y2 = y1 / (static_cast<T>(1) + sqrt_real(static_cast<T>(1) + y1 * y1));
    res = static_cast<T>(4) * detail::atan_taylor_small(y2);
  }

  return neg ? -res : res;
}

template <std::floating_point T> constexpr T atan2_real(T y, T x) noexcept {
  if (y != y || x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x > T{0}) {
    return atan_real(y / x);
  } else if (x < T{0}) {
    if (y >= T{0}) {
      return atan_real(y / x) + static_cast<T>(constants::pi);
    } else {
      return atan_real(y / x) - static_cast<T>(constants::pi);
    }
  } else {
    if (y > T{0})
      return static_cast<T>(constants::half_pi);
    if (y < T{0})
      return -static_cast<T>(constants::half_pi);
    return T{0};
  }
}

/* ==========================================================================
 * EXPONENCIAL NATURAL (exp) Y DE CUALQUIER BASE (exp_base, pow)
 * ========================================================================== */

template <std::floating_point T> constexpr T exp_real(T x) noexcept {
  if (x == T{0})
    return T{1};
  if (x < T{-708})
    return T{0}; // Underflow para double IEEE-754
  if (x > T{709})
    return std::numeric_limits<T>::infinity();

  // 1. Reducción de rango: x = k * ln(2) + r
  const int64_t k = round_int(x * static_cast<T>(constants::inv_ln2));
  const T r = x - static_cast<T>(k) * static_cast<T>(constants::ln2);

  // 2. Serie de Taylor de e^r: 1 + r + r^2/2! + ...
  T term = T{1};
  T sum = T{1};
  for (int i = 1; i <= 16; ++i) {
    term *= r / static_cast<T>(i);
    sum += term;
    if (term < T{1e-18} && term > T{-1e-18})
      break;
  }

  // 3. Multiplicar por 2^k
  return scale_by_2_pow(sum, k);
}

/* ==========================================================================
 * LOGARITMO NATURAL (ln) Y EN CUALQUIER BASE (log_base)
 * ========================================================================== */

template <std::floating_point T> constexpr T log_real(T x) noexcept {
  if (x <= T{0}) {
    if (x == T{0})
      return -std::numeric_limits<T>::infinity();
    return std::numeric_limits<T>::quiet_NaN();
  }
  if (x == T{1})
    return T{0};

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
    if (add < T{1e-18} && add > T{-1e-18})
      break;
  }
  const T ln_m = T{2} * sum;

  // 4. ln(x) = k * ln(2) + ln(m)
  return static_cast<T>(k) * static_cast<T>(constants::ln2) + ln_m;
}

template <std::floating_point T = double>
constexpr complex<T> log_complex(const complex<T> &z) noexcept {
  T u = z.real();
  T v = z.imag();
  T au = u < T{0} ? -u : u;
  T av = v < T{0} ? -v : v;
  T mag;
  if (au == T{0}) {
    mag = av;
  } else if (av == T{0}) {
    mag = au;
  } else if (au > av) {
    T q = av / au;
    mag = au * sqrt_real(T{1} + q * q);
  } else {
    T q = au / av;
    mag = av * sqrt_real(T{1} + q * q);
  }
  T theta = atan2_real(v, u);
  return complex<T>(log_real(mag), theta);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto log(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return log_complex(x);
    } else {
      return log_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return log_real(x);
  } else {
    return log_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename BaseT, typename ExpT>
constexpr auto pow(const BaseT &base, const ExpT &exponent) noexcept {
  using CommonFloat = std::conditional_t<
      std::is_floating_point_v<std::common_type_t<BaseT, ExpT>>,
      std::common_type_t<BaseT, ExpT>, FloatFallback>;
  if (base == BaseT{0}) {
    if (exponent == ExpT{0})
      return CommonFloat{1};
    if (exponent > ExpT{0})
      return CommonFloat{0};
    return std::numeric_limits<CommonFloat>::infinity();
  }
  if (base < BaseT{0}) {
    if constexpr (std::integral<ExpT>) {
      auto p = int_pow(base, exponent);
      return static_cast<CommonFloat>(p);
    } else {
      return std::numeric_limits<CommonFloat>::quiet_NaN();
    }
  }
  return exp_real(static_cast<CommonFloat>(exponent) *
                  log_real(static_cast<CommonFloat>(base)));
}

template <std::floating_point FloatFallback = double, typename BaseT, typename ExpT>
constexpr auto exp_base(const BaseT &base, const ExpT &x) noexcept {
  return pow<FloatFallback>(base, x);
}

template <std::floating_point FloatFallback = double, typename BaseT, typename ArgT>
constexpr auto log_base(const BaseT &base, const ArgT &x) noexcept {
  using CommonFloat = std::conditional_t<
      std::is_floating_point_v<std::common_type_t<BaseT, ArgT>>,
      std::common_type_t<BaseT, ArgT>, FloatFallback>;
  return log(static_cast<CommonFloat>(x)) / log(static_cast<CommonFloat>(base));
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto log10(const T &x) noexcept {
  return log(x) / static_cast<FloatFallback>(constants::ln10);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto log2(const T &x) noexcept {
  return log(x) * static_cast<FloatFallback>(constants::inv_ln2);
}

/* ==========================================================================
 * FUNCIONES TRIGONOMÉTRICAS (sin, cos, tan, cot)
 * ========================================================================== */

namespace detail {

template <std::floating_point T>
constexpr T sin_taylor_small(T r) noexcept {
  T term = r;
  T sum = r;
  const T r2 = r * r;
  for (int i = 1; i <= 10; ++i) {
    term = -term * r2 / static_cast<T>((2 * i) * (2 * i + 1));
    sum += term;
    if (term < static_cast<T>(1e-19) && term > static_cast<T>(-1e-19))
      break;
  }
  return sum;
}

template <std::floating_point T>
constexpr T cos_taylor_small(T r) noexcept {
  T term = static_cast<T>(1);
  T sum = static_cast<T>(1);
  const T r2 = r * r;
  for (int i = 1; i <= 10; ++i) {
    term = -term * r2 / static_cast<T>((2 * i - 1) * (2 * i));
    sum += term;
    if (term < static_cast<T>(1e-19) && term > static_cast<T>(-1e-19))
      break;
  }
  return sum;
}

} // namespace detail

// Reducción a [-pi, pi] mantenida por compatibilidad
template <std::floating_point T> constexpr T reduce_angle_pi(T x) noexcept {
  T k = static_cast<T>(round_int(x / static_cast<T>(constants::two_pi)));
  return x - k * static_cast<T>(constants::two_pi);
}

template <std::floating_point T> constexpr T sin_real(T x) noexcept {
  if (x != x || x > std::numeric_limits<T>::max() ||
      x < -std::numeric_limits<T>::max())
    return std::numeric_limits<T>::quiet_NaN();

  int64_t k = round_int(x / static_cast<T>(constants::half_pi));
  T r = x - static_cast<T>(k) * static_cast<T>(constants::half_pi);
  int q = static_cast<int>(k % 4);
  if (q < 0)
    q += 4;

  switch (q) {
  case 0:
    return detail::sin_taylor_small(r);
  case 1:
    return detail::cos_taylor_small(r);
  case 2:
    return -detail::sin_taylor_small(r);
  case 3:
    return -detail::cos_taylor_small(r);
  default:
    return T{0};
  }
}

template <std::floating_point T> constexpr T cos_real(T x) noexcept {
  if (x != x || x > std::numeric_limits<T>::max() ||
      x < -std::numeric_limits<T>::max())
    return std::numeric_limits<T>::quiet_NaN();

  int64_t k = round_int(x / static_cast<T>(constants::half_pi));
  T r = x - static_cast<T>(k) * static_cast<T>(constants::half_pi);
  int q = static_cast<int>(k % 4);
  if (q < 0)
    q += 4;

  switch (q) {
  case 0:
    return detail::cos_taylor_small(r);
  case 1:
    return -detail::sin_taylor_small(r);
  case 2:
    return -detail::cos_taylor_small(r);
  case 3:
    return detail::sin_taylor_small(r);
  default:
    return T{0};
  }
}

template <std::floating_point T> constexpr T tan_real(T x) noexcept {
  T c = cos_real(x);
  if (c == T{0}) {
    T s = sin_real(x);
    return s >= T{0} ? std::numeric_limits<T>::infinity()
                     : -std::numeric_limits<T>::infinity();
  }
  return sin_real(x) / c;
}

template <std::floating_point T> constexpr T cot_real(T x) noexcept {
  T s = sin_real(x);
  if (s == T{0}) {
    T c = cos_real(x);
    return c >= T{0} ? std::numeric_limits<T>::infinity()
                     : -std::numeric_limits<T>::infinity();
  }
  return cos_real(x) / s;
}

// Compatibilidad previa con sin_taylor y cos_taylor
template <std::floating_point T> constexpr T sin_taylor(T x) noexcept {
  return sin_real(x);
}

template <std::floating_point T> constexpr T cos_taylor(T x) noexcept {
  return cos_real(x);
}

/* ==========================================================================
 * FUNCIONES HIPERBÓLICAS (sinh, cosh, tanh, coth)
 * ========================================================================== */

template <std::floating_point T> constexpr T sinh_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x == T{0})
    return T{0};
  if (x > static_cast<T>(709))
    return std::numeric_limits<T>::infinity();
  if (x < static_cast<T>(-709))
    return -std::numeric_limits<T>::infinity();

  T ax = x < T{0} ? -x : x;
  if (ax < static_cast<T>(0.5)) {
    T term = x;
    T sum = x;
    const T x2 = x * x;
    for (int i = 1; i <= 8; ++i) {
      term = term * x2 / static_cast<T>((2 * i) * (2 * i + 1));
      sum += term;
      if (term < static_cast<T>(1e-19) && term > static_cast<T>(-1e-19))
        break;
    }
    return sum;
  }

  T ex = exp_real(ax);
  T res = static_cast<T>(0.5) * (ex - static_cast<T>(1) / ex);
  return x < T{0} ? -res : res;
}

template <std::floating_point T> constexpr T cosh_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  T ax = x < T{0} ? -x : x;
  if (ax > static_cast<T>(709))
    return std::numeric_limits<T>::infinity();

  if (ax < static_cast<T>(0.5)) {
    T term = static_cast<T>(1);
    T sum = static_cast<T>(1);
    const T x2 = x * x;
    for (int i = 1; i <= 8; ++i) {
      term = term * x2 / static_cast<T>((2 * i - 1) * (2 * i));
      sum += term;
      if (term < static_cast<T>(1e-19) && term > static_cast<T>(-1e-19))
        break;
    }
    return sum;
  }

  T ex = exp_real(ax);
  return static_cast<T>(0.5) * (ex + static_cast<T>(1) / ex);
}

template <std::floating_point T> constexpr T tanh_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x > static_cast<T>(20))
    return static_cast<T>(1);
  if (x < static_cast<T>(-20))
    return static_cast<T>(-1);
  return sinh_real(x) / cosh_real(x);
}

template <std::floating_point T> constexpr T coth_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x == T{0})
    return std::numeric_limits<T>::infinity();
  if (x > static_cast<T>(20))
    return static_cast<T>(1);
  if (x < static_cast<T>(-20))
    return static_cast<T>(-1);
  return cosh_real(x) / sinh_real(x);
}

/* ==========================================================================
 * TRIGONOMÉTRICAS E HIPERBÓLICAS COMPLEJAS
 * ========================================================================== */

template <std::floating_point T = double>
constexpr complex<T> exp_complex(const complex<T> &z) noexcept {
  T eu = exp_real(z.real());
  T cos_v = cos_real(z.imag());
  T sin_v = sin_real(z.imag());
  return complex<T>(eu * cos_v, eu * sin_v);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto exp(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return exp_complex(x);
    } else {
      return exp_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return exp_real(x);
  } else {
    return exp_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point T = double>
constexpr complex<T> sin_complex(const complex<T> &z) noexcept {
  T u = z.real();
  T v = z.imag();
  return complex<T>(sin_real(u) * cosh_real(v),
                    cos_real(u) * sinh_real(v));
}

template <std::floating_point T = double>
constexpr complex<T> cos_complex(const complex<T> &z) noexcept {
  T u = z.real();
  T v = z.imag();
  return complex<T>(cos_real(u) * cosh_real(v),
                    -sin_real(u) * sinh_real(v));
}

template <std::floating_point T = double>
constexpr complex<T> tan_complex(const complex<T> &z) noexcept {
  return sin_complex(z) / cos_complex(z);
}

template <std::floating_point T = double>
constexpr complex<T> cot_complex(const complex<T> &z) noexcept {
  return cos_complex(z) / sin_complex(z);
}

template <std::floating_point T = double>
constexpr complex<T> sinh_complex(const complex<T> &z) noexcept {
  T u = z.real();
  T v = z.imag();
  return complex<T>(sinh_real(u) * cos_real(v),
                    cosh_real(u) * sin_real(v));
}

template <std::floating_point T = double>
constexpr complex<T> cosh_complex(const complex<T> &z) noexcept {
  T u = z.real();
  T v = z.imag();
  return complex<T>(cosh_real(u) * cos_real(v),
                    sinh_real(u) * sin_real(v));
}

template <std::floating_point T = double>
constexpr complex<T> tanh_complex(const complex<T> &z) noexcept {
  return sinh_complex(z) / cosh_complex(z);
}

template <std::floating_point T = double>
constexpr complex<T> coth_complex(const complex<T> &z) noexcept {
  return cosh_complex(z) / sinh_complex(z);
}

/* ==========================================================================
 * WRAPPERS GENÉRICOS DE TRIGONOMÉTRICAS E HIPERBÓLICAS Y ALIASES
 * ========================================================================== */

// Seno: sin
template <std::floating_point FloatFallback = double, typename T>
constexpr auto sin(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return sin_complex(x);
    } else {
      return sin_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return sin_real(x);
  } else {
    return sin_real(static_cast<FloatFallback>(x));
  }
}

// Coseno: cos
template <std::floating_point FloatFallback = double, typename T>
constexpr auto cos(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return cos_complex(x);
    } else {
      return cos_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return cos_real(x);
  } else {
    return cos_real(static_cast<FloatFallback>(x));
  }
}

// Tangente: tan
template <std::floating_point FloatFallback = double, typename T>
constexpr auto tan(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return tan_complex(x);
    } else {
      return tan_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return tan_real(x);
  } else {
    return tan_real(static_cast<FloatFallback>(x));
  }
}

// Cotangente: cot / cotan
template <std::floating_point FloatFallback = double, typename T>
constexpr auto cot(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return cot_complex(x);
    } else {
      return cot_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return cot_real(x);
  } else {
    return cot_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto cotan(const T &x) noexcept {
  return cot<FloatFallback>(x);
}

// Seno hiperbólico: sinh
template <std::floating_point FloatFallback = double, typename T>
constexpr auto sinh(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return sinh_complex(x);
    } else {
      return sinh_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                 static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return sinh_real(x);
  } else {
    return sinh_real(static_cast<FloatFallback>(x));
  }
}

// Coseno hiperbólico: cosh
template <std::floating_point FloatFallback = double, typename T>
constexpr auto cosh(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return cosh_complex(x);
    } else {
      return cosh_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                 static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return cosh_real(x);
  } else {
    return cosh_real(static_cast<FloatFallback>(x));
  }
}

// Tangente hiperbólica: tanh
template <std::floating_point FloatFallback = double, typename T>
constexpr auto tanh(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return tanh_complex(x);
    } else {
      return tanh_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                 static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return tanh_real(x);
  } else {
    return tanh_real(static_cast<FloatFallback>(x));
  }
}

// Cotangente hiperbólica: coth / cotanh
template <std::floating_point FloatFallback = double, typename T>
constexpr auto coth(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return coth_complex(x);
    } else {
      return coth_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                 static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return coth_real(x);
  } else {
    return coth_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto cotanh(const T &x) noexcept {
  return coth<FloatFallback>(x);
}

/* ==========================================================================
 * FUNCIONES TRIGONOMÉTRICAS E HIPERBÓLICAS INVERSAS (asin, acos, atan, acot...)
 * ========================================================================== */

template <std::floating_point T> constexpr T asin_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x > static_cast<T>(1) || x < static_cast<T>(-1))
    return std::numeric_limits<T>::quiet_NaN();
  if (x == static_cast<T>(1))
    return static_cast<T>(constants::half_pi);
  if (x == static_cast<T>(-1))
    return -static_cast<T>(constants::half_pi);
  if (x == T{0})
    return T{0};

  T ax = x < T{0} ? -x : x;
  if (ax <= static_cast<T>(constants::inv_sqrt2)) {
    return atan_real(x / sqrt_real(static_cast<T>(1) - x * x));
  } else {
    T r = sqrt_real((static_cast<T>(1) - ax) * (static_cast<T>(1) + ax));
    T val = static_cast<T>(constants::half_pi) - atan_real(r / ax);
    return x < T{0} ? -val : val;
  }
}

template <std::floating_point T> constexpr T acos_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x > static_cast<T>(1) || x < static_cast<T>(-1))
    return std::numeric_limits<T>::quiet_NaN();
  if (x == static_cast<T>(1))
    return T{0};
  if (x == static_cast<T>(-1))
    return static_cast<T>(constants::pi);

  if (x > static_cast<T>(constants::inv_sqrt2)) {
    T r = sqrt_real((static_cast<T>(1) - x) * (static_cast<T>(1) + x));
    return atan_real(r / x);
  } else if (x < -static_cast<T>(constants::inv_sqrt2)) {
    T r = sqrt_real((static_cast<T>(1) + x) * (static_cast<T>(1) - x));
    return static_cast<T>(constants::pi) - atan_real(r / (-x));
  } else {
    return static_cast<T>(constants::half_pi) - asin_real(x);
  }
}

template <std::floating_point T> constexpr T acot_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  return static_cast<T>(constants::half_pi) - atan_real(x);
}

template <std::floating_point T> constexpr T asinh_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x == T{0})
    return T{0};

  bool neg = (x < T{0});
  T ax = neg ? -x : x;

  T res;
  if (ax < static_cast<T>(1e-4)) {
    T x2 = ax * ax;
    res = ax * (static_cast<T>(1) - x2 / static_cast<T>(6) +
                static_cast<T>(3) * x2 * x2 / static_cast<T>(40));
  } else if (ax > static_cast<T>(1e8)) {
    res = static_cast<T>(constants::ln2) + log_real(ax);
  } else {
    res = log_real(ax + sqrt_real(ax * ax + static_cast<T>(1)));
  }

  return neg ? -res : res;
}

template <std::floating_point T> constexpr T acosh_real(T x) noexcept {
  if (x != x || x < static_cast<T>(1))
    return std::numeric_limits<T>::quiet_NaN();
  if (x == static_cast<T>(1))
    return T{0};

  if (x > static_cast<T>(1e8)) {
    return static_cast<T>(constants::ln2) + log_real(x);
  }

  return log_real(x + sqrt_real(x - static_cast<T>(1)) *
                          sqrt_real(x + static_cast<T>(1)));
}

template <std::floating_point T> constexpr T atanh_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x > static_cast<T>(1) || x < static_cast<T>(-1))
    return std::numeric_limits<T>::quiet_NaN();
  if (x == static_cast<T>(1))
    return std::numeric_limits<T>::infinity();
  if (x == static_cast<T>(-1))
    return -std::numeric_limits<T>::infinity();
  if (x == T{0})
    return T{0};

  bool neg = (x < T{0});
  T ax = neg ? -x : x;

  T res;
  if (ax < static_cast<T>(1e-4)) {
    T x2 = ax * ax;
    res = ax * (static_cast<T>(1) + x2 / static_cast<T>(3) +
                x2 * x2 / static_cast<T>(5));
  } else {
    res = static_cast<T>(0.5) *
          log_real((static_cast<T>(1) + ax) / (static_cast<T>(1) - ax));
  }

  return neg ? -res : res;
}

template <std::floating_point T> constexpr T acoth_real(T x) noexcept {
  if (x != x)
    return std::numeric_limits<T>::quiet_NaN();
  if (x >= static_cast<T>(-1) && x <= static_cast<T>(1)) {
    if (x == static_cast<T>(1))
      return std::numeric_limits<T>::infinity();
    if (x == static_cast<T>(-1))
      return -std::numeric_limits<T>::infinity();
    return std::numeric_limits<T>::quiet_NaN();
  }
  return atanh_real(static_cast<T>(1) / x);
}

// Inversas complejas
template <std::floating_point T = double>
constexpr complex<T> asinh_complex(const complex<T> &z) noexcept {
  complex<T> one(T{1}, T{0});
  return log_complex(z + sqrt_complex(z * z + one));
}

template <std::floating_point T = double>
constexpr complex<T> acosh_complex(const complex<T> &z) noexcept {
  complex<T> one(T{1}, T{0});
  return log_complex(z + sqrt_complex(z - one) * sqrt_complex(z + one));
}

template <std::floating_point T = double>
constexpr complex<T> atanh_complex(const complex<T> &z) noexcept {
  complex<T> one(T{1}, T{0});
  return static_cast<T>(0.5) * (log_complex(one + z) - log_complex(one - z));
}

template <std::floating_point T = double>
constexpr complex<T> acoth_complex(const complex<T> &z) noexcept {
  complex<T> one(T{1}, T{0});
  return atanh_complex(one / z);
}

template <std::floating_point T = double>
constexpr complex<T> asin_complex(const complex<T> &z) noexcept {
  complex<T> i_unit(T{0}, T{1});
  return -i_unit * asinh_complex(i_unit * z);
}

template <std::floating_point T = double>
constexpr complex<T> acos_complex(const complex<T> &z) noexcept {
  complex<T> half_pi_val(static_cast<T>(constants::half_pi), T{0});
  return half_pi_val - asin_complex(z);
}

template <std::floating_point T = double>
constexpr complex<T> atan_complex(const complex<T> &z) noexcept {
  complex<T> i_unit(T{0}, T{1});
  return -i_unit * atanh_complex(i_unit * z);
}

template <std::floating_point T = double>
constexpr complex<T> acot_complex(const complex<T> &z) noexcept {
  complex<T> one(T{1}, T{0});
  return atan_complex(one / z);
}

/* ==========================================================================
 * WRAPPERS GENÉRICOS DE INVERSAS Y ALIASES
 * ========================================================================== */

// Arcoseno: asin / arcsin
template <std::floating_point FloatFallback = double, typename T>
constexpr auto asin(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return asin_complex(x);
    } else {
      return asin_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                 static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return asin_real(x);
  } else {
    return asin_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arcsin(const T &x) noexcept {
  return asin<FloatFallback>(x);
}

// Arcocoseno: acos / arccos
template <std::floating_point FloatFallback = double, typename T>
constexpr auto acos(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return acos_complex(x);
    } else {
      return acos_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                 static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return acos_real(x);
  } else {
    return acos_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arccos(const T &x) noexcept {
  return acos<FloatFallback>(x);
}

// Arcotangente: atan / arctan / atan2
template <std::floating_point FloatFallback = double, typename T>
constexpr auto atan(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return atan_complex(x);
    } else {
      return atan_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                 static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return atan_real(x);
  } else {
    return atan_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arctan(const T &x) noexcept {
  return atan<FloatFallback>(x);
}

template <std::floating_point FloatFallback = double, typename Y, typename X>
constexpr auto atan2(const Y &y, const X &x) noexcept {
  using CommonFloat = std::conditional_t<
      std::is_floating_point_v<std::common_type_t<Y, X>>,
      std::common_type_t<Y, X>, FloatFallback>;
  return atan2_real(static_cast<CommonFloat>(y), static_cast<CommonFloat>(x));
}

// Arcocotangente: acot / arccot / arcotan
template <std::floating_point FloatFallback = double, typename T>
constexpr auto acot(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return acot_complex(x);
    } else {
      return acot_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                 static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return acot_real(x);
  } else {
    return acot_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arccot(const T &x) noexcept {
  return acot<FloatFallback>(x);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arcotan(const T &x) noexcept {
  return acot<FloatFallback>(x);
}

// Arcoseno hiperbólico: asinh / arcsinh
template <std::floating_point FloatFallback = double, typename T>
constexpr auto asinh(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return asinh_complex(x);
    } else {
      return asinh_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                  static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return asinh_real(x);
  } else {
    return asinh_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arcsinh(const T &x) noexcept {
  return asinh<FloatFallback>(x);
}

// Arcocoseno hiperbólico: acosh / arccosh
template <std::floating_point FloatFallback = double, typename T>
constexpr auto acosh(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return acosh_complex(x);
    } else {
      return acosh_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                  static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return acosh_real(x);
  } else {
    return acosh_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arccosh(const T &x) noexcept {
  return acosh<FloatFallback>(x);
}

// Arcotangente hiperbólica: atanh / arctanh
template <std::floating_point FloatFallback = double, typename T>
constexpr auto atanh(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return atanh_complex(x);
    } else {
      return atanh_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                  static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return atanh_real(x);
  } else {
    return atanh_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arctanh(const T &x) noexcept {
  return atanh<FloatFallback>(x);
}

// Arcocotangente hiperbólica: acoth / arccoth / arcotanh
template <std::floating_point FloatFallback = double, typename T>
constexpr auto acoth(const T &x) noexcept {
  if constexpr (ComplexLike<T>) {
    using ValT = typename std::remove_cvref_t<T>::value_type;
    if constexpr (std::floating_point<ValT>) {
      return acoth_complex(x);
    } else {
      return acoth_complex(complex<FloatFallback>(static_cast<FloatFallback>(x.real()),
                                                  static_cast<FloatFallback>(x.imag())));
    }
  } else if constexpr (std::floating_point<T>) {
    return acoth_real(x);
  } else {
    return acoth_real(static_cast<FloatFallback>(x));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arccoth(const T &x) noexcept {
  return acoth<FloatFallback>(x);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto arcotanh(const T &x) noexcept {
  return acoth<FloatFallback>(x);
}

/* ==========================================================================
 * FUNCIÓN GAMMA DE EULER: Gamma(z) Y ln(Gamma(z))
 * ========================================================================== */

namespace detail {

// Coeficientes de Lanczos para g = 7, n = 9 (precisión de 15-16 dígitos)
inline constexpr double lanczos_g = 7.0;
inline constexpr double lanczos_c[9] = {
    0.99999999999980993, 676.5203681218851,     -1259.1392167224028,
    771.32342877765313,  -176.61502916214059,   12.507343278686905,
    -0.1385710958365926, 9.9843695780195716e-6, 1.5056327351493116e-7};

} // namespace detail

template <std::floating_point T> constexpr T gamma_real(T z) noexcept {
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
    T sin_val = sin_real(static_cast<T>(constants::pi) * z);
    return static_cast<T>(constants::pi) / (sin_val * gamma_real(T{1} - z));
  }

  // 2. Aproximación de Lanczos para z >= 0.5
  z -= T{1};
  T x = static_cast<T>(detail::lanczos_c[0]);
  for (std::size_t i = 1; i < 9; ++i) {
    x += static_cast<T>(detail::lanczos_c[i]) / (z + static_cast<T>(i));
  }

  T t = z + static_cast<T>(detail::lanczos_g) + T{0.5};
  T p = pow(t, z + T{0.5});
  return static_cast<T>(constants::sqrt_2pi) * p * exp_real(-t) * x;
}

template <std::floating_point T> constexpr T lgamma_real(T z) noexcept {
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
    return log_real(fact);
  }

  if (z < T{0.5}) {
    T sin_val = abs_val(sin_real(static_cast<T>(constants::pi) * z));
    return log_real(static_cast<T>(constants::pi)) - log_real(sin_val) -
           lgamma_real(T{1} - z);
  }

  z -= T{1};
  T x = static_cast<T>(detail::lanczos_c[0]);
  for (std::size_t i = 1; i < 9; ++i) {
    x += static_cast<T>(detail::lanczos_c[i]) / (z + static_cast<T>(i));
  }

  T t = z + static_cast<T>(detail::lanczos_g) + T{0.5};
  return T{0.5} * log_real(static_cast<T>(constants::two_pi)) +
         (z + T{0.5}) * log_real(t) - t + log_real(x);
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto gamma(const T &z) noexcept {
  if constexpr (std::floating_point<T>) {
    return gamma_real(z);
  } else {
    return gamma_real(static_cast<FloatFallback>(z));
  }
}

template <std::floating_point FloatFallback = double, typename T>
constexpr auto lgamma(const T &z) noexcept {
  if constexpr (std::floating_point<T>) {
    return lgamma_real(z);
  } else {
    return lgamma_real(static_cast<FloatFallback>(z));
  }
}

// Alias estándar para gamma de Euler (evita colisión con funciones obsoletas de C <math.h>)
template <std::floating_point FloatFallback = double, typename T>
constexpr auto tgamma(const T &z) noexcept {
  return gamma<FloatFallback>(z);
}

/* ==========================================================================
 * FUNCIÓN BETA DE EULER: B(x, y) = Gamma(x) * Gamma(y) / Gamma(x + y)
 * ========================================================================== */

template <std::floating_point FloatFallback = double, typename T, typename U>
constexpr auto beta(const T &x, const U &y) noexcept {
  using CommonFloat = std::conditional_t<
      std::is_floating_point_v<std::common_type_t<T, U>>,
      std::common_type_t<T, U>, FloatFallback>;
  CommonFloat fx = static_cast<CommonFloat>(x);
  CommonFloat fy = static_cast<CommonFloat>(y);

  if (fx > CommonFloat{0} && fx < CommonFloat{15} && fy > CommonFloat{0} &&
      fy < CommonFloat{15}) {
    return (gamma(fx) * gamma(fy)) / gamma(fx + fy);
  }

  CommonFloat log_b = lgamma(fx) + lgamma(fy) - lgamma(fx + fy);
  return exp(log_b);
}

template <std::floating_point FloatFallback = double, typename T, typename U>
constexpr auto lbeta(const T &x, const U &y) noexcept {
  using CommonFloat = std::conditional_t<
      std::is_floating_point_v<std::common_type_t<T, U>>,
      std::common_type_t<T, U>, FloatFallback>;
  CommonFloat fx = static_cast<CommonFloat>(x);
  CommonFloat fy = static_cast<CommonFloat>(y);
  return lgamma(fx) + lgamma(fy) - lgamma(fx + fy);
}

} // namespace spec_functs

#endif // SPEC_FUNCTS_HPP_INCLUDED
