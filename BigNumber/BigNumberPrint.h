/**
 * @Name    : BigNumberPrint.h
 * @Date    : 2020年4月4日 下午2:24:26
 * @Author  : happe
 * @brief   : see BigNumber.h
 */
#pragma once

#include "BigNumber.h"
#include <iostream>
#include <iomanip>
#include <cmath>

namespace BigMath {


	template <size_t WordSize>
	constexpr bool BigNumber<WordSize>::isHexChar(const char c) const {
		return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
	}

	template <size_t WordSize>
	constexpr bool BigNumber<WordSize>::isDecChar(const char c) const {
		return (c >= '0' && c <= '9');
	}

	template <size_t WordSize>
	constexpr bool BigNumber<WordSize>::isOctChar(const char c) const {
		return (c >= '0' && c <= '7');
	}

	template <size_t WordSize>
	constexpr bool BigNumber<WordSize>::isBinChar(const char c) const {
		return (c == '0' || c == '1');
	}
}





