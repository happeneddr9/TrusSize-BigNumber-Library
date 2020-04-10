// BigNumber.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <limits>
#include <vector>
#include <chrono>
#include "BigNumber.h"

using std::cout;
using std::endl;
using print_t = std::ostream;

using BigMath::BigNumber;

template <size_t WordSize>
void print_bigNumHex(const BigNumber<WordSize>& num, bool print_zero = true) {
	static constexpr uint32_t HEXmask = 0xF0000000U;
	uint32_t totalSize = num.IndexSize;
	bool start_print = print_zero;
	uint32_t shift_num;
	uint32_t buf;
	char ch_num;

	cout << "0x";
	while (totalSize--) {
		shift_num = 28;
		for (uint32_t i = HEXmask; i > 0; i >>= 4) {
			buf = (num[totalSize] & i) >> shift_num;
			if (buf > 0)
				start_print = true;
			ch_num = "0123456789ABCDEF"[buf];
			if (start_print)
				cout.put(ch_num);
			shift_num -= 4;
		}
		cout.flush();
	}

	if (!start_print) {
		cout.put('0');
	}
}


template <size_t WordSize>
std::ostream& operator<<(std::ostream& os, const BigMath::BigNumber<WordSize>& val) {
	static const uint32_t maxLength = 10 * WordSize + 8;			// get digits in decimal
	// log10(2 ^ n) + 1 => log10(2 ^ 32) * WordSize + bias
	// log10(2 ^ 32) -> 9.633 -> 10
	char buff[maxLength];
	memset(buff, '\0', maxLength);
	val.toStringDec(buff);
	os << buff;

	return os;
}



const BigNumber<4> BigNumberArray[] = {
		123456789,							// construct by int, value = 123456789
		-123456789,							// construct by int (negative), value = -123456789
		53456ULL,							// construct by unsigned long long, value = 53456
		0xFFFFU,							// construct by unsigned int (Hex), value = 65535
		"123456789",						// construct by string (Dec), value = 123456789
		"0123456789",						// construct by string (Oct, the '0' prefix), value = 342391
											// 8 and 9 will be truncated.
		"0xBadCAFE15BadE7707",				// construct by string (Hex), value = 215437285893945063175
		"0b0101110101011000010110111111‬",	// construct by string (Binary), value = 94879487
		1.414f,								// construct by float, rounding to 1
		1.5123f,							// construct by float, rounding to 2
		1.0e9f,								// construct by float, equal 10 ^ 9
		3.1415926e20,						// construct by double, value = 314159260000000016384
											// 
		std::numeric_limits<double>::infinity()	// construct by double, out of range, initialize to 0
};

print_t& BigNumberDemo(print_t& os) {
	BigNumber<2> a;
	BigNumber<4> b;
	BigNumber<8> c;
	BigNumber<16> d;
	BigNumber<32> e(9999.0f);
	os << "======== BigNumber Demo Start ========" << endl;
	os << "sizeof(BN<2> a) = " << sizeof(a) << " bytes" << endl;
	os << "sizeof(BN<4> b) = " << sizeof(b) << " bytes" << endl;
	os << "sizeof(BN<8> c) = " << sizeof(c) << " bytes" << endl;
	os << "sizeof(BN<16> d) = " << sizeof(d) << " bytes" << endl;
	os << "sizeof(BN<32> e) = " << sizeof(e) << " bytes" << endl;

	os << std::fixed << std::setprecision(6);

	os << "======== Arithmetic Test ========" << endl;
	a = 1234;
	os << "init a = " << a << endl;
	os << "a to float = " << static_cast<float>(a) << endl;
	// Addition test
	a += 20;
	os << "a += 20" << endl;
	os << "a = " << a << endl;
	// Subtraction test
	a -= 1999;
	os << "a -= 1999" << endl;
	os << "a = " << a << endl;
	// Multiplication test
	a *= 12345;
	os << "a *= 12345" << endl;
	os << "a = " << a << endl;
	// Division test
	a /= 16;
	os << "a /= 16" << endl;
	os << "a = " << a << endl;
	// Modulus test
	a %= 16;
	os << "a %= 16" << endl;
	os << "a = " << a << endl;

	os << "======== Init by string ========" << endl;
	b = "-3141592653589";
	os << "b = " << b << endl;
	b *= 10;
	os << "b * 10 = " << b << endl;
	float cmp = -31415926535890.0f;
	float tofp = static_cast<float>(b);
	os << "======== compare with float ========" << endl;
	os << "b to float = " << tofp << endl;
	os << "true float = " << cmp << endl;
	os << "compare? " << (tofp == cmp) << endl;

	os << "======== Init by string v2 ========" << endl;
	c = "0x0000FFFF";
	os << "c = 0x" << c.toString(16) << endl;
	c /= -0x11;
	os << "c / -0x11 = 0x" << c.toString(16) << endl;
	os << "c = (Dec) " << c << endl;
	os << "c to float = " << static_cast<float>(c) << endl;

	os << "======== Large Number test ========" << endl;
	d = 3141592.0f;
	d.pow(10);
	os << "d = 3141592 ^ 10 = \n" << d << endl;
	d.isqrt();
	os << "d.isqrt() = " << d << endl;
	cmp = std::pow(3141592.0f, 5);
	tofp = static_cast<float>(d);
	os << "d to float = " << tofp << endl;
	os << "pow(3141592.0f, 5) = " << cmp << endl;
	os << "compare? " << (tofp == cmp) << endl;

	os << "======== constructor test ========" << endl;
	BigNumber<8> lval(a);			// different size copy constructor test
	os << "lval = a = " << lval << endl;

	BigNumber<8> rval(a + b);		// different size move constructor test
	os << "rval = a + b = " << rval << endl;

	os << "======== compare test ========" << endl;


	os << "======== const BigNumber Array ========" << endl;
	uint32_t i = 0;
	for (const auto& x : BigNumberArray) {
		os << "BigArray[" << i++ << "]: " << x << endl;
	}


	os << "======== Floating point Check ========" << endl;
	bool all_pass = true;
	for(uint32_t i = 0; i < 100; ++i){
		static const float base_val = -3.141592653589f;
		static float test = base_val;
		d = test;
		float d_fp = static_cast<float>(d);
		float real = std::round(test);
		if (d_fp != real) {
			cout << "compare error!" << endl;
			cout << "d in float = " << d_fp << endl;
			cout << "real float = " << real << endl;
			all_pass = false;
			break;
		}
		test *= base_val;
	}

	for (uint32_t i = 0; i < 100; ++i) {
		static const double base_val = -3.141592653589f;
		static double test = base_val;
		d = test;
		double d_fp = static_cast<double>(d);
		double real = std::round(test);
		if (d_fp != real) {
			cout << "compare error!" << endl;
			cout << "d in float = " << d_fp << endl;
			cout << "real float = " << real << endl;
			all_pass = false;
			break;
		}
		test *= base_val;
	}
	if (all_pass)
		os << "All compare!" << endl;

	os << "======== BigNumber Demo End ========" << endl;
	return os;
}

typedef BigNumber<1> BigNum32;
typedef BigNumber<2> BigNum64;
typedef BigNumber<4> BigNum128;
typedef BigNumber<8> BigNum256;
typedef BigNumber<32> BigNum1024;
typedef BigNumber<64> BigNum2048;
typedef BigNumber<128> BigNum4096;
typedef BigNumber<256> BigNum8192;

using test_type = BigNum2048;
using other_type = BigNum256;

int main() {
	test_type test = 0;
	other_type ver = 0;
	cout << std::boolalpha;
	cout << std::setprecision(10);

	/*for (uint32_t i = 0; i < 33; ++i) {
		if(test.is_power_of_2())
			cout << "val: " << test << " lmost one: " << test.high_bit() << " log2: " << test.is_n_power_of_2() << endl;
		++test;
	}*/
	cout << "=============================================================================" << '\n';
	auto start = std::chrono::system_clock::now();

	BigNumberDemo(cout);

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "time used: " << elapsed.count() << " us\n\n\n";

	cout << "BigNumbers size = " << sizeof(test_type) << endl;
	cout << "=============================================================================" << '\n';
	
	start = std::chrono::system_clock::now();
	cout << "digits : " << std::numeric_limits<test_type>::max().digits10() << endl;
	cout << "Maximum: " << std::numeric_limits<test_type>::max() << endl;
	cout << "minimum: " << std::numeric_limits<test_type>::min() << endl;
	end = std::chrono::system_clock::now();

	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "print time used: " << elapsed.count() << " us" << '\n';
	cout << "=============================================================================" << '\n';
	
	test.random(0);		// range: 0 to maximum
	start = std::chrono::system_clock::now();
	cout << "BIN: " << test.toString(2) << "\n\n";			// to BIN string
	cout << "QUA: " << test.toString(4) << "\n\n";			// to QUA string
	cout << "OCT: " << test.toString(8) << "\n\n";			// to OCT string
	cout << "DEC: " << test.toString(10) << "\n\n";			// to DEC string
	cout << "HEX: " << test.toString(16) << "\n\n";			// to HEX string
	end = std::chrono::system_clock::now();

	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "print HEX time used: " << elapsed.count() << " us" << '\n';
	cout << "=============================================================================" << '\n';
	cout << endl;
	//cout << (BigNumberArray[11] % 10000000u) << endl;

	return 0;
}
