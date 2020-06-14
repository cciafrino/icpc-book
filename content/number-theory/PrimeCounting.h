/**
 * Author: Chris
 * Date: 
 * License:
 * Source: https://en.wikipedia.org/wiki/Meissel%E2%80%93Lehmer_algorithm,
 	https://www.topcoder.com/single-round-match-741-editorials/,
 	https://blog.csdn.net/bestFy/article/details/80100244
 * Description: Count the number of primes up to $x$. Also useful for sum of primes.
 * Status: lightly-tested
 * Time:  $O(n^{3/4}/\log n)$
 */
#include<Sieve.h>
const int N = 1e5, K = 50, T = 10000000; // T <= 1e17 is fine for N <= 10^11
vector<int> primes_until;
vector<vector<uint16_t>> dp(N+1, vector<uint16_t>(K+1)); // use 32-bit integer if N >= 2^17

void fill_primes(int n) { // get # of primes up to i
	run_sieve(n);
	int walk = 0;
	for (int i = 0; i < n; ++i) {
		if (!i) primes_until.push_back(0);
		else primes_until.push_back(primes_until.back());
		if (primes[walk] == i) walk++, primes_until.back()++;
	}
}

int64_t solve(int64_t n, int k) { // how many numbers
	if (k == 0) return n; //  in [1, N] not divisible by 
	int64_t p = primes[k]; // any of the first k primes
	if (n < p) return 1ll;
	if (n < min(int64_t(T), p*p)) return primes_until[n] - k + 1;
	bool mark = n < N && k < K;
	if (mark && dp[n][k]) return dp[n][k];
	p = primes[k-1];
	int64_t res = solve(n, k-1) - solve(n/p, k-1);
	if (mark) dp[n][k] = res;
	return res;
}

int64_t calc(int64_t x) {
	if (x < T) return primes_until[x];
	int k = primes_until[sqrt(x)];
	return solve(x, k) + k - 1;
}