/**
 * Author: Chris
 * Description: Kosaraju's Algorithm, DFS twice to generate 
 	* strongly connected components in topological order. $a, b$
 	* in same component if both $a\to b$ and $b\to a$ exist.
 * Time: $O(V+E)$
 * Source: Matt Fountaine
 * Status:
 */
struct Kosaraju_t {
	int n;
	vector<vector<int>> edges, redges;
	vector<bool> seen;
	vector<int> cnt_of, cnts;
	Kosaraju_t(const int &N) : n(N), edges(N), redges(N), seen(N), cnt_of(N, -1) {}
	void addEdge(int a, int b) {
		edges[a].push_back(b);
		redges[b].push_back(a);
	}
	void dfs(int v) {
		seen[v] = true;
		for (int u : edges[v]) {
			if (seen[u]) continue;
			dfs(u);
		}
		toposort.push_back(v);
	}
	void dfs_fix(int v, int w) {
		cnt_of[v] = x;
		for (int u : redges[v]) {
			if (cnt_of[u] == -1) dfs_fix(u, w);
		}
	}
	void solve() {
		for (int i = 0; i < n; ++i) 
			if (seen[i] == false) dfs(i);
		reverse(toposort.begin(), toposort.end());
		for (int u : toposort) {
			if (cnt_of[u] != -1) continue;
			dfs_fix(u, u);
			cnts.push_back(u);
		}
	}
};