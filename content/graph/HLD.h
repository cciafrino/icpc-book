/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Supports any segtree modifications/queries on paths and
 * subtrees. Takes as input the full adjacency list.
 * Status: Will do in morning
 */
#pragma once

#include "../data-structures/DynamicSegTree.h"

template<bool USE_EDGES> struct HLD {
	int N;
	vector<vector<int>> edges;
	vector<int> par, sz, depth, rt, pos;
	node *tree;
	HLD(vector<vector<int>> g)
		: N(g.size()), edges(g), par(N, -1), sz(N, 1), depth(N),
		  rt(N), pos(N) { dfs_sz(),dfsHld(); tree = build(0, n-1); }
	void dfs_sz(int v = 0) {
		if (par[v] != -1) 
			edges[v].erase(find(edges[v].begin(), edges[v].end(), par[v]));
		for(int u : edges[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfs_sz(u);
			sz[v] += sz[u];
			if (sz[u] > sz[edges[v][0]]) swap(u, edges[v][0]);
		}
	}
	int t = 0;
	void dfsHld(int v = 0) {
		pos[v] = t++;
		for(int u : edges[v]) {
			rt[u] = (u == edges[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u] + USE_EDGES, pos[v] + 1);
	}
	void modifyPath(int u, int v, int delta) {
		process(u, v, [&](int l, int r) { upd(tree, l, r, delta); });
	}
	int queryPath(int u, int v) {
		int res = 0;
		process(u,v,[&](int l, int r) { res+=query(tree,l,r); });
		return res;
	}
	void modifySubtree(int v, int delta) {
		upd(tree, pos[v] + USE_EDGES, pos[v]+sz[v]-1, delta);
	}
	int querySubtree(int v) { 
		return query(tree, pos[v] + USE_EDGES, pos[v] + sz[v]);
	}
};