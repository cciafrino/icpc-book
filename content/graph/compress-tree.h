/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Status: Tested at CodeForces
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns a list of (par, orig\_index) representing a tree rooted at 0.
 * The root points to itself.
 * Time: $O(|S| \log |S|)$
 */
#include "heavylight.h"
template<bool T> auto compressTree(hld_t<T> &h, vector<int> s){
	static vector<int> rev; rev.resize(h.T);
	auto cmp = [&](int a, int b){ return h.in[a] < h.in[b]; };
	sort(s.begin(), s.end(), cmp); int m = int(s.size())-1;
	for (int i = 0; i < m; ++i)
		s.push_back(h.lca(s[i], s[i+1]));
	sort(s.begin(), s.end(), cmp);
	s.erase(unique(s.begin(), s.end()), s.end());
	for (int i = 0; i < int(s.size()); ++i) rev[s[i]] = i;
	vector<pii> ret = { {0, s[0]} };
	for (int i = 0; i + 1 < int(s.size()); ++i)
		ret.emplace_back(rev[h.lca(s[i], s[i+1])], s[i+1]);
	return ret;
}
