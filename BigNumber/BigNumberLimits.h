/**
 * @Name    : BigNumberLimits.h
 * @Date    : 2020年4月6日 下午7:41:04
 * @Author  : happe
 * @brief   : numeric_limits overloading
 */

#pragma once

#include "BigNumber.h"
#include <limits>

namespace std {
	using BigMath::BigNumber;
/// numeric_limits<float> specialization.

	template <size_t WordSize>
	struct numeric_limits<BigNumber<WordSize>> : public _Num_int_base {

			static constexpr bool is_specialized = true;

			static constexpr BigNumber<WordSize>(min)() noexcept {
				return BigNumber<WordSize>::minValue();
			}

			static constexpr BigNumber<WordSize>(max)() noexcept {
				return BigNumber<WordSize>::maxValue();
			}

#if __cplusplus >= 201103L
			static constexpr BigNumber<WordSize> lowest() noexcept {
				return min();
			}
#endif

			static constexpr int digits = (WordSize * 32);
			static constexpr int digits10 = ((WordSize * 32) * 643L / 2136);
#if __cplusplus >= 201103L
			static constexpr int max_digits10 = 0;
#endif
			static constexpr bool is_signed = true;
			static constexpr bool is_integer = true;
			static constexpr bool is_exact = true;
			static constexpr int radix = 2;

			static constexpr BigNumber<WordSize> epsilon() noexcept {
				return 0;
			}

			static constexpr BigNumber<WordSize> round_error() noexcept {
				return 0;
			}

			static constexpr int min_exponent = 0;
			static constexpr int min_exponent10 = 0;
			static constexpr int max_exponent = 0;
			static constexpr int max_exponent10 = 0;

			static constexpr bool has_infinity = false;
			static constexpr bool has_quiet_NaN = false;
			static constexpr bool has_signaling_NaN = false;
			static constexpr std::float_denorm_style has_denorm = std::denorm_absent;
			static constexpr bool has_denorm_loss = false;

			static constexpr BigNumber<WordSize> infinity() noexcept {
				return 0;
			}

			static constexpr BigNumber<WordSize> quiet_NaN() noexcept {
				return 0;
			}

			static constexpr BigNumber<WordSize> signaling_NaN() noexcept {
				return 0;
			}

			static constexpr BigNumber<WordSize> denorm_min() noexcept {
				return 0;
			}

			static constexpr bool is_iec559 = false;
			static constexpr bool is_bounded = true;
			static constexpr bool is_modulo = false;

			static constexpr bool traps = true;
			static constexpr bool tinyness_before = false;
			static constexpr std::float_round_style round_style = std::round_toward_zero;
	};

	/*template <size_t WordSize>
	struct __is_integral_helper<BigNumber<WordSize>> : public true_type {
	};*/
}

