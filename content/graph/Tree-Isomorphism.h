/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: UFMG
 * Description: 
 * Time: O(N\logN)
 * Status: not tested
 */

map<vector<int>, int> delta;

struct tree_t {
	int n;
	pair<int,int> centroid;
	vector<vector<int>> edges;
	vector<int> sz;
	tree_t(vector<vector<int>>& graph) : 
		edges(graph), sz(edges.size()) {}
	int dfs_sz(int v, int p) {
		sz[v] = 1;
		for (int u : edges[v]) {
			if (u == p) continue;
			sz[v] += dfs_sz(u, v);
		}
		return sz[v];
	}
	int dfs(int tsz, int v, int p) {
		for (int u : edges[v]) {
			if (u == p) continue;
			if (2*sz[u] <= tsz) continue;
			return dfs(tsz, u, v);
		}
		return centroid.first = v;
	}
	pair<int,int> find_centroid(int v) {
		int tsz = dfs_sz(v, -1);
		centroid.second = dfs(tsz, v, -1);
		for (int u : edges[centroid.first]) {
			if (2*sz[u] == tsz) 
				centroid.second = u;
		}
		return centroid;
	}
	int hash_it(int v, int p) {
		vector<int> offset;
		for (int u : edges[v]) {
			if (u == p) continue;
			offset.push_back(hash_it(u, v));
		}
		sort(offset.begin(), offset.end());
		if (!delta.count(offset)) 
			delta[offset] = int(delta.size());
		return delta[offset];
	}
	lint get_hash(int v = 0) {
		pair<int,int> cent = find_centroid(v);
		lint x = hash_it(cent.first, -1), y = hash_it(cent.second, -1);
		if (x > y) swap(x, y);
		return (x << 30) + y;
	}
};