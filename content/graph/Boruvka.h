/**
 * Author: Chris
 * Date: 2019-04-26
 * License: CC0
 * Source: 
 * Description: 
 * Status: Not tested
 */

struct edge_t {
	int u, v, w, id;
	edge_t() {};
	edge_t(int u, int v, int w = 0, int id = 0) : u(u), v(v), w(w), id(id) {};
	bool operator<(edge_t &o) const { return w < other.w; };
};

vector<edge_t> Boruvka(vector<edge_t> &edges, int n) {
	vector<edge_t> mst, best(n);
	UF dsu(n);
	int f = 1;
	while (f) {
		f = 0;
		for (int i = 0; i < n; ++i) best[i] = edge_t(i, i, INF);
		for (edge_t e : edges) {
			int pu = dsu.find(e.u), pv = dsu.find(e.v);
			if (pu == pv) continue;
			if (e < best[pu]) best[pu] = e;
			if (e < best[pv]) best[pv] = e;
		}
		for (int i = 0; i < n; ++i) {
			edge_t e = best[dsu.find(i)];
			if (e.w != INF) {
				dsu.unite(e.u, e.v);
				mst.push_back(e);
				f = 1;
			}
		}
	}
	return mst;
}