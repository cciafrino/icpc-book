/**
 * Author: Chris
 * Description: Maximum Matching for general graphs (undirected and non bipartite) using 
 * a crazy chinese heuristic(Yet to find any counter case). one-indexed based implementation, 
 * be careful. $it$ represents how many iterations you wanna try, something between [5, 500] suffice. 
 * Usage:GeneralMatching G(N+1); G.addEdge(a+1, b+1); int max_matching = G.solve(5);
 * Status: tested for $n \leq 1000$
 * Time: $O(EV)$ 
 */
#include"../various/RandomNumbers.h"
struct GeneralMatching {
	int N, T;
	vector<vector<int>> edges;
	vector<int> seen, match;
	GeneralMatching(int _N) : N(_N), T(0), edges(N), seen(N), match(N) {} 
	void addEdge(int a, int b) { // one-based!
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	bool dfs(int v) {
		if (v == 0) return true;
		seen[v] = T;
		shuffle(edges[v].begin(), edges[v].end(), rng);
		for (int u : edges[v]) {
			int to = match[u];
			if (seen[to] < T) {
				match[v] = u, match[u] = v, match[to] = 0;
				if (dfs(to)) return true;
				match[u] = to, match[to] = u, match[v] = 0;
			}
		}
		return false;
	}
	int solve(int it) {
		int res = 0;
		for (int t = 0; t < it; ++t) {
			for (int i = 1; i < N; ++i) {
				if (match[i]) continue;
				++T;
				res += dfs(i);
			}
		}
		return res;
	}
	vector<array<int, 2>> get_edges(int it) {
		int ma = solve(it);
		vector<array<int, 2>> E; E.reserve(ma);
		for (int i = 1; i < N; ++i) {
			if (i > match[i] || match[i] <= 0) continue;
			E.push_back({i-1, match[i]-1});
		}
		return E;
	}
};
