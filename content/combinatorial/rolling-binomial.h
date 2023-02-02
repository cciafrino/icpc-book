/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: 
 * Status: 
 * Description: $\binom{n}{k} \pmod{m}$ in time proportional to 
 *		the difference between $(n, k)$ and the previous $(n, k)$.
 * Source: 
 */
#include "../number-theory/preparator.h"
using i64 = int64_t;
const int mod = int(1e9) + 7;
struct Bin {
	int N = 0,  K = 0; i64 r = 1;
	void m(int a, int b) { r = r * a % mod * invs[b] % mod; }
	i64 choose(int n, int k) {
		if (k > n || k < 0) return 0;
		while(N < n) ++N, m(N, N - K);
		while(K < k) ++K, m(N - K + 1, K);
		while(K > k) m(K, N - K + 1), --K;
		while(N > n) m(N - K, N), --N;
		return r;
	}
};
