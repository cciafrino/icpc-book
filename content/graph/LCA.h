/**
 * Author: Johan Sannemo, Simon Lindholm, Chris
 * Date: 2015-09-20
 * License: CC0
 * Source: Folklore
 * Status: Somewhat tested
 * Description: Data structure for computing lowest common
 * ancestors in a tree (with 0 as root). C should be an adjacency list of the tree,
 * either directed or undirected.
 * Can also find the distance between two nodes.
 * Usage:
 *  lca_t lca(undirGraph);
 *  lca.query(firstNode, secondNode);
 *  lca.dist(firstNode, secondNode);
 * Time: $O(N \log N + Q)$
 */
#pragma once

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) {
		int N = V.size(), on = 1, depth = 1;
		while (on < N) on *= 2, depth++;
		jmp.assign(depth, V);
		for(int i = 0; i < depth-1; ++i) for(int j = 0; j < N; ++j)
			jmp[i+1][j] = min(jmp[i][j],
			jmp[i][min(N - 1, j + (1 << i))]);
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct lca_t {
	int n;
	vector<int> depth, order;
	vector<vector<int>> edges;
	vector<pair<int,int>> temp;
	RMQ<pair<int,int>> rmq;
	lca_t(vector<vector<int>>& g) : n(g.size()), 
	edges(g), depth(n), order(n), rmq(dfs(0,-1)) {}
	vector<pair<int,int>> dfs(int v, int p) {
		order[v] = temp.size();
		depth[v] = 1 + depth[p];
		temp.push_back({depth[v], v});
		for (int u : edges[v]) {
			if (u == p) continue;
			dfs(u, v);
			temp.push_back({depth[v], v});
		}
		return temp;
	}
	int query(int a, int b) {
		a = order[a]; b = order[b];
		if (a > b) swap(a, b);
		return rmq.query(a, b).second;
	}
	int dist(int a, int b) {
		return depth[a] + depth[b] - 2*depth[query(a, b)];
	}
};
