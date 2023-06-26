/**
 * Author: Lucian Bicsi, Chris, Daniel Rutschmann
 * Date: 
 * License: 
 * Source:
 * Description: Fast Kuhn! Simple maximum cardinality bipartite matching algorithm. 
 * Better than hopcroftKarp in practice. 
 * Worst case is $O(VE)$ on an hairy tree. Shuffling the
 * edges and vertices ordering should break some worst-case inputs.
 * Time: $\Omega(VE)$ 
 * Usage: 
 * Status: stress-tested
 */
struct bipartite_matching {
	int N, M, T;
	vector<vector<int>> adj;
	vector<int> match, seen;
	bipartite_matching(int a, int b) : N(a), M(a + b), adj(M), 
	match(M, -1), seen(M, -1), T(0) {}
	void add_edge(int a, int b) {
		assert(0 <= a && a < N && b + N < M && N <= b + N);
		adj[a].push_back(b + N);
	}
	void shuffle_edges() { // useful to break some hairy tests
		mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
		for (auto& cur : adj)
			shuffle(cur.begin(), cur.end(), rng);
	} 
	bool dfs(int cur) {
		if (seen[cur] == T) return false;
		seen[cur] = T;
		for (int nxt : adj[cur]) 
			if (match[nxt] == -1) {
				match[nxt] = cur, match[cur] = nxt;
				return true;
			}
		for (int nxt : adj[cur]) 
			if (dfs(match[nxt])) {
				match[nxt] = cur, match[cur] = nxt;
				return true;
			}
		return false;
	}
	int solve() {
		int res = 0;
		while (true) {
			int cur = 0; ++T;
			for (int i = 0; i < N; ++i) 
				if (match[i] == -1) cur += dfs(i);
			if (cur == 0) break;
			else res += cur;
		}
		return res;
	}
};
