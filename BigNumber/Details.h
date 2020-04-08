/**
 * @Name    : Details.h
 * @Date    : 2020年4月7日 下午8:08:44
 * @Author  : happe
 * @brief   :
 */
#pragma once

#include <limits.h>
#include <stdint.h>

namespace BigMath {
	template <typename T>
	struct BitSize {
			BitSize() = delete;
			static constexpr auto Value = sizeof(T) * CHAR_BIT;
	};

	template <bool Condition, typename TTrue, typename TFalse>
	struct Conditional;

	template <typename TTrue, typename TFalse>
	struct Conditional<true, TTrue, TFalse> {
			using Type = TTrue;
	};

	template <typename TTrue, typename TFalse>
	struct Conditional<false, TTrue, TFalse> {
			using Type = TFalse;
	};

	template <bool Condition, typename TTrue, typename TFalse>
	using ConditionalT = typename Conditional<Condition, TTrue, TFalse >::Type;

	template <typename T, typename U>
	using LargerType = ConditionalT<(BitSize<T>::Value > BitSize<U>::Value), T, U>;

	template <typename T, typename U>
	using StrictLargerType = ConditionalT< (BitSize<T>::Value > BitSize<U>::Value), T, ConditionalT< (BitSize<U>::Value > BitSize<T>::Value), U, void > >;

	template <typename T, typename U>
	using SmallerType = ConditionalT<(BitSize<T>::Value < BitSize<U>::Value), T, U>;

	template <typename T, typename U>
	using StrictSmallerType = ConditionalT< (BitSize<T>::Value < BitSize<U>::Value), T, ConditionalT< (BitSize<U>::Value < BitSize<T>::Value), U, void > >;

}
