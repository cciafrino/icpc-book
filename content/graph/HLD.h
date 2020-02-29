/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template <bool VALS_EDGES> struct HLD {
	int N, t = 0;
	vector<vector<int>> edges;
	vector<int> par, size, depth, rt, pos;
	// Node *tree;
	segtree_t<int,int> tree;
	HLD(vector<vector<int>> adj_)
		: N(adj_.size()), edges(adj_), par(N, -1), size(N, 1), depth(N),
		  rt(N),pos(N), tree(N) { dfs_sz(),dfs_hld();}
	void dfs_sz(int v = 0) {
		if (par[v] != -1) 
			edges[v].erase(find(edges[v].begin(), edges[v].end(), par[v]));
		for(auto &u : edges[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfs_sz(u);
			size[v] += size[u];
			if (size[u] > size[edges[v][0]]) swap(u, edges[v][0]);
		}
	}
	void dfs_hld(int v = 0) {
		pos[v] = t++;
		for(auto &u : edges[v]) {
			rt[u] = (u == edges[v][0] ? rt[v] : u);
			dfs_hld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v]);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v]);
	}
	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree.update(l, r, val); });
	}
	int queryPath(int u, int v) { // Modify depending on query
		int res = -1e9;
		process(u, v, [&](int l, int r) {
				res = max(res, tree.query(l, r));
		});
		return res;
	}
	int querySubtree(int v) { // modifySubtree is similar
		return tree.query(pos[v] + VALS_EDGES, pos[v] + size[v] - 1);
	}
	void modifySubtree(int v, int delta) {
		tree.update(pos[v] + VALS_EDGES, pos[v] + size[v] - 1, delta);
	}
};
