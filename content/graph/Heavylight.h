/**
 * Author: LeticiaFCS
 * Date: 2020-03-07
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, KACTL
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code supports commutative segtree modifications/queries on paths, edges and subtrees.
 * Takes as input the full adjacency list with pairs of (vertex, value). USE_EDGES being true means that
 * values are stored in the edges and are initialized with the adjacency list, otherwise values are
 * stored in the nodes and are initialized to the T defaults value.
 * Time: O((\log N)^2)
 * Status: Tested on codeforces 101908L and 101807J
 */
#include "../data-structures/SegTree.h" 
typedef vector<vector<pair<int,int>>> adj;
template<typename T, bool USE_EDGES>
struct HLD {
	int t{0}, n;
	vector<int> in, par, chain, sz, dep;
	vector<T> val;
 	tree_t<T> seg; 
	HLD(adj &g, int r = 0) : n(g.size()), par(n,-1), 
	chain(n,-1), dep(n), in(n), sz(n),  val(n){ 
		par[r] = chain[r] = r;
		dfs_sz(g, r), dfs_hld(g, r); 
		seg = {val}; 
	}
	void f(T &a, T b){ a = max(a,b); } 
	T query(int a, int b) { return seg.query(a, b+1); }
	void update(int a, T value) { seg.update(a, value); }
	void update(int a, int b, T value) { }
	void dfs_sz(adj &g, int u) { 
		sz[u]++;
		for(auto &e : g[u]) {
			int v = e.first;
			if(par[v] == -1) {
				par[v] = u; dep[v] = dep[u] + 1;
				dfs_sz(g, v);
				sz[u] += sz[v]; 
				if (par[u] == g[u][0].first || sz[v] > sz[g[u][0].first])
					swap(g[u][0], e);
			}
		}
	}
	void dfs_hld(adj &g, int u) {
		in[u] = t++;
		for (auto &e : g[u]) {
			int v = e.first;
			if (chain[v] == -1) {
				if (e == g[u][0]) chain[v] = chain[u];
				else chain[v] = v;
				dfs_hld(g, v);
				if (USE_EDGES) val[in[v]] = e.second;
			}
		}
	}
	void path(int u, int v, function<void(int,int)> func){
		if (u == v){ return func(in[u],in[u]);}
		for(int e, p; chain[u] != chain[v]; u = p){
			if (dep[chain[u]] < dep[chain[v]]) swap(u,v);
			e = 1, p = chain[u];
			if(u == p) e = 0, p = par[u];
			func(in[chain[u]] + e, in[u]);
		}
		if (in[u] > in[v]) swap(u, v);
		func(in[u] + USE_EDGES, in[v]);
	}
	void update_path(int u, int v, T value){
		path(u, v, [&](int a,int b){ update(a, b, value); });
	}
	T query_path(int u, int v) {
		T ans = -(1<<29);
		path(u, v, [&](int a,int b){ f(ans, query(a, b)); });
		return ans;
	}
	void update_edge(int u, int v, T value) {
		if (dep[u] < dep[v]) u = v;
		update(in[u], value);
	}
	T query_subtree(int v) { 
		return query(in[v] + USE_EDGES, in[v] + sz[v]);
	}
	void update_subtree(int v, T value) {
		update(in[v] + USE_EDGES, in[v] + sz[v], value);
	}
};
