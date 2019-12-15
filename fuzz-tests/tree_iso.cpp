#include<bits/stdc++.h>
using namespace std;

using lint = long long;

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
		dfs(tsz, v, -1);
		centroid.second = centroid.first;
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
	lint get_hash(int v) {
		pair<int,int> cent = find_centroid(v);
		lint x = hash_it(cent.first, -1), y = hash_it(cent.second, -1);
		if (x > y) swap(x, y);
		return (x << 30) + y;
	}
};

map<vector<int>, int> mapp;

struct tree {
	int n;
	vector<vector<int> > g;
	vector<int> subsize;
	using ll = lint;
	tree(vector<vector<int>>& graph) : 
		g(graph), subsize(g.size()) {}
	void dfs(int k, int p=-1) {
		subsize[k] = 1;
		for (int i : g[k]) if (i != p) {
			dfs(i, k);
			subsize[k] += subsize[i];
		}
	}
	int centroid(int k, int p=-1, int size=-1) {
		if (size == -1) size = subsize[k];
		for (int i : g[k]) if (i != p)
			if (subsize[i] > size/2) 
				return centroid(i, k, size);
		return k;
	}
	pair<int, int> centroids(int k=0) {
		dfs(k);
		int i = centroid(k), i2 = i;
		for (int j : g[i]) if (2*subsize[j] == subsize[k]) i2 = j;
		return {i, i2};
	}
	int hashh(int k, int p=-1) {
		vector<int> v;
		for (int i : g[k]) if (i != p) v.push_back(hashh(i, k));
		sort(v.begin(), v.end());
		if (!mapp.count(v)) mapp[v] = int(mapp.size());
		return mapp[v];
	}
	ll getHash(int k=0) {
		pair<int, int> c = centroids(k);
		//cout << c.first << ' '<< c.second << '\n';
		ll a = hashh(c.first), b = hashh(c.second);
		if (a > b) swap(a, b);
		return (a<<30)+b;
	}
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    for (int _ = 0; _ < T; ++_) {
	    int n;
		cin >> n;
		vector<vector<int>> g1(n), g2(n);
		for (int i = 0; i < n-1; ++i) {
			int a, b;
			cin >> a >> b;
			a--,b--;
			g1[a].push_back(b);
			g1[b].push_back(a);
		}
		for (int i = 0; i < n-1; ++i) {
			int a, b;
			cin >> a >> b;
			a--,b--;
			g2[a].push_back(b);
			g2[b].push_back(a);
		}
		//cout << "\n\n\n";
		tree_t t1(g1), t2(g2);
		//tree t3(g1), t4(g2);
		if (t1.get_hash(0) == t2.get_hash(0)) cout << "YES\n";
		else cout << "NO\n";
	}
}