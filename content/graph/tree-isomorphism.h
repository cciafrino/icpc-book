/**
 * Author:
 * Date: 
 * License: 
 * Source: UFMG & https://www.slideshare.net/KuoE0/acmicpc-tree-isomorphism
 * Description: 
 * Time: O(N\log(N))
 * Status: not tested
 */
map<vector<int>, int> val;
struct tree_t {
	int n;
	pair<int,int> centroid;
	vector<vector<int>> adj; vector<int> sz;
	tree_t(vector<vector<int>>& gr) : adj(gr), sz(adj.size()){}
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
		} return centroid.first = v;
	}
	pair<int,int> find_centroid(int v) {
		int tsz = dfs_sz(v, -1);
		centroid.second = dfs(tsz, v, -1);
		for (int u : adj[centroid.first]) if (2*sz[u] == tsz)
			centroid.second = u;
		return centroid;
	}
	int hash_it(int v, int p) {
		vector<int> offset;
		for (int u : adj[v]) if (u != p)
			offset.push_back(hash_it(u, v));
		sort(offset.begin(), offset.end());
		if (!val.count(offset))  val[offset] = int(val.size());
		return val[offset];
	}
	ll get_hash(int v = 0) {
		pair<int,int> cent = find_centroid(v);
		ll x = hash_it(cent.first,-1), y=hash_it(cent.second,-1);
		if (x > y) swap(x, y);
		return (x << 30) + y;
	}
};
