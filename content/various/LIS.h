/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices for the longest increasing subsequence.
 * Status: Tested on Kattis, longincsubseq
 * Time: $O(N \log N)$
 */
template<class I> vector<int> lis(const vector<I>& S) {
	if (S.empty()) return {};
	vector<int> prev(S.size());
	using p = pair<I, int>; vector<p> res;
	for(int i = 0; i < (int)S.size(); i++) {
		// change 0 -> i for longest non-decreasing subsequence
		auto it = lower_bound(res.begin(), res.end(), p {S[i], 0}); 
		if (it == res.end()) res.emplace_back(), it = res.end()-1;
		*it = {S[i], i};
		prev[i] = it == res.begin() ? 0 : (it-1)->second; 
	}
	int L = res.size(), cur = res.back().second;
	vector<int> ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
}
