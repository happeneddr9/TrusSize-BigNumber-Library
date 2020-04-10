# TrueSize-BigNumber-Library
Static variadic large-size integer without dynamic memory allocation

## Description
Tiny portable [Arbitrary-precision arithmetic](https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic) in modern C++ class, uses an array of `uint32_t` as underlying type, no any one bits wasted in each word, variadic array length signed integer, how many size how many range, You can easily set any size integer you want for your project.

## Requirements
- C++11 or later.

## Supported operation list:
>Most of the member are constexpr.
### Constructor
- `BigNumber<size_t WordSize>`: WordSize can be any positive integer.
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
- `abs`:	Absolute in integer.			`A.abs();`
- `pow`:	power of in integer.			`A.pow(B), A.pow(3);`
- `isqrt`:	square root in integer.		`A.isqrt();`
- `divmod`:	division with remainder.		`A.divmod(B, C);`
- `random`: get random value in big range. `A.random(min, Max);`

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
- `std::numeric_limits`: (in test) standard C++ numeric limits library support.

## Usage
### Create a BigNumber

```cpp
#include <iostream>
#include "BigNumber.h"      // include BigNumber library.
using BigMath::BigNumber;   // BigNumber define in BigMath namespace.
BigNumber<8> myNumber = 0;  // Create a 8-wordsize (256-bits) signed integer.
```

### Assignment to your BigNumber
```cpp
BigNumber<8> myNumber = 429264526;   // initialize by int.
myNumber = 157744114380602‬ULL;       // Assignment by uint64_t.
myNumber = 24512.5f                  // Assignment by float.
myNumber = 3.14159e25                // Assignment by double.
```

### Assignment by string

```cpp
// cout overloading in main.cpp
BigNumber<8> myNumber = "-14143141592653589";  // initialize by string (DEC).
cout << myNumber << endl;                      // output: -14143141592653589
myNumber = "014143141592653589";               // Assignment by string (OCT, use '0' prefix), 8 and 9 will be truncated.
cout << myNumber << endl;                      // output: 25572109
myNumber = "0b0101100101101010";               // Assignment by string (BIN, use '0b' or '0B' prefix).
cout << myNumber << endl;                      // output: 22890
myNumber = "0xBadCAFE15BadE7707";              // Assignment by string (HEX, use '0x' or '0X' prefix).
cout << myNumber << endl;                      // output: 215437285893945063175
```

### Some operations
```cpp
BigNumber<8> d = -3141592.0f;	// d = -3141592
d.abs();						// d = 3141592
d.pow(10);  // d = 93647852647034719970876567502856390570791695495376238755734093824
d.isqrt();  // d = 306019366457475563428218912735232
float fp = static_cast<float>(d);    // to float, fp = 306019357995739418977067367137280.00
cout << (fp == std::pow(3141592.0f, 5)) << endl;    // output: true
```

### constant BigNumber
```cpp
// convert in compile-time!
const BigNumber<4> BigNumberArray[] = {
  0, 1234567890UL, 0xFEDC123, "0b0101110101011000010110111111",
  3.1415926e20, 1.5123f
};
```

## Testing platform
- Visual Studio 2019 C++
- Eclipse IDE with MinGW

## Up Next
- `log` in integer version
- completely support built-in data types
- completely support built-in numeric check
- Fixed-point library base on BigNumber

