/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: BenQ
 * Status: Not tested
 * Description: Euler Tour LCA 
 * Time: $O(1)$
 */
#include<RMQ.h>

struct lca_t {
	int n, r = 1;
	vector<int> depth, order;
	vector<vector<int>> edges;
	vector<pair<int,int>> temp;
	RMQ<pair<int,int>> rmq;
	lca_t(int _n) : n(_n), edges(n), depth(n), order(n) { }
	void addEdge(int a, int b) {
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	void dfs(int v, int p) {
		order[v] = temp.size();
		depth[v] = 1 + depth[p];
		temp.push_back({depth[v], v});
		for (int u : edges[v]) {
			if (u == p) continue;
			dfs(u, v);
			temp.push_back({depth[v], v});
		}
	}
	void build(int n) {
		dfs(r, 0); 
		rmq = RMQ<pair<int,int>>(temp);
	}
	int query(int a, int b) {
		a = order[a];
		b = order[b];
		if (a > b) swap(a, b);
		return rmq.query(a, b).second;
	}
	int dist(int a, int b) {
		return depth[a] + depth[b] - 2*depth[query(a, b)];
	}
};