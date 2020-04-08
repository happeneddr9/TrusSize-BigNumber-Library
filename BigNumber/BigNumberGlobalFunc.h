/**
 * @Name    : BigNumberLogic.h
 * @Date    : 2020年4月4日 下午7:30:31
 * @Author  : happe
 * @brief   : see BigNumber.h, there is ton of operator overloading.
 */

#pragma once

#include "BigNumber.h"

namespace BigMath {
	template <size_t WordSize>
	constexpr BigNumber<WordSize * 2> multiply(const BigMath::BigNumber<WordSize> &lhs,
			const BigMath::BigNumber<WordSize> &rhs) {
		using dtype = BigNumber<WordSize * 2>;
		dtype tmp = lhs;
		tmp *= static_cast<dtype>(rhs);
		return tmp;
	}


}

/* Logic operator */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator&(const BigMath::BigNumber<WordSize> &lhs,
		const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp &= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator|(const BigMath::BigNumber<WordSize> &lhs,
		const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp |= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator^(const BigMath::BigNumber<WordSize> &lhs,
		const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp ^= rhs;
	return tmp;
}

/* with int */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator&(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp &= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator|(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp |= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator^(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp ^= rhs;
	return tmp;
}

/* Another side*/
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator&(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp &= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator|(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp |= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator^(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp ^= rhs;
	return tmp;
}

/* Compare Logic operator */
template <size_t WordSize>
constexpr bool operator==(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (lhs.compare(rhs) == BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator!=(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (lhs.compare(rhs) != BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator>=(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (lhs.compare(rhs) >= BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator<=(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (lhs.compare(rhs) <= BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator>(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (lhs.compare(rhs) == BigMath::BigNumber_Base::LARGER);
}

template <size_t WordSize>
constexpr bool operator<(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (lhs.compare(rhs) == BigMath::BigNumber_Base::SMALLER);
}

/* different size compare */
template <size_t lsize, size_t rsize>
constexpr bool operator==(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;
	return (static_cast<CompareType>(lhs) == static_cast<CompareType>(rhs));
}

template <size_t lsize, size_t rsize>
constexpr bool operator!=(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;
	return (static_cast<CompareType>(lhs) != static_cast<CompareType>(rhs));
}

template <size_t lsize, size_t rsize>
constexpr bool operator>=(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;
	return (static_cast<CompareType>(lhs) >= static_cast<CompareType>(rhs));
}

template <size_t lsize, size_t rsize>
constexpr bool operator<=(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;
	return (static_cast<CompareType>(lhs) <= static_cast<CompareType>(rhs));
}

template <size_t lsize, size_t rsize>
constexpr bool operator>(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;
	return (static_cast<CompareType>(lhs) > static_cast<CompareType>(rhs));
}

template <size_t lsize, size_t rsize>
constexpr bool operator<(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;
	return (static_cast<CompareType>(lhs) < static_cast<CompareType>(rhs));
}

/* Compare whit int Logic operator */
template <size_t WordSize>
constexpr bool operator==(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	return (lhs.compare(rhs) == BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator!=(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	return (lhs.compare(rhs) != BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator>=(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	return (lhs.compare(rhs) >= BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator<=(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	return (lhs.compare(rhs) <= BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator>(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	return (lhs.compare(rhs) == BigMath::BigNumber_Base::LARGER);
}

template <size_t WordSize>
constexpr bool operator<(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	return (lhs.compare(rhs) == BigMath::BigNumber_Base::SMALLER);
}

/* int Compare Logic operator */
template <size_t WordSize>
constexpr bool operator==(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (rhs.compare(lhs) == BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator!=(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (rhs.compare(lhs) != BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator>=(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (rhs.compare(lhs) <= BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator<=(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (rhs.compare(lhs) >= BigMath::BigNumber_Base::EQUAL);
}

template <size_t WordSize>
constexpr bool operator>(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (rhs.compare(lhs) == BigMath::BigNumber_Base::SMALLER);
}

template <size_t WordSize>
constexpr bool operator<(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	return (rhs.compare(lhs) == BigMath::BigNumber_Base::LARGER);
}

/* Common operator */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator+(const BigMath::BigNumber<WordSize> &lhs,
		const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp += rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator-(const BigMath::BigNumber<WordSize> &lhs,
		const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp -= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator*(const BigMath::BigNumber<WordSize> &lhs,
		const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp *= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator/(const BigMath::BigNumber<WordSize> &lhs,
		const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp /= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator%(const BigMath::BigNumber<WordSize> &lhs,
		const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp %= rhs;
	return tmp;
}

/* different size */
template <size_t lsize, size_t rsize>
constexpr auto operator+(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;

	CompareType tmp(lhs);
	tmp += rhs;
	return tmp;
}

template <size_t lsize, size_t rsize>
constexpr auto operator-(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;

	CompareType tmp(lhs);
	tmp -= rhs;
	return tmp;
}

template <size_t lsize, size_t rsize>
constexpr auto operator*(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;

	CompareType tmp(lhs);
	tmp *= rhs;
	return tmp;
}

template <size_t lsize, size_t rsize>
constexpr auto operator/(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;

	CompareType tmp(lhs);
	tmp /= rhs;
	return tmp;
}

template <size_t lsize, size_t rsize>
constexpr auto operator%(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs) {
	using LeftType = BigMath::BigNumber<lsize>;
	using RightType = BigMath::BigNumber<rsize>;

	using CompareType = BigMath::LargerType<LeftType, RightType>;

	CompareType tmp(lhs);
	tmp %= rhs;
	return tmp;
}

/* Arithmetic operator with int */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator+(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp += rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator-(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp -= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator*(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp *= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator/(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp /= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator%(const BigMath::BigNumber<WordSize> &lhs, int rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp %= rhs;
	return tmp;
}

/* another side */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator+(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp += rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator-(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp -= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator*(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp *= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator/(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp /= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator%(int lhs, const BigMath::BigNumber<WordSize> &rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp %= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator<<(const BigMath::BigNumber<WordSize> &lhs, size_t rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp <<= rhs;
	return tmp;
}

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator>>(const BigMath::BigNumber<WordSize> &lhs, size_t rhs) {
	BigMath::BigNumber<WordSize> tmp = lhs;
	tmp >>= rhs;
	return tmp;
}

