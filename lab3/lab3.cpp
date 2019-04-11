#include <iostream>
#include <stdint.h>
#include <fstream>
#include <iterator>

unsigned LFSR_Galois(const unsigned polynomR, unsigned& s, const unsigned len) {
	if (s & 1) {
		s = ((s ^ polynomR) >> 1) | (1 << len);
		return 1;
	}
	s >>= 1;
	return 0;

}

int main()
{
	unsigned a1 = 0x40001F,
		a1_rev = 0x7C0001,
		a2 = 0x4DB270,
		b1 = 0x10000061,
		b1_rev = 0x10C00001,
		b2 = 0x1F951D70,
		c1 = 0x40000020,
		c1_rev = 0x2000001,
		c2 = 0x6500C12C;
	const unsigned n = 1e7;
	uint8_t* res = (uint8_t*)calloc(n / 8, 8);
	for (unsigned i = 0; i < n; i++) {
		unsigned s1 = LFSR_Galois(a1_rev, a2, 23);
		unsigned s2 = LFSR_Galois(b1_rev, b2, 29);
		unsigned s3 = LFSR_Galois(c1_rev, c2, 31);

		res[i / 8] |= ((s1 & s2) ^ ((s1 ^ 1) & s3)) << (7 - i % 8);
	}
	std::ofstream cipher("out1.bin", std::ios::binary);
	std::copy(res, res + n / 8, std::ostreambuf_iterator<char>(cipher));

	free(res);
	return 0;
}