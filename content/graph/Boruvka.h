/**
 * Author: Chris
 * Date: 2019-04-26
 * License: CC0
 * Source: 
 * Description: 
 * Status: Not tested
 */

struct Edge {
	int u, v, w, id;
	Edge() {};
	Edge(int u, int v, int w = 0, int id = 0) : u(u), v(v), w(w), id(id) {};
	bool operator<(Edge &o) const { return w < other.w; };
};

vector<Edge> Boruvka(vector<Edge> &edges, int n) {
	vector<Edge> mst, best(n);
	UF dsu(n);
	int f = 1;
	while (f) {
		f = 0;
		for (int i = 0; i < n; ++i) best[i] = Edge(i, i, INF);
		for (Edge e : edges) {
			int pu = dsu.find(e.u), pv = dsu.find(e.v);
			if (pu == pv) continue;
			if (e < best[pu]) best[pu] = e;
			if (e < best[pv]) best[pv] = e;
		}
		for (int i = 0; i < n; ++i) {
			Edge e = best[dsu.find(i)];
			if (e.w != INF) {
				dsu.unite(e.u, e.v);
				mst.push_back(e);
				f = 1;
			}
		}
	}
	return mst;
}