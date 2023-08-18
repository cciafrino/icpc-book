/**
 * Author: Chris
 * Date: 2023
 * License: CC0
 * Source: https://codeforces.com/blog/entry/96199?#comment-852652
 * Description: Bostan-Mori algorithm. Generates the $k$'th term of an $n$-order
 * linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$,
 * given $S[0 \dots n-1]$ and $tr[0 \dots n-1]$.
 * Faster than matrix multiplication.
 * Useful together with Berlekamp--Massey.
 * Usage: linear_rec({0, 1}, {1, 1}, k) // k'th Fibonacci number
 * Time: O(n \log n \log k)
 * Status: bruteforce-tested mod 5 for n <= 5
 */
#include "../modular-arithmetic.h"
template<typename T> 
T linear_rec(const vector<T>& S, const vector<T>& tr, ll K) {
	const int N = int(tr.size());
	vector<T> qs(N + 1); qs[0] = 1;
	for (int i = 0; i < N; ++i) qs[i + 1] = -tr[i];
	auto fs = fft.convolve(S, qs); fs.resize(N);
	for (; K; K /= 2) {
		auto qneg = qs;
		for (int i = 1; i <= N; i += 2) qneg[i] = -qneg[i];
		fs = fft.convolve(fs, qneg), qs = fft.convolve(qs, qneg);
		for (int i = 0; i < N; ++i) {
			fs[i] = fs[2 * i + (K & 1)];
			qs[i] = qs[2 * i];
		}
		qs[N] = qs[2*N]; fs.resize(N), qs.resize(N+1);
	}
	return fs[0];
}
