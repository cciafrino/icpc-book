/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: Codeforces
 * Description: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal) optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Status: tested on http://codeforces.com/contest/321/problem/E
 * Time: O((N + (hi-lo)) \log N)
 */
struct DP { ///start-hash
	vector<int>a, freq;
	vector<ll>old, cur;
	ll cnt; int lcur, rcur;
	DP(const vector<int>&_a, int n): a(_a), freq(n), old(n+1, linf), cur(n+1, linf), cnt(0), lcur(0), rcur(0){}
	int lo(int ind) { return 0; }
	int hi(int ind) { return ind; }
	void add(int k, int c){ cnt += freq[a[k]]++; }
	void del(int k, int c){ cnt -= --freq[a[k]]; }
	ll C(int l, int r){
		while(lcur > l) add(--lcur, 0);
		while(rcur < r) add(rcur++, 1);
		while(lcur < l) del(lcur++, 0);
		while(rcur > r) del(--rcur, 1);
		return cnt;
	} ///end-hash
	ll f(int ind, int k) { return old[k] + C(k, ind); } ///start-hash
	void store(int ind, int k, ll v) { cur[ind] = v; }
	void rec(int L, int R, int LO, int HI) {
		if (L >= R) return;
		int mid = (L + R) >> 1;
		pair<ll, int> best(LLONG_MAX, LO);
		for(int k = max(LO,lo(mid)); k <= min(HI,hi(mid)); ++k)
			best = min(best, make_pair(f(mid, k), k));
		store(mid, best.second, best.first);
		rec(L, mid, LO, best.second);
		rec(mid+1, R, best.second, HI);
	}
}; ///end-hash
