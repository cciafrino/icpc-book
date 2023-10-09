/**
 * Author:
 * Date: 
 * License: 
 * Source: UFMG & https://www.slideshare.net/KuoE0/acmicpc-tree-isomorphism
 * Description: 
 * Time: O(N\log(N))
 * Status: Tested on CSES Tree Isomorphism II
 */
struct tree_t {
	vector<int> cen, sz;
	vector<vector<int>> adj;
	tree_t(vector<vector<int>>& g):cen(2), sz(g.size()), adj(g){}
	int dfs_sz(int v, int p) {
		sz[v] = 1;
		for (int u : adj[v]) if (u != p)
			sz[v] += dfs_sz(u, v);
		return sz[v];
	}
	int dfs(int tsz, int v, int p) {
		for (int u : adj[v]) if (u != p) {
			if (2*sz[u] <= tsz) continue;
			return dfs(tsz, u, v);
		} return cen[0] = v;
	}
	void find_cenroid(int v) {
		int tsz = dfs_sz(v, -1);
		cen[1] = dfs(tsz, v, -1);
		for (int u : adj[cen[0]]) if (2*sz[u] == tsz)
			cen[1] = u;
	}
	int hash_it(int v, int p = -1) {
    	static map<vector<int>, int> val;
		vector<int> offset;
		for (int u : adj[v]) if (u != p)
			offset.push_back(hash_it(u, v));
		sort(offset.begin(), offset.end());
		if (!val.count(offset))  val[offset] = int(val.size());
		return val[offset];
	}
	ll get_hash(int v = 0) {
		find_cenroid(v);
		ll x = hash_it(cen[0]), y=hash_it(cen[1]);
		if (x > y) swap(x, y);
		return (x << 30) + y;
	}
};
