/**
 * Author: Felipe Abella, Chris
 * Description: Builds suffix array for a string, first element is the size of the string. 
 * The {\tt lcp} function calculates longest
 * common prefixes for neighbouring strings in suffix array.
 * The returned vector is of size $n+1$. 
 * Time: $O(N \log N)$ where $N$ is the length of the string
 * for creation of the SA. $O(N)$ for longest common prefixes.
 */
#include<../data-structures/rmq.h>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct suffix_array_t {
	int N, H; vector<int> sa, invsa, lcp;
	rmq_t<pair<int, int>> rmq;
	bool cmp(int a, int b) { return invsa[a + H] < invsa[b + H]; }
	void ternary_sort(int a, int b) {
		if (a == b) return;
		int md = sa[a+rng() % (b-a)], lo = a, hi = b;
		for (int i = a; i < b; ++i) if (cmp(sa[i], md)) swap(sa[i], sa[lo++]);
		for (int i = b-1; i >= lo; --i) if (cmp(md, sa[i])) swap(sa[i], sa[--hi]);
		ternary_sort(a, lo);
		for (int i = lo; i < hi; ++i) invsa[sa[i]] = hi-1;
		if (hi-lo == 1) sa[lo] = -1;
		ternary_sort(hi, b);
	}
	suffix_array_t() {}
	template<typename I>
	suffix_array_t(I begin, I end): N(int(end - begin)+1), sa(N) {
		vector<int> v(begin, end); v.push_back(INT_MIN);
		invsa = v; iota(sa.begin(), sa.end(), 0);
		H = 0; ternary_sort(0, N);
		for (H = 1; H <= N; H *= 2)
			for (int j = 0, i = j; i != N; i = j)
				if (sa[i] < 0) {
					while (j < N && sa[j] < 0) j += -sa[j];
					sa[i] = -(j - i);
				}
				else { j = invsa[sa[i]] + 1; ternary_sort(i, j); }
		for (int i = 0; i < N; ++i) sa[invsa[i]] = i;
		lcp.resize(N-1); int K = 0;
		for (int i = 0; i < N-1; ++i) {
			if (invsa[i] > 0) while (v[i + K] == v[sa[invsa[i] - 1] + K]) ++K;
			lcp[invsa[i]-1] = K; K = max(K - 1, 0);
		}
		vector<pair<int, int>> lcp_index(N-1);
		for (int i = 0; i < N-1; ++i) lcp_index[i] = {lcp[i], 1 + i};
		rmq = rmq_t<pair<int, int>>(std::move(lcp_index));
	} 
	pair<int, int> rmq_query(int a, int b) const { return rmq.query(a, b); }
	pair<int, int> get_split(int a, int b) const { return rmq.query(a, b-1); }
	int get_lcp(int a, int b) const {
		if (a == b) return N - a;
		a = invsa[a], b = invsa[b];
		if (a > b) swap(a, b);
		return rmq_query(a + 1, b + 1).first;
	}
};
