#include "utils.h"
#include <iostream>

int main()
{
	typedef long long base;

	base n = 123456789987654321;

	std::map<base, unsigned> m;
	factorize(n, m, (long long)0);

	for (auto &i : m) {
		std::cout << i.first << "^" << i.second << " * ";
	}
	std::cout << '1';

	return 0;
}
