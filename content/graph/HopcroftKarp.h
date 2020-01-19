/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Fast bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Usage: vector<int> btoa(m, -1); hopcroftKarp(g, btoa);
 * Status: Tested on oldkattis.adkbipmatch and SPOJ:MATCHING
 * Time: O(\sqrt{V}E)
 */
#pragma once

bool dfs(int a, int layer, const vector<vector<int>> &g, vector<int> &btoa, vector<int> &A, vector<int> &B) { /// start-hash
	if (A[a] != layer) return 0;
	A[a] = -1;
	for(auto &b : g[a]) if (B[b] == layer + 1) {
		B[b] = -1;
		if (btoa[b] == -1 || dfs(btoa[b], layer+2, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}/// end-hash

int hopcroftKarp(const vector<vector<int>> &g, vector<int> &btoa) { /// start-hash
	int res = 0;
	vector<int> A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(A.begin(), A.end(), 0);
		fill(B.begin(), B.end(), -1);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for(auto &a : btoa) if(a != -1) A[a] = -1;
		for (int a = 0; a < g.size(); ++a) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay += 2) { 
			bool islast = 0;
			next.clear();
			for(auto &a : cur) for(auto &b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && B[b] == -1) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for(auto &a : next) A[a] = lay+1;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		for(int a = 0; a < g.size(); ++a) 
			res += dfs(a, 0, g, btoa, A, B);
	}
} /// end-hash
