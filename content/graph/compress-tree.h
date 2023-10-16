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
auto compressTree(hld_t<false> &h, vector<int> sb) {
	static vector<int> rev; rev.resize(h.T);
	auto cmp = [&](int a, int b){ return h.in[a] < h.in[b]; };
	sort(sb.begin(), sb.end(), cmp);
	for (int i = 0 , m = sb.size() - 1 ; i < m ; ++i)
		sb.push_back(h.lca(sb[i], sb[i+1]));
	sort(sb.begin(), sb.end(), cmp);
	sb.erase(unique(sb.begin(), sb.end()), sb.end());
	for (int i = 0; i < int(sb.size()); ++i) rev[sb[i]] = i;
	vector<pii> ret = { {0, sb[0]} };
	for (int i = 0; i + 1 < int(sb.size()); ++i)
		ret.emplace_back(rev[h.lca(sb[i], sb[i+1])], sb[i+1]);
	return ret;
}
