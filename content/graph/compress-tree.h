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
#include "LCA.h"
vector<pair<int,int>> compressTree(lca_t &lca, const vector<int>& subset) {
	static vector<int> rev; rev.resize(lca.time.size());
	vector<int> li = subset, &T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; };
	sort(li.begin(), li.end(), cmp);
	int m = li.size()-1;
	for (int i = 0; i < m; ++i) {
		int a = li[i], b = li[i+1];
		li.push_back(lca.lca(a, b));
	}
	sort(li.begin(), li.end(), cmp);
	li.erase(unique(li.begin(), li.end()), li.end());
	for (int i = 0; i < int(li.size()); ++i) rev[li[i]] = i;
	vector<pair<int,int>> ret = {{0, li[0]}};
	for (int i = 0; i < li.size()-1; ++i) {
		int a = li[i], b = li[i+1];
		ret.emplace_back(rev[lca.lca(a, b)], b);
	} return ret;
}
