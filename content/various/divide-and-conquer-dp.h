/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: Codeforces
 * Description: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal) optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Status: tested on http://codeforces.com/contest/321/problem/E
 * Time: O((N + (hi-lo)) \log N)
 */
struct DP { // Modify at will:
	int lo(int ind) { return 0; }
	int hi(int ind) { return ind; }
	lint f(int ind, int k) { return dp[ind][k]; }
	void store(int ind, int k, lint v) { res[ind] = {k, v}; }
	void rec(int L, int R, int LO, int HI) {
		if (L >= R) return;
		int mid = (L + R) >> 1;
		pair<lint, int> best(LLONG_MAX, LO);
		for(int k = max(LO,lo(mid)); k <= min(HI,hi(mid)); ++k)
			best = min(best, make_pair(f(mid, k), k));
		store(mid, best.second, best.first);
		rec(L, mid, LO, best.second);
		rec(mid+1, R, best.second, HI);
	}
	void solve(int L, int R) { rec(L, R, INT_MIN, INT_MAX); }
};

struct DP { 
    vector<int>a, freq;
    vector<lint>old, cur;
    lint cnt;
    DP(const vector<int>&_a, int n): a(_a), freq(n), old(n, linf), cur(n, linf), cnt(0) {}
    int lo(int ind) { return 0; }
    int hi(int ind) { return ind; }
    lint f(int ind, int k) { return old[k] + cnt; }
    void add(int ind, int k){ cnt += freq[a[k]]++; }
    void del(int ind, int k){ cnt -= --freq[a[k]]; }
    void store(int ind, int k, lint v) { cur[ind] = v; }
    void rec(int L, int R, int LO, int HI, int lastl, int lastr) {
        if (L >= R) return;
        int mid = (L + R) >> 1;
        pair<lint, int> best(LLONG_MAX, LO);
        int left = max(LO,lo(mid)), right = min(HI,hi(mid));
        if(lastl != -1){
            for(int k = lastr; k > mid; --k) del(mid, k);
            for(int k = lastr+1; k <= mid; ++k) add(mid, k);
            
            for(int k = lastl; k <= right; ++k) del(mid, k);
            for(int k = lastl; k > right; --k) add(mid, k);    
        }
        for(int k = right; k >= left; --k){    
            best = min(best, make_pair(f(mid, k), k));
            add(mid, k);
        }
        store(mid, best.second, best.first);
        rec(L, mid, LO, best.second, left, mid);
        rec(mid+1, R, best.second, HI, left, mid);
        for(int k = right; k >= left; --k) del(mid, k);        
        if(lastl != -1){
            for(int k = lastr; k > mid; --k) add(mid, k);
            for(int k = lastr+1; k <= mid; ++k) del(mid, k);
            
            for(int k = lastl; k <= right; ++k) add(mid, k);
            for(int k = lastl; k > right; --k) del(mid, k);
        }    
    }
    //void solve(int L, int R) { rec(L, R, INT_MIN, INT_MAX); }
};
