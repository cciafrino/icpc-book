/**
 * Author: LeticiaFCS
 * Date: 2020-03-07
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, KACTL
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code supports commutative segtree modifications/queries on paths, edges and subtrees.
 * Takes as input the full adjacency list with pairs of (vertex, value). USE\_EDGES being true means that
 * values are stored in the edges and are initialized with the adjacency list, otherwise values are
 * stored in the nodes and are initialized to the T defaults value.
 * Time: $O((\log N)^2)$
 * Status: Tested on codeforces 101908L and 101807J
 */
#include "../data-structures/LazySegmentTree.h" 
using G = vector<vector<pair<int,int>>>;
template<typename T, bool USE_EDGES> struct heavylight_t {
	int t, n;
	vector<int> timer, preorder;
	vector<int> chain, par;
	vector<int> dep, sz;
	vector<T> val;
	heavylight_t() {}
	heavylight_t(G &g, int r = 0) : t(0), n(g.size()), par(n, -1), chain(n, -1), 
	dep(n), timer(n), sz(n),  val(n), preorder(n) { par[r] = chain[r] = r;
		dfs_sz(g, r), dfs_hld(g, r);  
	}
	int dfs_sz(G &g, int u) { 
		int subtree = 1;
		for(auto &e : g[u]) {
			int v = e.first;
			if (par[v] != -1) continue;
			par[v] = u; dep[v] = dep[u] + 1;
			subtree += dfs_sz(g, v);
			if (sz[v] > sz[g[u][0].first]) swap(g[u][0], e);
		}
		return sz[u] = subtree;
	}
	void dfs_hld(G &g, int u) {
		preorder[timer[u] = t++] = u;
		for (auto &e : g[u]) {
			int v = e.first;
			if (chain[v] != -1) continue;
			chain[v] = (e == g[u][0] ? chain[u] : v);
			dfs_hld(g, v);
			if (USE_EDGES) val[timer[v]] = e.second;
		}
	}
	template<class F> void path(int u, int v, F op) {
		if (u == v) return op(timer[u], timer[u]); 
		for(int e, p; chain[u] != chain[v]; u = p) {
			if (dep[chain[u]] < dep[chain[v]]) swap(u,v);
			u == (p = chain[u]) ? e = 0, p = par[u] : e = 1;
			op(timer[chain[u]] + e, timer[u]);
		}
		if (timer[u] > timer[v]) swap(u, v);
		op(timer[u] + USE_EDGES, timer[v]);
	}
};

template<typename T, bool USE_EDGES> struct hld_solver {
	heavylight_t<T, USE_EDGES> h;
	segtree_lz<decltype(F), decltype(US),decltype(UY), node, T> seg;
	hld_solver(const heavylight_t<T, USE_EDGES> &g) : h(g),
	seg(h.val.size(), F, US, UY, {'n', 0}, 0) {
		for(int i=0; i < int(h.val.size()); i++)
			seg.at(i) = h.val[i];
		seg.build();
	}
	void updatePath(int u, int v, T value) {
		h.path(u, v, [&](int a,int b) { seg.query(a, b+1, {'a', value}); });
	}
	T queryPath(int u, int v) { 
		T ans = 0;
		h.path(u, v, [&](int a,int b) { ans += seg.query(a, b+1, {'n', 0}); });
		return ans;
	}
	void updateEdge(int u, int v, T value) {
		int pos = h.timer[h.dep[u] < h.dep[v] ? v : u];
		seg.query(pos, pos+1, {'a', value});
	}
	T querySubtree(int v) { 
		return seg.query(h.timer[v] + USE_EDGES, h.timer[v] + h.sz[v], {'n', 0});
	}
	void updateSubtree(int v, T value) {
		seg.query(h.timer[v] + USE_EDGES, h.timer[v] + h.sz[v], {'a', value});
	}
};

template<typename T, bool USE_EDGES> struct lca_t { // lca operations using hld
	heavylight_t<T, USE_EDGES> h;
	lca_t(const heavylight_t<T, USE_EDGES> &g) : h(g) {}
	int kth_ancestor(int u, int k) const {	
		int kth = u;
		for(int p = h.chain[kth]; k && h.timer[kth]; kth = p, p = h.chain[kth]) {
			if (p == kth) p = h.par[kth];
			if (h.dep[kth] - h.dep[p] >= k) p = h.preorder[h.timer[kth]-k];
			k -= (h.dep[kth] - h.dep[p]);
		}
		return (k ? -1 : kth);
	}
	int lca(int u, int v) {
		if (u == v) return u;
		int x = h.timer[u];
		h.path(u, v, [&](int a,int b) { x = a - USE_EDGES; });
		return h.preorder[x];
	}
	int kth_on_path(int u, int v, int k) { //k 0-indexed
		int x = lca(u,v);		
		if (k > h.dep[u] + h.dep[v] - 2 * h.dep[x]) return -1;
		if (h.dep[u] - h.dep[x] > k) return kth_ancestor(u, k);
		return kth_ancestor(v, h.dep[u] + h.dep[v] - 2 * h.dep[x] - k );	
	}
};
