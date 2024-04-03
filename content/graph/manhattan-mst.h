/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-11-02
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/rectilinear_mst.cc
 * Description: Given N points, returns up to 4*N edges, which are guaranteed
 * to contain a minimum spanning tree for the graph with edge weights $w(p, q) =
 * |p.x - q.x| + |p.y - q.y|$. Edges are in the form (distance, src, dst). Use a
 * standard MST algorithm on the result to find the final MST.
 * Time: O(N log N)
 * Status: Fuzz-tested and tested on Kattis - Grid MST
 */
#include<dsu.h>
typedef Point<int> P;
pair<vector<array<int, 3>>, int> manhattanMST(vector<P> ps) {
	vector<int> id(ps.size()); iota(id.begin(), id.end(), 0);
	vector<array<int, 3>> edges; ///start-hash
	for(int k = 0; k < 4; ++k) {
		sort(id.begin(), id.end(), [&](int i, int j) {
			return (ps[i]-ps[j]).x < (ps[j]-ps[i]).y;});
		map<int, int> sweep;
		for(auto& i : id) {
			for (auto it = sweep.lower_bound(-ps[i].y);
				it != sweep.end(); sweep.erase(it++)) {
				int j = it->second; P d = ps[i] - ps[j];
				if (d.y > d.x) break;
				edges.push_back({d.y + d.x, i, j});
			} sweep[-ps[i].y] = i;
		}
		if (k & 1) for(auto& p : ps) p.x = -p.x;
		else for(auto& p : ps) swap(p.x, p.y);
	} ///end-hash
	sort(edges.begin(), edges.end());
	UF uf(ps.size()); int cost = 0;
	for (auto e: edges) if (uf.unite(e[1], e[2])) cost += e[0];
	return {edges, cost};
}
