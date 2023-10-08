/**
 * Author: Chris
 * Date: 2023
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, KACTL
 * Description: 
 * Time: $O((\log N)^2)$
 * Status: Tested on codeforces 101908L and 101807J
 * Details:  Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code supports commutative segtree modifications/queries on paths, edges and subtrees.
 * Takes as input the full adjacency list with pairs of (vertex, value). USE\_EDGES being true means that
 * values are stored in the edges and are initialized with the adjacency list, otherwise values are
 * stored in the nodes and are initialized to the T defaults value.
 */
#include "../data-structures/lazy-segtree.h" 
template<bool use_edges> struct hld_t {
	int N, T{};
	vector<vector<int>> adj;
	vector<int> sz, depth, chain, par, in, out, preorder;
	hld_t() {}
	hld_t(const vector<vector<int>>& G, int r = 0) : N(int(G.size())),
	adj(G), sz(N), depth(N), chain(N), par(N), in(N), out(N),
	preorder(N) { dfs_sz(r); chain[r] = r; dfs_hld(r); }
	void dfs_sz(int cur) {
		sz[cur] = 1;
		for (auto& nxt : adj[cur]) {
			par[nxt] = cur; depth[nxt] = 1 + depth[cur];
			adj[nxt].erase(find(adj[nxt].begin(), adj[nxt].end(), cur));
			dfs_sz(nxt); sz[cur] += sz[nxt];
			if (sz[nxt] > sz[adj[cur][0]]) swap(nxt, adj[cur][0]);
		}
	}
	void dfs_hld(int cur) {
		in[cur] = T++; preorder[in[cur]] = cur;
		for (auto& nxt : adj[cur]) {
			chain[nxt] = (nxt == adj[cur][0] ? chain[cur] : nxt);
			dfs_hld(nxt);
		} out[cur] = T;
	}
	int lca(int a, int b) {
		while (chain[a] != chain[b]) {
			if (in[a] < in[b]) swap(a, b);
			a = par[chain[a]];
		} return (in[a] < in[b] ? a : b);
	}
	bool is_ancestor(int a, int b) { return in[a] <= in[b] && in[b] < out[a]; }
	int climb(int a, int k) {
		if (depth[a] < k) return -1;
		int d = depth[a] - k;
		while (depth[chain[a]] > d) a = par[chain[a]];
		return preorder[in[a] - depth[a] + d];
	}
	int kth_on_path(int a, int b, int K) {
		int m = lca(a, b);
		int x = depth[a] - depth[m], y = depth[b] - depth[m];
		if (K > x + y) return -1;
		return (x > K ? climb(a, K) : climb(b, x + y - K));
	}
	// bool is true if path should be reversed (only for noncommutative operations)
	const vector<tuple<bool, int, int>>& get_path(int a, int b) const {
		static vector<tuple<bool, int, int>> L, R;
		L.clear(); R.clear();
		while (chain[a] != chain[b])
			if (depth[chain[a]] > depth[chain[b]]) {
				L.push_back({true, in[chain[a]], in[a] + 1});
				a = par[chain[a]];
			} else {
				R.push_back({false, in[chain[b]], in[b] + 1});
				b = par[chain[b]];
			}
		if (depth[a] > depth[b]) 
			L.push_back({true, in[b] + use_edges, in[a] + 1});
		else R.push_back({false, in[a] + use_edges, in[b] + 1});
		L.insert(L.end(), R.rbegin(), R.rend());
		return L;
	}
};
