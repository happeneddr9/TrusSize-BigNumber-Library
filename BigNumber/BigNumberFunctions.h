/**
 * @Name    : BigNumberFunctions.cpp
 * @Date    : 2020年4月4日 下午1:25:17
 * @Author  : happe
 * @brief   : see BigNumber.h
 */

#pragma once

#include <string.h>
#include "BigNumber.h"

namespace BigMath {

	template<size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber() {
		init();
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber(int num) {
		/*init(num < 0 ? subNum_Max : subNum_min);
		numidx[0] = static_cast<uint32_t>(num);*/
		*this = num;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber(uint32_t num) {
		/*init();
		numidx[0] = static_cast<uint32_t>(num);*/
		*this = num;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber(long int num) {
		/*init(num < 0 ? subNum_Max : subNum_min);
		numidx[0] = static_cast<uint32_t>(num);*/
		*this = num;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber(unsigned long int num) {
		/*init();
		numidx[0] = static_cast<uint32_t>(num);*/
		*this = num;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber(int64_t num) {
		/*init(num < 0 ? subNum_Max : subNum_min);
		numidx[1] = static_cast<uint32_t>(num >> 32);
		numidx[0] = static_cast<uint32_t>(num);*/
		*this = num;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber(uint64_t num) {
		/*init();
		numidx[1] = static_cast<uint32_t>(num >> 32);
		numidx[0] = static_cast<uint32_t>(num);*/
		*this = num;
	}

	//const char * str
	template <size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber(const char *str) {
		str2num(str);
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber(float num) {
		*this = num;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::BigNumber(double num) {
		*this = num;
	}

	/* Construct by other word size */
	template <size_t WordSize>
	template <size_t OtherWordSize>
	constexpr BigNumber<WordSize>::BigNumber(const BigNumber<OtherWordSize>& other){
		*this = other;
	}

	template <size_t WordSize>
	template <size_t OtherWordSize>
	constexpr BigNumber<WordSize>::BigNumber(BigNumber<OtherWordSize>&& other){
		*this = other;
	}

	template <size_t WordSize> constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(int num) {
		init(num < 0 ? subNum_Max : subNum_min);
		numidx[0] = static_cast<uint32_t>(num);
		return *this;
	}

	template <size_t WordSize> constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(uint32_t num) {
		init();
		numidx[0] = static_cast<uint32_t>(num);
		return *this;
	}

	template <size_t WordSize> constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(long int num) {
		init(num < 0 ? subNum_Max : subNum_min);
		numidx[0] = static_cast<uint32_t>(num);
		return *this;
	}

	template <size_t WordSize> constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(unsigned long int num) {
		init();
		numidx[0] = static_cast<uint32_t>(num);
		return *this;
	}

	template <size_t WordSize> constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(int64_t num) {
		init(num < 0 ? subNum_Max : subNum_min);
		if(WordSize > 1)
			numidx[1] = static_cast<uint32_t>(num >> 32);
		numidx[0] = static_cast<uint32_t>(num);
		return *this;
	}

	template <size_t WordSize> constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(uint64_t num) {
		init();
		if(WordSize > 1)
			numidx[1] = static_cast<uint32_t>(num >> 32);
		numidx[0] = static_cast<uint32_t>(num);
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(const char *str) {
		str2num(str);
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(float num) {
		init();
		float_32b tmp;
		tmp.fp = num;

		if(tmp.Exponent < tmp.zero_exp){					// Exponent < 0
			// Exponent = -1; val must greater than 0.5; rounding to 1
			if (tmp.Exponent == (tmp.zero_exp - 1)) {
				*this = 1;
			} else {
				clear();
			}
		} else {
			uint32_t exp = tmp.Exponent - tmp.zero_exp;
			numidx[0] = tmp.Mantissa;
			numidx[0] |= (1 << tmp.Mantissa_width);
			if (exp >= tmp.Mantissa_width) {
				*this <<= (exp - tmp.Mantissa_width);
			} else {
				numidx[0] >>= (tmp.Mantissa_width - 1) - exp;
				++numidx[0];
				numidx[0] >>= 1;
			}
		}

		if(tmp.Sign == 1)
			invert();

		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(double num) {
		init();
		float_64b tmp;
		tmp.fp = num;

		if (tmp.Exponent < tmp.zero_exp) {					// Exponent < 0
			// Exponent = -1; val must greater than 0.5; rounding to 1
			if (tmp.Exponent == (tmp.zero_exp - 1)) {
				*this = 1;
			} else {
				clear();
			}
		} else {
			uint32_t exp = static_cast<uint32_t>(tmp.Exponent - tmp.zero_exp);
			uint64_t value;
			value = tmp.Mantissa;
			value |= (1ULL << tmp.Mantissa_width);
			if (exp >= tmp.Mantissa_width) {
				*this = value;
				*this <<= (exp - tmp.Mantissa_width);
			} else {
				value >>= (tmp.Mantissa_width - 1) - exp;
				value += 1;
				value >>= 1;
				*this = value;
			}
		}

		if (tmp.Sign == 1)
			invert();

		return *this;
	}

	/* Assign by other word size */
	template <size_t WordSize>
	template <size_t OtherWordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(const BigNumber<OtherWordSize> &other){
		uint32_t i = 0;
		if (OtherWordSize > WordSize) {
			for (; i < WordSize; ++i) {
				numidx[i] = other[i];
			}
		} else  {
			init(other.isNegative() ? subNum_Max : subNum_min);
			for (; i < OtherWordSize; ++i) {
				numidx[i] = other[i];		// TODO: C6201 warning so annoying
			}
		}
		return *this;
	}

	template <size_t WordSize>
	template <size_t OtherWordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator=(BigNumber<OtherWordSize> &&other){
		uint32_t i = 0;
		if (OtherWordSize > WordSize) {
			for (; i < WordSize; ++i) {
				numidx[i] = std::move(other[i]);
			}
		} else {
			init(other.isNegative() ? subNum_Max : subNum_min);
			for (; i < OtherWordSize; ++i) {
				numidx[i] = std::move(other[i]);
			}
		}
		return *this;
	}

	template<size_t WordSize>
	BigNumber<WordSize>::~BigNumber() {
		/* none */
	}

	/**
	 * @brief: initialize by char string, Leading space will be ignored.
	 * 		   Non-Prefix will initialize in Decimal.
	 * 		   Prefix with '0' will initialize in Octal.
	 * 		   Prefix with '0b' or '0B' will initialize in Binary.
	 * 		   Prefix with '0x' or '0X' will initialize in Hexadecimal.
	 *
	 */
	template <size_t WordSize>
	constexpr void BigNumber<WordSize>::str2num(const char *str) {
		init();

		if (str == nullptr)
			return;

		uint32_t str_len = strlen(str);
		uint32_t str_idx = 0;
		uint32_t base = 10;
		uint32_t hex_buf = 0;
		bool negative = false;
		bool number_start = false;

		/* ignored space */
		while (str[str_idx] == ' ') {
			str_idx++;
		}

		if (str_idx >= str_len)
			return;

		if (str[str_idx] == '0') {
			str_idx++;
			char buf = str[str_idx++];
			switch (buf) {
				case 'x':
				case 'X': {
					base = 16;
					break;
				}

				case 'b':
				case 'B': {
					base = 2;
					break;
				}

				default:
					base = 8;
					--str_idx;
					break;
			}
		}



		switch (base) {
			case 2: {
				while (isBinChar(str[str_idx])) {
					hex_buf = str[str_idx];
					if(hex_buf != '0')
						number_start = true;
					if (number_start) {
						*this <<= 1;
						numidx[0] |= static_cast<uint32_t>(hex_buf - '0');
					}
					++str_idx;
				}
				break;
			}

			case 8: {
				while (isOctChar(str[str_idx])) {
					hex_buf = str[str_idx];
					if (hex_buf != '0')
						number_start = true;
					if (number_start) {
						*this <<= 3;
						numidx[0] |= static_cast<uint32_t>(hex_buf - '0');
					}
					++str_idx;

				}
				break;
			}

			case 10: {
				if(str[str_idx] == '-'){
					negative = true;
					++str_idx;
				}

				while (isDecChar(str[str_idx])) {
					hex_buf = str[str_idx];
					if (hex_buf != '0')
						number_start = true;
					if (number_start) {
						*this = (*this << 3) + (*this << 1);		// *this *= 10
						*this += (hex_buf - '0');
					}
					++str_idx;
				}

				if(negative)
					invert();

				break;
			}

			case 16: {
				while (isHexChar(str[str_idx])) {
					hex_buf = str[str_idx];
					if (hex_buf != '0')
						number_start = true;
					if (number_start) {
						*this <<= 4;
						hex_buf = (hex_buf >= 'a') ? (hex_buf - 'a' + 10) :
									(hex_buf >= 'A') ? (hex_buf - 'A' + 10) : (hex_buf - '0');
						numidx[0] |= hex_buf;
					}
					++str_idx;
				}
				break;
			}
		}

	}

	template <size_t WordSize>
	constexpr void BigNumber<WordSize>::init(uint32_t val) {
		for(uint32_t i = 0; i < IndexSize; i++)
			numidx[i] = val;
	}

	template <size_t WordSize>
	constexpr bool BigNumber<WordSize>::isNegative() const {
		return numidx[IndexSize - 1] & static_cast<uint32_t>(0x80000000U);
	}

	template <size_t WordSize>
	constexpr bool BigNumber<WordSize>::isZero() const {
		uint32_t i = WordSize;
		do {
			i -= 1; /* Decrement first, to start with last array element */
			if (numidx[i] != 0) {
				return false;
			}
		} while (i != 0);

		return true;
	}

	template <size_t WordSize>
	constexpr bool BigNumber<WordSize>::isInt() const {
		// Numerical value in int(32-bits signed integer) range
		uint32_t mask = isNegative() ? subNum_Max : subNum_min;
		if(WordSize != 1)
			return (numidx[1] == mask) && isLong();
		else
			return true;
	}

	template <size_t WordSize>
	constexpr bool BigNumber<WordSize>::isLong() const {
		// Numerical value in long(64-bits signed integer) range
		if (IndexSize > 2) {
			uint32_t mask = isNegative() ? subNum_Max : subNum_min;
			for (uint32_t i = 2; i < IndexSize; i++) {
				if (numidx[i] != mask)
					return false;
			}
		}
		return true;
	}

	template<size_t WordSize>
	inline constexpr bool BigNumber<WordSize>::is_power_of_2() const
	{
		return (!isZero() && !(*this & (*this - 1)));
	}

	/**
	 * @brief:	Compare two Numbers, negative sign check
	 * @return:	LARGER	= 1
	 * 			EQUAL	= 0
	 * 			SMALLER = -1
	 */
	template <size_t WordSize>
	constexpr int BigNumber<WordSize>::compare(const BigNumber<WordSize>& rhs) const {
		uint32_t i = WordSize;
		bool self_nega = isNegative();
		bool rhs_nega = rhs.isNegative();

		if(!self_nega && rhs_nega)					// a > 0 ; b < 0 ; a > b absolute
			return LARGER;
		else if (self_nega && !rhs_nega)			// a < 0 ; b > 0 ; a < b absolute
			return SMALLER;



		do {
			i -= 1; /* Decrement first, to start with last array element */
			if (numidx[i] > rhs[i]) {
				//return self_nega ? SMALLER : LARGER;
				return LARGER;
			} else if (numidx[i] < rhs[i]) {
				//return self_nega ? LARGER : SMALLER;
				return SMALLER;
			}
		} while (i != 0);

		return EQUAL;
	}

	/**
	 * @brief:	Compare with int, negative sign check
	 * @return:	LARGER	= 1
	 * 			EQUAL	= 0
	 * 			SMALLER = -1
	 */
	template <size_t WordSize>
	constexpr int BigNumber<WordSize>::compare(int rhs) const {
		bool self_nega = isNegative();
		bool rhs_nega = (rhs < 0);


		if (!isInt())							// a out of int range, Definitely greater or less than b
			return self_nega ? SMALLER : LARGER;
		else if (!self_nega && rhs_nega)		// a > 0 ; b < 0 ; a > b Definitely
			return LARGER;
		else if (self_nega && !rhs_nega)		// a < 0 ; b > 0 ; a < b Definitely
			return SMALLER;

		bool zero = isZero();
		if (zero) {
			if(rhs == 0)
				return EQUAL;
			return ((rhs < 0) ? LARGER : SMALLER);
		}

		if (numidx[0] > static_cast<uint32_t>(rhs))
			return LARGER;
		else if (numidx[0] < static_cast<uint32_t>(rhs))
			return SMALLER;
		return EQUAL;

	}

	/**
	 * @brief:	return the Leftmost '1' in this Number, using in floating-point conversion
	 *
	 */
	template <size_t WordSize>
	constexpr size_t BigNumber<WordSize>::high_bit() const {
		size_t i = IndexSize - 1;
		for(; i != 0; --i){
			if(numidx[i] != 0)
				break;
		}
		i = _leftmost_one(numidx[i]) + (i * 32) - 1;
		return i;
	}

	template <size_t WordSize>
	constexpr size_t BigNumber<WordSize>::low_bit() const {
		// TODO : coming soon
		return 0;
	}

	template<size_t WordSize>
	inline constexpr size_t BigNumber<WordSize>::is_n_power_of_2() const {
		size_t i = IndexSize - 1;
		for (; i != 0; --i) {
			if (numidx[i] != 0)
				break;
		}
		i = _is_n_power_of_2(numidx[i]);
		return i;
	}

	/**
	 * @brief:	return this Numbers bitwise complement value.	1 <=> -2 (1's complement)
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize> BigNumber<WordSize>::complement_v() const {
		BigNumber<WordSize> tmp = *this;				// get self value
		for (uint32_t i = 0; i < IndexSize; i++) {
			tmp[i] = subNum_Max - tmp[i];
		}
		return tmp;
	}

	/**
	 * @brief:	return this Numbers negative value. equal negate_v()
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize> BigNumber<WordSize>::invert_v() const {
		return negate_v();
	}

	/**
	 * @brief:	return this Numbers negative value.	1 <=> -1 (2's complement)
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize> BigNumber<WordSize>::negate_v() const {
		BigNumber<WordSize> tmp = complement_v();				// bitwise complement
		/*tmp[0] = -tmp[0];
		for (uint32_t i = 0; i < IndexSize; i++) {
			tmp[i] = subNum_Max - tmp[i];
		}*/
		++tmp;
		return tmp;
	}

	/**
	 * @brief:	bitwise complement this Number.	1 <=> -2 (1's complement)
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::complement() {
		*this = complement_v();
		return *this;
	}

	/**
	 * @brief:	invert this Number, equal negate().
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::invert() {
		*this = invert_v();
		return *this;
	}
	/**
	 * @brief:	negate this Number.	1 <=> -1 (2's complement)
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::negate() {
		*this = negate_v();
		return *this;
	}


	/**
	 * @brief:	to Zero
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::clear() {
		for(uint32_t i = 0; i < IndexSize; ++i)
			numidx[i] = subNum_min;
		return *this;
	}

	/* Normal number convert */

	template <size_t WordSize>
	constexpr int BigNumber<WordSize>::toInt() const {
		return static_cast<int>(numidx[0]);
	}

	template <size_t WordSize>
	constexpr int64_t BigNumber<WordSize>::toLong() const {
		return static_cast<int64_t>(static_cast<uint64_t>(numidx[0]) |
				(static_cast<uint64_t>(numidx[1]) << 32));
	}

	template <size_t WordSize>
	constexpr float BigNumber<WordSize>::toFloat() const {
		return static_cast<float>(*this);
	}

	template <size_t WordSize>
	constexpr double BigNumber<WordSize>::toDouble() const {
		return static_cast<double>(*this);
	}

	template <size_t WordSize>
	constexpr char* BigNumber<WordSize>::toString(char *str, uint8_t base) const{
		if(str == nullptr)
			return str;
		using larger_type = BigMath::BigNumber<WordSize + 1>;
		using normal_type = BigMath::BigNumber<WordSize>;
		normal_type tmp = *this;
		int val_buf;
		char * ptr = str;
		char * ptr_start = str;		// string start at
		char tmp_char;
		// optimize for Binary, Quaternary, Octal or Hexadecimal.
		// 0xAB, A = shift valve, B = bitmask.
		uint8_t bitwise_opti = (base == 16) ?
				0x4F : (base == 8) ?
				0x37 : (base == 4) ?
				0x23 : (base == 2) ?
				0x11 : 0;

		if(base < 2)	// can't be zero or one;
			base = 10;	// set default

		if (tmp.isNegative() && !bitwise_opti) {	// if base is not special, check negative.
			*str = '-';
			++ptr;
			++str;
		}

		if (bitwise_opti > 0) {
			uint8_t bit_shift = bitwise_opti >> 4;
			uint8_t bit_mask = bitwise_opti & 0x0F;
			do {
				val_buf = tmp[0] & bit_mask;
				*str = "0123456789ABCDEF"[val_buf];
				++str;
				tmp >>= bit_shift;
			} while (!tmp.isZero());
		} else {
			larger_type tmp_larger = static_cast<larger_type>(tmp);
			larger_type math_tmp;
			tmp_larger.abs();
			do {
				tmp_larger.divmod(base, math_tmp);
				val_buf = math_tmp[0];
				*str = (val_buf < 10) ? "0123456789"[val_buf] : (val_buf - 'A');
				++str;
			} while (!tmp_larger.isZero());
		}

		*str = '\0';
		--str;


		// reverse char string
		while (ptr <= str) {
			tmp_char = *ptr;
			*ptr = *str;
			*str = tmp_char;
			++ptr;
			--str;
		}

		return ptr_start;
	}

	template <size_t WordSize>
	constexpr std::string BigNumber<WordSize>::toString(uint8_t base) const{
		std::string str = "";
		uint32_t lowest_size = 0;
		if (base >= 16)
			lowest_size = 8;
		else if (base >= 8)
			lowest_size = 11;
		else if (base >= 4)
			lowest_size = 16;
		else if (base >= 2)
			lowest_size = 32;
		else
			lowest_size = 10;		// default base = 10
		lowest_size *= (WordSize + 1);
		lowest_size += 4;
		char *cstr = new char[lowest_size];
		str = toString(cstr, base);
		delete [] cstr;
		return str;
	}


	/**
	 * @brief:	get integer index, no check.
	 */
	template <size_t WordSize>
	constexpr uint32_t& BigNumber<WordSize>::operator[](size_t idx) {
		return numidx[idx];
	}

	template <size_t WordSize>
	constexpr const uint32_t& BigNumber<WordSize>::operator[](size_t idx) const {
		return numidx[idx];
	}

	/* increase and decrease */

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator ++() {
		*this += 1;
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator --() {
		*this -= 1;
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize> BigNumber<WordSize>::operator ++(int) {
		BigNumber<WordSize> tmp = *this;
		*this += 1;
		return tmp;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize> BigNumber<WordSize>::operator --(int) {
		BigNumber<WordSize> tmp = *this;
		*this -= 1;
		return tmp;
	}

	/* Arithmetic operator */

	/**
	 *	@brief:		BigNumber Addition
	 *	@Method:	add 2 index with pre-levels carry.
	 *				if "a + b < a && carry = false";	'a' overflowed.
	 *				if "a + b = a && carry = true"; 	'a' overflowed.
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator +=(const BigNumber<WordSize>& rhs) {
		bool carry = false;
		uint32_t tmpreg = 0;
		for (uint32_t i = 0; i < IndexSize; i++) {
			tmpreg = numidx[i];
			numidx[i] += rhs[i] + static_cast<uint32_t>(carry);
			carry = (numidx[i] < tmpreg || (numidx[i] == tmpreg && carry));
		}
		return *this;
	}

	/**
	 *	@brief:		BigNumber Subtraction
	 *	@Method:	a - b = a + (-b)
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator -=(const BigNumber<WordSize> &rhs) {
		*this += rhs.invert_v();
		return *this;
	}

	/**
	 *	@brief:		BigNumber Multiplication
	 *	@Method:	need "32-bits * 32-bits = 64-bits" Multiplier supports
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator *=(const BigNumber<WordSize> &rhs) {
		
		
		//bool self_nega, rhs_nega;
		

		/*self_nega = isNegative();
		rhs_nega = rhs_tmp.isNegative();

		abs();
		rhs_tmp.abs();*/

		// Special case handling
		if (isZero() || rhs.isZero()) {
			*this = 0;
		}
		else if (rhs.is_power_of_2()) {
			*this <<= rhs.high_bit();
		}
		else {
			BigNumber<WordSize> row;
			BigNumber<WordSize> tmp;
			//BigNumber<WordSize> rhs_tmp(rhs);
			BigNumber<WordSize> output;
			uint32_t i, j;
			uint64_t intermediate;
			for (i = 0; i < IndexSize; ++i) {
				row.clear();
				for (j = 0; j < IndexSize; ++j) {
					if (i + j < IndexSize) {
						if (numidx[i] + rhs.numidx[j] != 0) {
							intermediate = static_cast<uint64_t>(numidx[i])* static_cast<uint64_t>(rhs.numidx[j]);
							tmp = intermediate;
							tmp.lshift_word(i + j);
							row += tmp;
						}
					}
				}
				output += row;
			}
			//*this = (self_nega ^ rhs_nega) ? (-output) : output;
			*this = output;
		}
		return *this;
	}

	/**
	 *	@brief:		BigNumber Division
	 *	@Method:	original is refer from https://github.com/kokke/tiny-bignum-c,
	 *				now it use new algorithmon
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator /=(const BigNumber<WordSize> &rhs) {
		return divmod(rhs);
	}

	/**
	 *	@brief:		Modulus
	 *	@Method:	looking for a better way
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator %=(const BigNumber<WordSize> &rhs) {
		BigNumber<WordSize> tmp;
		divmod(rhs, tmp);
		*this = tmp;
		return *this;
	}

	/**
	 *	@brief:		Euclidean division
	 *	@Method:	division with remainder
	 *
	 *	@update:	2020/04/08:
	 *					new function for division
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::divmod(const BigNumber<WordSize> &rhs, BigNumber<WordSize> *remainder) {
		/*BigNumber<WordSize> tmp = *this;
		tmp /= rhs;
		remainder = tmp * rhs;
		remainder = *this - remainder;
		*this = tmp;*/

		// Special case handling
		if (remainder != nullptr)
			*remainder = 0;
		if (rhs.isZero()) {		// divided by zero
			*this = -1;
		}
		else if (rhs == 1) {	// divided by one, nothing happened.
			
		}
		else if (rhs == -1) {	// divided by negative one, number negate.
			negate();
		}
		else if (*this == rhs) {
			*this = 1;
		}
		else if (rhs.is_power_of_2()) {
			*this >>= rhs.high_bit();
		}
		else {

			// for fix 'minValue' problem, WordSize should larger than original.
			using larger_type = BigNumber<WordSize + 1>;
			using ori_type = BigNumber<WordSize>;
			larger_type current = 1;
			larger_type divisor = static_cast<larger_type>(rhs);
			larger_type dividend = static_cast<larger_type>(*this);
			larger_type ans;

			bool dividend_nega = dividend.isNegative();
			bool divisor_nega = divisor.isNegative();

			dividend.abs();
			divisor.abs();

			if (dividend < divisor) {
				if (remainder != nullptr)
					*remainder = *this;
				*this = 0;
			}
			else {

				while (divisor <= dividend) {	// let divisor align to dividend.
					current <<= 1;
					divisor <<= 1;
				}

				while (!current.isZero()) {
					if (dividend >= divisor) {
						dividend -= divisor;
						ans |= current;
					}
					current >>= 1;
					divisor >>= 1;
				}
				// A exclusive or B is negative, Quotient is negative
				*this = static_cast<ori_type>((dividend_nega ^ divisor_nega) ? (-ans) : (ans));
				if (remainder != nullptr)
					*remainder = static_cast<ori_type>((dividend_nega) ? (-dividend) : dividend);
			}
		}
		return *this;
	}

	/* remainder call by reference */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::divmod(const BigNumber<WordSize>& rhs, BigNumber<WordSize>& remainder) {
		return divmod(rhs, &remainder);
	}

	/**
	 *	@brief:		BigNumber Power operation
	 *	@Method:	a = b ^ 5 => a = b * (b ^ 4)
	 *				a = b ^ 48 => a = (b ^ 16) * (b ^ 32)
	 *				reference from java pow method.
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::pow(uint32_t exp) {

		if ((exp == 0) || (*this == 1)) {
			/* Return 1 when exponent is 0 -- n^0 = 1 */
			*this = 1;
		} else if(isZero()) {

		} else {
			BigNumber<WordSize> tmp = *this;	// this

			*this = 1;
			while (exp != 0) {
				if ((exp & 0x01) == 0x01) {
					*this *= tmp;
				}
				exp >>= 1;
				tmp *= tmp;
			}
		}
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::pow(const BigNumber<WordSize> &rhs) {
		return pow(static_cast<uint32_t>(rhs));
	}

	/**
	 *	@brief:		BigNumber integer square root
	 *	@Method:
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::isqrt() {
		if(isNegative() || isZero()){
			*this = 0;
			return *this;
		}

		BigNumber<WordSize> remainder = *this;
		BigNumber<WordSize> place = 1;

		place <<= ((IndexSize * bits_per_word) - 2);

		while (place > remainder) {
			place >>= 2;				// place /= 4;
		}

		BigNumber<WordSize> root = 0;
		while (!place.isZero() && !place.isNegative()) {		// place > 0
			if (remainder >= (root + place)) {
				remainder -= (root + place);
				root += (place << 1);
			}
			root >>= 1;
			place >>= 2;
		}
		*this = root;
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::random(BigNumber<WordSize> range_min,
			BigNumber<WordSize> range_max) {
		using Uty = BigNumber<WordSize>;

		std::mt19937 gen = std::mt19937(_random_device()); // using mt19937
		//std::default_random_engine gen = std::default_random_engine(_random_device());
		std::uniform_int_distribution<uint32_t> _distribution;
		
		for (uint32_t i = 0; i < IndexSize; ++i) {
			numidx[i] = _distribution(gen);
		}

		if (range_max - range_min == Uty(-1)) {
			
		} else {
			*this %= (range_max - range_min + 1);
			abs();
			*this += range_min;
		}

		return *this;
	}

	/* Logic operator */

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator &=(const BigNumber<WordSize> &rhs) {
		for (uint32_t i = 0; i < IndexSize; ++i) {
			numidx[i] &= rhs.numidx[i];
		}
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator |=(const BigNumber<WordSize> &rhs) {
		for (uint32_t i = 0; i < IndexSize; ++i) {
			numidx[i] |= rhs.numidx[i];
		}
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator ^=(const BigNumber<WordSize> &rhs) {
		for (uint32_t i = 0; i < IndexSize; ++i) {
			numidx[i] ^= rhs.numidx[i];
		}
		return *this;
	}



	/* Shift operator */

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator <<=(size_t n) {
		/* Handle shift in multiples of word-size */
		uint32_t nwords = n / bits_per_word;
		if (nwords != 0) {
			lshift_word(nwords);
			n -= (nwords * bits_per_word);
		}

		if (n != 0) {
			int i = (IndexSize - 1);
			if (i > 0) {
				for (; i > 0; --i) {
					numidx[i] = (numidx[i] << n) | (numidx[i - 1] >> (bits_per_word - n));
				}
			}
			numidx[i] <<= n;
		}
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::operator >>=(size_t n) {
		/* Handle shift in multiples of word-size */
		uint32_t nwords = n / bits_per_word;
		if (nwords != 0) {
			rshift_word(nwords);
			n -= (nwords * bits_per_word);
		}

		if (n != 0) {
			int j = static_cast<int>(IndexSize - 1);
			int i = 0;
			if (j > 0) {
				for (; i < j; ++i) {
					numidx[i] = (numidx[i] >> n) | (numidx[i + 1] << (bits_per_word - n));
				}
			}
			numidx[i] >>= n;
		}
		return *this;
	}

	/* optimized shift by word operator */

	/**
	 *	@brief:		BigNumber Shift by Words
	 *	@Method:
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::lshift_word(size_t n) {
		int i;
		if (n == 0) {		// don't do anything
			
		}
		else {
			/* Shift whole words */
			for (i = (IndexSize - 1); i >= static_cast<int>(n); --i) {
				numidx[i] = numidx[i - n];
			}
			/* Zero pad shifted words. */
			for (; i >= 0; --i) {
				numidx[i] = 0;
			}
		}
		return *this;
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>& BigNumber<WordSize>::rshift_word(size_t n) {
		int i;
		if (n >= IndexSize) {
			for (i = 0; i < static_cast<int>(IndexSize); ++i) {
				numidx[i] = 0;
			}
		}
		else if (n == 0) {	// don't do anything
			
		}
		else {

			for (i = 0; i < static_cast<int>(IndexSize - n); ++i) {
				numidx[i] = numidx[i + n];	// TODO: C6385 warning so annoying
			}

			for (; i < static_cast<int>(IndexSize); ++i) {
				numidx[i] = 0;
			}
			
		}
		return *this;
	}


	/**
	 *	@brief:		BigNumber invert
	 * 	@Method:
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize> BigNumber<WordSize>::operator -() const {
		return negate_v();
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize> BigNumber<WordSize>::operator ~() const {
		return complement_v();
	}

	template <size_t WordSize>
	constexpr bool BigNumber<WordSize>::operator !() const {
		return isZero();
	}

	/**
	 *	@brief:		BigNumber convert to any size
	 * 	@Method:	
	 */
	template <size_t WordSize>
	template <size_t OtherWordSize>
	inline constexpr BigNumber<WordSize>::operator BigNumber<OtherWordSize>() const {
		BigNumber<OtherWordSize> tmp = 0;
		bool m_nega = isNegative();
		uint32_t i = 0;

		for (i = OtherWordSize; i >= IndexSize; i--) {
			//tmp[counter] = m_nega ? subNum_Max : subNum_min;
			tmp[i] = subNum_min;
		}

		for (i = 0; i < IndexSize; i++) {
			tmp[i] = m_nega ? (subNum_Max - numidx[i]) : numidx[i];
		}

		++tmp;

		//tmp[OtherWordSize - 1] |= static_cast<uint32_t>(m_nega ? 0x80000000U : 0U);
		return m_nega ? tmp.negate_v() : tmp;
	}

	/* convert BigNumber to integer */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>::operator int() const {
		return toInt();
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::operator uint32_t() const {
		return static_cast<uint32_t>(toInt());
	}
	template <size_t WordSize>
	constexpr BigNumber<WordSize>::operator int64_t() const {
		return toLong();
	}

	template <size_t WordSize>
	constexpr BigNumber<WordSize>::operator uint64_t() const {
		return static_cast<uint64_t>(toLong());
	}

	/* convert BigNumber to floating point */

	/**
	 * 	@brief:		convert to single-precision float
	 * 	@Method:	TODO: optimize this
	 *
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>::operator float() const {
		float_32b flopt;
		BigNumber<WordSize> tmp = *this;
		if(tmp.isZero())
			flopt.val = 0;
		else {
			if (tmp.isNegative()) {
				tmp.invert();
				flopt.Sign = 1;
			}
			uint32_t hb = tmp.high_bit();
			uint32_t exp = hb + static_cast<uint32_t>(flopt.zero_exp);
			if (exp >= flopt.max_exp) {			// out of range
				flopt.val |= flopt.inf;			// inf or -inf
				return flopt.fp;
			}


			if (hb < flopt.Mantissa_width) {
				tmp <<= flopt.Mantissa_width - hb;	// if number less than Mantissa length, lshift to align.
			} else if (hb > flopt.Mantissa_width) {
				// If the number is greater than mantissa,
				// Confirm if rounding is required.
				tmp >>= hb - (flopt.Mantissa_width + 1);
				++tmp[0];
				tmp >>= 1;
				/*if(tmp > flopt.Mantissa_mask){
					++exp;
					tmp >>= 1;
				}*/
			}

			flopt.Exponent = exp;
			flopt.Mantissa = tmp[0] & flopt.Mantissa_mask;


		}
		return flopt.fp;
	}
	
	/**
	 * 	@brief:		convert to double-precision float
	 * 	@Method:	TODO: optimize this
	 *
	 */
	template <size_t WordSize>
	constexpr BigNumber<WordSize>::operator double() const {
		float_64b flopt;
		BigNumber<WordSize> tmp = *this;
		if(tmp.isZero())
			flopt.val = 0;
		else {
			if (tmp.isNegative()) {
				tmp.invert();
				flopt.Sign = 1;
			}
			uint32_t hb = tmp.high_bit();
			uint32_t exp = hb + static_cast<uint32_t>(flopt.zero_exp);
			if (exp >= flopt.max_exp) {			// out of range
				flopt.val |= flopt.inf;			// inf or -inf
				return flopt.fp;
			}

			if (hb < flopt.Mantissa_width) {
				tmp <<= flopt.Mantissa_width - hb;	// if number less than Mantissa length, lshift to align.
			} else if (hb > flopt.Mantissa_width) {
				// If the number is greater than mantissa,
				// Confirm if rounding is required.
				tmp >>= hb - (flopt.Mantissa_width + 1);
				++tmp;
				tmp >>= 1;
			}
			uint64_t value = tmp.toLong();

			flopt.Exponent = exp;
			flopt.Mantissa = value & flopt.Mantissa_mask;
		}
		return flopt.fp;
	}

	/* BigNumber_Base functions */

	/**
	 * 	"1010 1010" return 8
	 * 	"0000 0001" return 1
	 *  "0000 0000" return 0
	 */
	constexpr uint32_t BigNumber_Base::_leftmost_one(uint32_t x) const {
		x |= x >> 16;
		x |= x >> 8;
		x |= x >> 4;
		x |= x >> 2;
		x |= x >> 1;
		return _popcount(x);
	}

	inline constexpr bool BigNumber_Base::_is_power_of_2(uint32_t x) const
	{
		return (x && !(x & (x - 1)));
	}

	/**
	 *	@brief: integer versions log2()
	 */
	inline constexpr uint8_t BigNumber_Base::_is_n_power_of_2(uint32_t v) const
	{
		
		v |= v >> 1; // first round down to one less than a power of 2 
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;

		return MultiplyDeBruijnBitPosition[(uint32_t)(v * 0x07C4ACDDU) >> 27];
	}

	constexpr uint32_t BigNumber_Base::_popcount(uint32_t x) const {
		x -= (x >> 1) & 0x55555555;
		x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
		x = ((x >> 4) + x) & 0x0F0F0F0F;
		x += x >> 8;
		x += x >> 16;
		return x & 0x0000003F;
	}


} /* namespace BigMath */
