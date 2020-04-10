/**
 * @Name    : BigNumber.h
 * @Date    : 2020年4月4日 下午1:25:17	2020/04/04-13:25	YYYY/MM/DD
 * @Author  : happe
 * @version	: 0.X.X (iduno)
 * @brief   : True-Size BigNumber Library, signed integer.
 * 			  can be any size times WordSize(uint32_t) length.
 *			  has optimal memory utilization in 32-bits Embedded system.
 *			  it's statically, No dynamic memory allocation need.
 *			  Constructor and most operation are prefix constexpr,
 *			  Will be process at the compilation stage to achieve
 *			  maximum efficiency.
 *
 *			  The main design goal of this is to be tight,
 *			  flexible and use few resources(i.e. a 256-bit integer
 *			  takes up 32 bytes).
 *			  The most important is clarity of the code,
 *			  that's why i use c++ written this,
 *			  operator overloading make it more intuitive.
 *
 *
 * 	Supported operation list:
 *
 * 		Constructor & Assignment operator:
 *
 * 			void:		will initialize to 0;
 * 			int:		initialize this by int (32-bits), signed.
 * 			uint32_t:	initialize this by unsigned int (32-bits).
 * 			long:		initialize this by long (64-bits), signed.
 * 			uint64_t:	initialize this by unsigned long (64-bits).
 *
 * 			float:		initialize this by float, No additional processing for infinity or Nan.
 * 			double:		initialize this by double, No additional processing for infinity or Nan.
 *
 * 			const char string:
 * 				initialize this by string.
 * 				Leading space will be ignored.
 * 				Non-Prefix will initialize in Decimal.
 * 				Prefix with '0' will initialize in Octal.
 * 				Prefix with '0b' or '0B' will initialize in Binary.
 * 				Prefix with '0x' or '0X' will initialize in Hexadecimal.
 *
 *		Copy/Move Constructor & Assignment operator:
 *			set Default: compiler will handle this.
 *
 *		Destructor:
 *			set Default: compiler know how to handle this.
 *
 *		Unary:
 *			Prefix Increment:		++A;
 *			Prefix Decrement:		--A;
 *			Postfix Increment:		A++;
 *			Postfix Decrement:		A--;
 *			Negative:				-A;
 *
 * 		Arithmetic:
 * 			Addition:		A + B,	A += B, A += 9999;
 * 			Subtraction:	A - B,	A -= B, A -= 9999;
 * 			Multiplication:	A * B,	A *= B, A *= 1234;
 * 			Division:		A / B,	A /= B, A /= 5;		<attention!> The Quotient is not rounded
 * 			Modulus:		A % B,	A %= B, A %= 5;
 *
 * 		Logical (Bitwise):
 * 			AND:	A & B,	A &= B, A &= 0x87;
 * 			OR:		A | B,	A |= B, A |= 0xAA;
 * 			XOR:	A ^ B,	A ^= B, A ^= 0xFF;
 * 			NOT:	~A (return A's bitwise complement),
 * 					!A (return true if A is zero);
 *
 * 		Compare (Relational):
 * 			==, !=, >=, <=, <, >;		numeric compare, will consider the negative value.
 * 										compare with same type or int are all legal.
 *
 * 		Shift (Bitwise):
 * 			Right-Shift:	A >> n, A >>= n;	n is unsigned int;
 * 			Left-Shift:		A << n, A <<= n;	n is unsigned int;
 * 			RShift_word:	A.rshift_word(n);	n is unsigned int;
 * 			LShift_word:	A.lshift_word(n);	n is unsigned int;
 *
 *		Special:
 *			abs:	Absolute in integer			A.abs();
 *			pow:	power of in integer			A.pow(B), A.pow(3);
 *			isqrt:	square root in integer		A.isqrt();
 *			divmod:	division with remainder		A.divmod(B, C);
 *					(Euclidean division)
 *					// B is Divisor, A is Dividend also Quotient, C is remainder
 *
 *		Cast (convert value to temporary value of type):
 *		  Built-in types:
 *			toInt:		return int (32-bits) type, may overflow.
 *			toLong:		return long (64-bits) type, may overflow.
 *			toFloat:	return float (single-precision) type,
 *						if overflow, it'll return inf or -inf.
 *			toDouble:	return double (double-precision) type,
 *						if overflow, it'll return inf or -inf.
 *
 *			toString (itoa):
 *						convert to c-style char string,
 *						give it a char array (a.k.a char pointer)
 *						which you want to write string here.
 *						return char pointer you gave.
 *
 *			toString (std::string):						<attention!> dynamic memory allocation.
 *						Same function as above,
 *						but it return std::string type.
 *
 *
 *			int 		(explicit):	same as toInt();
 *			uint32_t	(explicit):	same as toInt(), unsigned version;
 *			long 		(explicit):	same as toLong();
 *			uint64_t	(explicit):	same as toLong(), unsigned version;
 *			float		(explicit): same as toFloat();
 *			Double		(explicit): same as toDouble();
 *
 *		  Others:
 *			BigNumber<OtherWordSize>:
 *						convert this to other size class,
 *						may overflow when it convert to smaller one.
 *
 *		For Fun:
 *			std::numeric_limits<BigNumber<WordSize>>:
 *						standard C++ numeric limits library support,
 *						Don't know where it can be used, but it looks cool.
 *
 *	BuildLog:
 *		2020/04/04:
 *			Let's build a BigNumber library!
 *			Added shift operations!
 *			Added shift by words operations!
 *			Added compare function!
 *			Added logical operations!
 *			Added negative-value and zero-value check, BigNumber is signed integer now!
 *			Added abs()!
 *			Added arithmetic operations for addition, subtraction, multiplication and division!
 *			Added constructor for initialization that using signed / unsigned int and long long int!
 *			Added convert to int or long long int function!
 *
 *		2020/04/05:
 *			Added another compare function that compare with int!
 *			Added invert() (return 2's complement)!
 *			Added arithmetic operations for modulus!
 *			Added constructor and assignment operator for char string!
 *			Added constructor and assignment operator for float!
 *			Added explicit cast for most built-in types!
 *			Added implicit cast for different size types!
 *			Added pow(), isqrt()!
 *		2020/04/06:
 *			Added constructor and assignment operator for double!
 *			Added explicit cast for double!
 *			Added complement() (return 1's complement) and '!', '~' overloading!
 *			Support to std::numeric_limits!
 *
 *		2020/04/07:
 *			Added two versions toString()!
 *		2020/04/08:
 *			Optimized for division and modulus.
 *		2020/04/09:
 *			Added begin() and end() for iterator operations.
 *			A little optimize for toString() of decimal mode.
 *
 *
 */
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <numeric>
#include <limits>
#include <string.h>
#include <random>
#include "Details.h"



namespace BigMath {
	std::random_device _random_device;



	 /* float's details */
	struct float_32b {
			constexpr float_32b() : val(0) {

			}

			union {
					// SEEEEEEE EMMMMMMM MMMMMMMM MMMMMMMM
					struct {
							uint32_t Mantissa : 23;		// LSB
							uint32_t Exponent : 8;
							uint32_t Sign : 1;
					};
					uint32_t val;
					float fp;
			};

			static constexpr uint8_t Mantissa_width = 23;
			static constexpr uint8_t Exponent_width = 8;
			static constexpr uint32_t Mantissa_mask = 0x007FFFFF;
			static constexpr uint32_t zero = 0x00000000;		// All zero.
			static constexpr uint32_t one = 0x3F800000;			// Exp is 0. Mantissa is zero.
			static constexpr uint32_t inf = 0x7F800000;			// Exp is Max,  Mantissa is zero.
			static constexpr uint32_t nan = 0x7FFFFFFF;			// Exp is Max,  Mantissa is not zero.
			static constexpr uint8_t zero_exp = 0x7F;			// Exponent in 2^0 = 1
			static constexpr uint8_t max_exp = 0xFF;			// Max Exponent
	};

	/* double's details */
	struct float_64b {
			constexpr float_64b() : val(0) {

			}

			union {
					struct {
							uint64_t Mantissa :52;		// LSB
							uint64_t Exponent :11;
							uint64_t Sign :1;
					};
					uint64_t val;
					double fp;
			};

			static constexpr uint8_t Mantissa_width = 52;
			static constexpr uint8_t Exponent_width = 11;
			static constexpr uint64_t Mantissa_mask = 0x000FFFFFFFFFFFFF;
			static constexpr uint64_t zero = 0ULL;					// All zero.
			static constexpr uint64_t one = 0x3FF0000000000000ULL;	// Exp is 0. Mantissa is zero.
			static constexpr uint64_t inf = 0x7FF0000000000000ULL;	// Exp is Max,  Mantissa is zero.
			static constexpr uint64_t nan = 0x7FFFFFFFFFFFFFFFULL;	// Exp is Max,  Mantissa is not zero.
			static constexpr uint16_t zero_exp = 0x03FF;			// Exponent in 2^0 = 1
			static constexpr uint16_t max_exp = 0x07FF;				// Max Exponent
	};


	class BigNumber_Base {
		public:
			static constexpr uint32_t subNum_Max = std::numeric_limits<uint32_t>::max();
			static constexpr uint32_t subNum_min = std::numeric_limits<uint32_t>::min();
			static constexpr uint32_t subNum_digits = std::numeric_limits<uint32_t>::digits;
			static constexpr uint32_t subNum_digits10 = std::numeric_limits<uint32_t>::digits10;
			static constexpr uint32_t bits_per_word = 32;

			static constexpr uint32_t uint_mask = 0x7FFFFFFFU;
			static constexpr uint32_t sint_mask = 0x80000000U;
			static constexpr uint64_t ulong_mask = 0x7FFFFFFFFFFFFFFFULL;
			static constexpr uint64_t slong_mask = 0x8000000000000000ULL;
			enum {
				SMALLER = -1,
				EQUAL = 0,
				LARGER = 1,
			};
		protected:
			constexpr uint32_t _popcount(uint32_t x) const;
			constexpr uint32_t _leftmost_one(uint32_t x) const;

			constexpr bool _is_power_of_2(uint32_t x) const;
			constexpr uint8_t _is_n_power_of_2(uint32_t v) const;

			static constexpr uint8_t MultiplyDeBruijnBitPosition[32] =
			{
				0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
				8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
			};

	};



	template<size_t WordSize>
	class BigNumber : public BigNumber_Base {
		public:	/* using */
			using const_iterator = const uint32_t*;
			using iterator = uint32_t*;

		public:	
			static constexpr size_t IndexSize = WordSize;

			static_assert(WordSize > 0, "Size can not be Zero!!");

			/* default copy and move constructor */
			constexpr BigNumber(const BigNumber &other) = default;
			constexpr BigNumber(BigNumber &&other) = default;
			constexpr BigNumber& operator=(const BigNumber &other) = default;
			constexpr BigNumber& operator=(BigNumber &&other) = default;

		public:	/* initialization constructor and base destructor */
			constexpr BigNumber();
			constexpr BigNumber(int num);
			constexpr BigNumber(uint32_t num);
			constexpr BigNumber(long int num);
			constexpr BigNumber(unsigned long int num);
			constexpr BigNumber(int64_t num);
			constexpr BigNumber(uint64_t num);
			constexpr BigNumber(const char * str);

			constexpr BigNumber(float num);
			constexpr BigNumber(double num);

			/* Construct by other word size */
			template<size_t OtherWordSize>
			constexpr BigNumber(const BigNumber<OtherWordSize>& other);

			template <size_t OtherWordSize>
			constexpr BigNumber(BigNumber<OtherWordSize>&& other);

			/* Assignment operator */
			constexpr BigNumber& operator=(int num);
			constexpr BigNumber& operator=(uint32_t num);
			constexpr BigNumber& operator=(long int num);
			constexpr BigNumber& operator=(unsigned long int num);
			constexpr BigNumber& operator=(int64_t num);
			constexpr BigNumber& operator=(uint64_t num);
			constexpr BigNumber& operator=(const char * str);

			constexpr BigNumber& operator=(float num);
			constexpr BigNumber& operator=(double num);

			/* Assign by other word size */
			template <size_t OtherWordSize>
			constexpr BigNumber& operator=(const BigNumber<OtherWordSize>& other);

			template <size_t OtherWordSize>
			constexpr BigNumber& operator=(BigNumber<OtherWordSize>&& other);

			~BigNumber();

		public:	/* main members */
			constexpr void init(uint32_t val = subNum_min);		// initialize all index to same value
			constexpr void str2num(const char * str);			// initialize from char string
			
			/* checks */
			constexpr bool isNegative() const;
			constexpr bool isZero() const;
			constexpr bool isInt() const;		// Numerical value in int(32-bits signed integer) range
			constexpr bool isLong() const;		// Numerical value in long(64-bits signed integer) range
			constexpr bool is_power_of_2() const;

			/* compare */
			constexpr int compare(const BigNumber& rhs) const;
			constexpr int compare(int rhs) const;

			/* gimme bit position */
			constexpr size_t high_bit() const;
			constexpr size_t low_bit() const;
			constexpr size_t is_n_power_of_2() const;

			/* change value */
			constexpr BigNumber complement_v() const;
			constexpr BigNumber invert_v() const;
			constexpr BigNumber negate_v() const;
			constexpr BigNumber& complement();
			constexpr BigNumber& invert();
			constexpr BigNumber& negate();
			constexpr BigNumber& clear();
			constexpr BigNumber& add(const BigNumber& rhs, size_t start_at = 0);

			/* built-in type cast */
			constexpr int toInt() const;
			constexpr int64_t toLong() const;
			constexpr float toFloat() const;
			constexpr double toDouble() const;

			/* to string */
			constexpr uint32_t digits10() const;
			constexpr char * toStringDec(char* str) const;						// itoa dec version
			constexpr char * toString(char * str, uint8_t base = 10) const;		// itoa
			constexpr std::string toString(uint8_t base = 10) const;			// for C++ std::string

			/* do math */
			constexpr BigNumber& lshift_word(size_t n);
			constexpr BigNumber& rshift_word(size_t n);
			constexpr BigNumber& divmod(const BigNumber& rhs, BigNumber * remainder = nullptr);
			constexpr BigNumber& divmod(const BigNumber& rhs, BigNumber& remainder);
			constexpr BigNumber& pow(const BigNumber& rhs);
			constexpr BigNumber& pow(uint32_t exp);
			constexpr BigNumber& isqrt();
			constexpr BigNumber& random(BigNumber range_min = minValue(), BigNumber range_max = maxValue());
			constexpr BigNumber factorial(uint32_t exp) const;

		public: /* operators */

			/* iterator support */
			constexpr iterator begin() noexcept {
				return iterator(&(numidx[0]));
			}

			constexpr iterator end() noexcept {
				return iterator(&(numidx[WordSize]));
			}

			constexpr const_iterator begin() const noexcept {
				return const_iterator(&(numidx[0]));
			}

			constexpr const_iterator end() const noexcept {
				return const_iterator(&(numidx[WordSize]));
			}

			/* operators overload */
			constexpr uint32_t& operator[](size_t idx);
			constexpr const uint32_t& operator[](size_t idx) const;

			/* Common operator */
			constexpr BigNumber& operator ++();						// ++Me
			constexpr BigNumber& operator --();						// --Me
			constexpr BigNumber operator ++(int);					// Me++
			constexpr BigNumber operator --(int);					// Me--
			constexpr BigNumber& operator +=(const BigNumber& rhs);
			constexpr BigNumber& operator -=(const BigNumber& rhs);
			constexpr BigNumber& operator *=(const BigNumber &rhs);
			constexpr BigNumber& operator /=(const BigNumber &rhs);
			constexpr BigNumber& operator %=(const BigNumber &rhs);

			/* Logic operator */
			constexpr BigNumber& operator &=(const BigNumber &rhs);
			constexpr BigNumber& operator |=(const BigNumber &rhs);
			constexpr BigNumber& operator ^=(const BigNumber &rhs);

			/* Shift operator */
			constexpr BigNumber& operator <<=(size_t n);
			constexpr BigNumber& operator >>=(size_t n);

			constexpr BigNumber operator -() const;
			constexpr BigNumber operator ~() const;
			constexpr bool operator !() const;

			/**
			 *	@brief:		BigNumber convert to any size
			 * 	@Method:	FIXME: don't know why it not working at BigNumberFunctions.h in Visual C++.
			 */
			template<size_t OtherWordSize>
			constexpr operator BigNumber<OtherWordSize>() const {
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
			
			constexpr explicit operator int() const;
			constexpr explicit operator uint32_t() const;
			constexpr explicit operator int64_t() const;
			constexpr explicit operator uint64_t() const;

			constexpr explicit operator float() const;
			constexpr explicit operator double() const;

			constexpr const BigNumber copy_this() const {
				return *this;
			}

			constexpr BigNumber& abs() {
				if(isNegative())
					invert();
				return *this;
			}

			static constexpr BigNumber maxValue() {
				return minValue() - 1;
			}

			// Fixed print '-0' problem
			static constexpr BigNumber minValue() {
				BigNumber tmp;
				tmp[IndexSize - 1] = 0x80000000;
				return tmp;
			}

		private:

		protected:
			constexpr bool isHexChar(const char c) const;
			constexpr bool isDecChar(const char c) const;
			constexpr bool isOctChar(const char c) const;
			constexpr bool isBinChar(const char c) const;

		protected:
			union {
				uint32_t numidx[WordSize];
				uint16_t numidx_16b[WordSize * 2];
				uint8_t numidx_8b[WordSize * 4];
			};
	};

	/* others global function */

	// return teo times size BigNumber
	template <size_t WordSize>
	constexpr BigNumber<WordSize * 2> multiply(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

} /* namespace BigMath */

/* Logic operator */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator&(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator|(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator^(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

/* with int */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator&(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator|(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator^(const BigMath::BigNumber<WordSize> &lhs, int rhs);

/* Another side*/
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator&(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator|(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator^(int lhs, const BigMath::BigNumber<WordSize> &rhs);


/* Compare Logic operator */
template <size_t WordSize>
constexpr bool operator==(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator!=(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator>=(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator<=(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator>(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator<(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

/* different size compare */
template <size_t lsize, size_t rsize>
constexpr bool operator==(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

template <size_t lsize, size_t rsize>
constexpr bool operator!=(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

template <size_t lsize, size_t rsize>
constexpr bool operator>=(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

template <size_t lsize, size_t rsize>
constexpr bool operator<=(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

template <size_t lsize, size_t rsize>
constexpr bool operator>(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

template <size_t lsize, size_t rsize>
constexpr bool operator<(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

/* Compare whit int Logic operator */
template <size_t WordSize>
constexpr bool operator==(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr bool operator!=(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr bool operator>=(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr bool operator<=(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr bool operator>(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr bool operator<(const BigMath::BigNumber<WordSize> &lhs, int rhs);

/* Another side */
template <size_t WordSize>
constexpr bool operator==(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator!=(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator>=(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator<=(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator>(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr bool operator<(int lhs, const BigMath::BigNumber<WordSize> &rhs);


/* both Arithmetic operator */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator+(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator-(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator*(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator/(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator%(const BigMath::BigNumber<WordSize> &lhs, const BigMath::BigNumber<WordSize> &rhs);

/* different size */
template <size_t lsize, size_t rsize>
constexpr auto operator+(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

template <size_t lsize, size_t rsize>
constexpr auto operator-(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

template <size_t lsize, size_t rsize>
constexpr auto operator*(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

template <size_t lsize, size_t rsize>
constexpr auto operator/(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

template <size_t lsize, size_t rsize>
constexpr auto operator%(const BigMath::BigNumber<lsize> &lhs, const BigMath::BigNumber<rsize> &rhs);

/* Arithmetic operator with int */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator+(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator-(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator*(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator/(const BigMath::BigNumber<WordSize> &lhs, int rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator%(const BigMath::BigNumber<WordSize> &lhs, int rhs);

/* another side */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator+(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator-(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator*(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator/(int lhs, const BigMath::BigNumber<WordSize> &rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator%(int lhs, const BigMath::BigNumber<WordSize> &rhs);



/* shift */
template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator<<(const BigMath::BigNumber<WordSize> &lhs, size_t rhs);

template <size_t WordSize>
constexpr BigMath::BigNumber<WordSize> operator>>(const BigMath::BigNumber<WordSize> &lhs, size_t rhs);


#include "BigNumberFunctions.h"
#include "BigNumberPrint.h"
#include "BigNumberGlobalFunc.h"
#include "BigNumberLimits.h"
