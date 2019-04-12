#pragma once

#include <vector>
#include <map>

template<class T>
bool even(const T &n);

//! divides by 2
template<class T>
void bisect(T &n);

//! multiply by 2
template<class T>
void redouble(T &n);

template<class T>
bool perfect_square(const T &n);

//! lower bound sq root
template<class T>
T sq_root(const T &n);

template<class T>
unsigned bits_in_number(T n);

template<class T>
bool test_bit(const T &n, unsigned k);

template<class T>
void mulmod(T &a, T b, const T &n);

template<>
inline void mulmod(int &a, int b, const int &n);

template<>
inline void mulmod(unsigned &a, unsigned b, const unsigned &n);

template<>
inline void mulmod(unsigned long long &a, unsigned long long b, const unsigned long long &n);

template<>
inline void mulmod(long long &a, long long b, const long long &n);


template<class T, class T2>
T powmod(T a, T2 k, const T &n);

//! transform n into q*2^p
template<class T>
void transform_num(T n, T &p, T &q);

//! Euclidean algorithm
template<class T, class T2>
T gcd(const T &a, const T2 &b);

//!symbol Jacobi
template<class T>
T jacobi(T a, T b);

template<class T, class T2>
const std::vector<T> &get_primes(const T &b, T2 &pi);

// returns:
// 1: n is prime
// p>1 - it's divider
// 0 - unknown result
template<class T, class T2>
T2 prime_div_trivial(const T &n, T2 m);

template<class T, class T2>
bool miller_rabin(T n, T2 b);

template<class T, class T2>
bool lucas_selfridge(const T &n, T2 unused);

template<class T>
bool baillie_pomerance_selfridge_wagstaff(T n);

template<class T>
bool isprime(T n);

template<class T>
T pollard_p_1(T n);

template<class T>
T pollard_rho(T n, unsigned iterations_count = 100000);

template<class T>
T pollard_bent(T n, unsigned iterations_count = 19);

template<class T>
T pollard_monte_carlo(T n, unsigned m = 100);

template<class T, class T2>
T ferma(const T &n, T2 unused);

template<class T, class T2>
void factorize(const T &n, std::map<T, unsigned> &result, T2 unused);
