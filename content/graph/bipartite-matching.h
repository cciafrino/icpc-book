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
 * Status: stress-tested and tested on library-checker
 */
struct bm_t {
	int N, M, T;
	vector<vector<int>> adj;
	vector<int> match, seen;
	bm_t(int a, int b) : N(a), M(a+b), T(0), adj(M),
	match(M, -1), seen(M, -1) {}
	void add_edge(int a, int b) { adj[a].push_back(b + N); }
	bool dfs(int cur) { ///start-hash
		if (seen[cur] == T) return false;
		seen[cur] = T;
		for (int nxt : adj[cur]) if (match[nxt] == -1) {
			match[nxt] = cur, match[cur] = nxt;
			return true;
		}
		for (int nxt : adj[cur]) if (dfs(match[nxt])) {
			match[nxt] = cur, match[cur] = nxt;
			return true;
		}
		return false;
	} ///end-hash
	int solve() { ///start-hash
		int res = 0;
		for (int cur = 1; cur; ) {
			cur = 0; ++T;
			for (int i = 0; i < N; ++i) if (match[i] == -1)
				cur += dfs(i);
			res += cur;
		}
		return res;
	} ///end-hash
};
