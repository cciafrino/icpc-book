/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: 
 * Status: 
 * Description: $\binom{n}{k} \pmod{m}$ in time proportional to the difference between (n, k) and the previous (n, k).
 * Source: 
 */
const int mod = int(1e9) + 7;
vector<lint> invs; // precomputed inverses up to n
struct Bin {
	int N = 0,  K = 0; lint r = 1;
	void m(lint a, lint b) { return r = r * a % mod * invs[b] % mod; }
	lint choose(int n, int k) {
		if (k > n || k < 0) return 0;
		while(N < n) ++N, m(N, N-K);
		while(K < k) ++K, m(N-K+1, K);
		while(K > k) m(K, N-K-1), --K;
		while(N > n) m(N, N-K), --N;
		return r;
	}
};