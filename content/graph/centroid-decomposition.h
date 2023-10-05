/**
 * Author: Chris
 * Description: Divide and Conquer on Trees.
 * Status: Tested on CSES2080
 * 
 */
template<typename T> struct centroid_t {
	int N;
	vector<vector<int>> adj; 
	vector<vector<int>> dist; // dist to all ancestors
	vector<bool> blocked; // processed centroid
	vector<int> sz, depth, parent; // centroid parent
	centroid_t(int _n) : N(_n), adj(_n), dist(32 - __builtin_clz(_n), vector<int>(_n)), 
	blocked(_n), sz(_n), depth(_n), parent(_n) {}
	void add_edge(int a, int b) {
		adj[a].push_back(b); adj[b].push_back(a);
	}
	void dfs_sz(int cur, int prv) {
		sz[cur] = 1;
		for (int nxt : adj[cur]) {
			if (nxt == prv || blocked[nxt]) continue;
			dfs_sz(nxt, cur); sz[cur] += sz[nxt];
		}
	}
	int find(int cur, int prv, int tsz) { 
		for (int nxt : adj[cur]) 
			if (!blocked[nxt] && nxt != prv && 2*sz[nxt] > tsz) 
				return find(nxt, cur, tsz);
		return cur;
	}
	void dfs_dist(int cur, int prv, int layer, int d) {
		dist[layer][cur] = d;
		for (int nxt : adj[cur]) {
			if (blocked[nxt] || nxt == prv) continue;
			dfs_dist(nxt, cur, layer, d + 1);
		}
	}
	void get_path(int cur, int prv, int d,vector<int>& cur_path){
		cur_path.push_back(d);
		for (int nxt : adj[cur]) {
			if (nxt == prv || blocked[nxt]) continue;
			get_path(nxt, cur, d + 1, cur_path);
		}
	} 
	// solve for each subtree (cnt := # of paths of length K 
	// that goes through vertex cur)
	T solve_subtree(int cur, int prv, int K) {
		vector<T> dp(sz[prv] + 1); dp[0] = 1;
		T cnt = 0;
		for (int nxt : adj[cur]) {
			if (blocked[nxt]) continue;
			vector<int> path; get_path(nxt, cur, 1, path);
			for (int d : path) {
				if (d > K || K - d > sz[prv]) continue;
				cnt += dp[K - d];
			}
			for (int d : path) dp[d] += 1;
		} return cnt;
	}
	T decompose(int cur, int K, int layer=0, int prv_root = -1){
		dfs_sz(cur, -1);
		int root = find(cur, cur, sz[cur]);
		blocked[root] = true; depth[root] = layer;
		parent[root] = prv_root; dfs_dist(root, root, layer, 0);
		T res = solve_subtree(root, cur, K);
		for (int nxt : adj[root]) {
			if (blocked[nxt]) continue;
			res += decompose(nxt, K, layer + 1, root);
		} return res;
	}
};
