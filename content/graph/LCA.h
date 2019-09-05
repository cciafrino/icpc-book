/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2015-09-20
 * License: CC0
 * Source: Folklore
 * Status: Somewhat tested
 * Description: Data structure for computing lowest common
 * ancestors in a tree (with 0 as root). C should be an adjacency list of the tree,
 * either directed or undirected.
 * Can also find the distance between two nodes.
 * Usage:
 *  LCA lca(undirGraph);
 *  lca.query(firstNode, secondNode);
 *  lca.distance(firstNode, secondNode);
 * Time: $O(N \log N + Q)$
 */
#pragma once

typedef vector<vector<pair<int,int>>> graph;

#include "../data-structures/RMQ.h"

struct LCA {
	vector<int> time;
	vector<lint> dist;
	RMQ<pair<int,int>> rmq;
	LCA(graph &C) : time(C.size(), -99), dist(C.size()), rmq(dfs(C)) {}
	vector<pair<int,int>> dfs(graph &C) {
		vector<tuple<int, int, int, lint>> q(1);
		vector<pair<int,int>> ret;
		int T = 0, v, p, d; lint di;
		while (!q.empty()) {
			tie(v, p, d, di) = q.back();
			q.pop_back();
			if (d) ret.emplace_back(d, p);
			time[v] = T++;
			dist[v] = di;
			for(auto &e : C[v]) if (e.first != p)
				q.emplace_back(e.first, v, d+1, di + e.second);
		}
		return ret;
	}
	int query(int a, int b) {
		if (a == b) return a;
		a = time[a], b = time[b];
		return rmq.query(min(a, b), max(a, b)).second;
	}
	lint distance(int a, int b) {
		int lca = query(a, b);
		return dist[a] + dist[b] - 2 * dist[lca];
	}
};
