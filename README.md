# TrueSize-BigNumber-class
Static variadic large-size integer without dynamic memory allocation

## Description
Tiny portable [Arbitrary-precision arithmetic](https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic) in modern C++ class, uses an array of `uint32_t` as underlying type, no any one bits wasted in each word, variadic array length signed integer, how many size how many range, You can easily set any size integer you want for your project.

## Requirements
- C++11 or later.

## Supported operation list:

### Arithmetic & Assignment Arithmetic:
- Addition:         `A + B,	A += B, A += 9999;`
- Subtraction:  	`A - B,	A -= B, A -= 9999;`
- Multiplication:	`A * B,	A *= B, A *= 1234;`
- Division:    		`A / B,	A /= B, A /= 5;`
- Modulus:    		`A % B,	A %= B, A %= 5;`

### Logical (Bitwise):
- AND:  	`A & B,	A &= B, A &= 0x9487;`
- OR:		`A | B,	A |= B, A |= 0xAABB;`
- XOR:  	`A ^ B,	A ^= B, A ^= 0x1234;`
- NOT:  	`~A (bitwise complement);`

### Compare (Relational):
- (==, !=, >=, <=, <, >) numbers compare, it'll consider the negative value.

### Shift (Bitwise):
- Right-Shift:	`A >> n, A >>= n;	n is unsigned int;`
- Left-Shift:	`A << n, A <<= n;	n is unsigned int;`
- RShift_word:	`A.rshift_word(n);	n is unsigned int;`
- LShift_word:	`A.lshift_word(n);	n is unsigned int;`

### Special:
- `abs`:	Absolute in integer			`A.abs();`
- `pow`:	power of in integer			`A.pow(B), A.pow(3);`
- `isqrt`:	square root in integer		`A.isqrt();`
- `divmod`:	division with remainder		`A.divmod(B, C);`

### Cast:
- `toInt`:		return int (32-bits) type, may overflow.
- `toLong`:		return long (64-bits) type, may overflow.
- `toFloat`:	return float (single-precision) type, if overflow, it'll return inf or -inf.
- `toDouble`:	return double (double-precision) type, if overflow, it'll return inf or -inf.
- `toString (itoa)`: convert to c-style char string.
- `toString (std::string)`: Same function as above, but it return std::string type.
- explicit cast for `int`, `uint32_t`, `long int`, `uint64_t`, `float` and `double`.
- implicit cast for `BigNumber<OtherWordSize>`, convert this to other size class.

### Others:
- `std::numeric_limits`: standard C++ numeric limits library support.

## Usage
### Create a BigNumber
```cpp
#include "BigNumber.h"      // include BigNumber library.
using BigMath::BigNumber;   // BigNumber define in BigMath namespace.
BigNumber<8> myNumber = 0;  // Create a 8-wordsize (256-bits) signed integer.
```
### Assignment to your BigNumber
```cpp
myNumber = 429264526;           // Assignment by int.
myNumber = 157744114380602‬ULL;  // Assignment by uint64_t.
myNumber = 24512.5f             // Assignment by float.
myNumber = 3.14159e25           // Assignment by double.
```

