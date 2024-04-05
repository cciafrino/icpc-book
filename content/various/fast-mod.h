/**
 * Author: Simon Lindholm
 * Date: 2019-04-19
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Barrett_reduction
 * Description: Compute $a \% b$ about 4 times faster than usual, where $b$ is constant but not known at compile time.
 * Fails for $b = 1$.
 * Status: proven correct, fuzz-tested
 * Measured as having 3 times lower latency, and 8 times higher throughput.
 */
typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) { // a % b + (0 or b)
		return a - (ull)((__uint128_t(m) * a) >> 64) * b;
	}
};