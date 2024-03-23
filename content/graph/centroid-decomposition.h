/**
 * Author: Chris
 * Description: 
 * Status: somewhat tested
 * 
 */
struct centroid_tree {
	int N;
	vector<pair<int, int>> max_sub;
	vector<vector<int>> dist, adj;
	vector<int> depth, par;
	vector<bool> deleted;
	centroid_tree(const auto& G) : N(G.size()), adj(G), depth(N),
		par(N,-1), deleted(N), dist(__lg(N)+1, vector(N,0)), max_sub(N) {
			rec(0, -1, 0);
		}
	int dfs(int cur, int prv) {
		int sz = 1;
		max_sub[cur] = {0, -1};
		for (int nxt : adj[cur]) {
			if (nxt == prv || deleted[nxt]) continue;
			int cur_sz = dfs(nxt, cur);
			sz += cur_sz;
			max_sub[cur] = max(max_sub[cur], {cur_sz, nxt});
		}
		return sz;
	}
	void layer(int cur, int prv, int lvl) {
		for (int nxt : adj[cur]) {
			if (nxt == prv || deleted[nxt]) continue;
			dist[lvl][nxt] = dist[lvl][cur] + 1;
			layer(nxt, cur, lvl);
		}
	}
	void rec(int cur, int prv, int d) {
		int sz = dfs(cur, prv);
		while(max_sub[cur].first > sz/2) cur = max_sub[cur].second;
		depth[cur] = d;
		par[cur] = prv;
		layer(cur, prv, d);
		deleted[cur] = true;
		for (int nxt : adj[cur]) {
			if (deleted[nxt]) continue;
			rec(nxt, cur, d + 1);
		}
	}
};