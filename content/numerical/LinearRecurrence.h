/**
 * Author: Lucian Bicsi
 * Date: 2018-02-14
 * License: CC0
 * Source: Chinese material
 * Description: Generates the $k$'th term of an $n$-order
 * linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$,
 * given $S[0 \dots n-1]$ and $tr[0 \dots n-1]$.
 * Faster than matrix multiplication.
 * Useful together with Berlekamp--Massey.
 * Usage: linearRec({0, 1}, {1, 1}, k) // k'th Fibonacci number
 * Time: O(n^2 \log k)
 * Status: bruteforce-tested mod 5 for n <= 5
 */
#pragma once

const lint mod = 1000000007; /** exclude-line */

typedef vector<lint> Poly;
lint linearRec(Poly S, Poly tr, lint k) { /// start-hash
	int n = tr.size();
	auto combine = [&](Poly a, Poly b) {
		Poly res(n * 2 + 1);
		for(int i = 0; i < n+1; ++i) for(int j = 0; j < n+1; ++j)
			res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
		for (int i = 2 * n; i > n; --i) for(int j = 0; j < n; ++j)
			res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % mod;
		res.resize(n + 1);
		return res;
	};
	Poly pol(n + 1), e(pol);
	pol[0] = e[1] = 1;
	for (++k; k; k /= 2) {
		if (k % 2) pol = combine(pol, e);
		e = combine(e, e);
	}
	lint res = 0;
	for(int i = 0; i < n; ++i) res = (res + pol[i + 1] * S[i]) % mod;
	return res;
} /// end-hash
