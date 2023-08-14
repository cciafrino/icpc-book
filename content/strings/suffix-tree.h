/**
 * Author: Chris
 * Description: Builds suffix-tree informations based by emulating it over the suffix-array and lcp,
 * root of the tree represents the special character (size of string for suffix-array), can therefore be ignored when
 * calculating stuff.
 * Status: tested on cf (802I - FakeNews Hard) and (305539 G)
 * Time: $O(N \log N)$
 */
#include<../data-structures/rmq.h>
#include"suffix-array.h"
struct suffix_tree_t {
	int N, V;
	vector<vector<int>> ch;
	vector<array<int, 2>> sa_range;
	vector<int> leaves, par, depth;
	vector<int> suff_link;
	vector<bool> is_unique_link, has_unique_child;
	suffix_array_t us;
	suffix_tree_t() {}
	suffix_tree_t(string S) : N(int(S.size())), V(0), ch(2*N+1),
	sa_range(2*N+1), leaves(N+1), par(2*N+1), depth(2*N+1), 
	us(S.begin(), S.end()) { dfs(0, N+1, -1); }
	void dfs(int a, int b, int prv) {
		int cur = V++;
		par[cur] = prv;
		if (prv != -1) ch[prv].push_back(cur);
		sa_range[cur] = {a, b};
		if (b - a == 1) {
			leaves[us.sa[a]] = cur;
			depth[cur] = N - us.sa[a];
		} else {
			int d = us.get_split(a, b).first;
			depth[cur] = d;
			int mi = a;
			while (b - mi >= 2) {
				auto [nd, nmi] = us.get_split(mi, b);
				if (nd != d) break;
				dfs(mi, nmi, cur);
				mi = nmi;
			}
			dfs(mi, b, cur);
		}
	}
	void build_links() {
		suff_link.resize(V, -1), is_unique_link.resize(V), has_unique_child.resize(V);
		for (int i = 0; i < N; ++i) {
			for (int cur = leaves[i], link = leaves[i+1];; cur = par[cur]) {
				if (cur == 0 || suff_link[cur] != -1) break;
				suff_link[cur] = link;
				is_unique_link[cur] = (sa_range[cur][1] - sa_range[cur][0]) == (sa_range[link][1] - sa_range[link][0]);
				if (is_unique_link[cur]) has_unique_child[link] = true;
				while (~link && depth[link] + 1 > depth[par[cur]]) link = par[link];
			}
		}
	}
};
