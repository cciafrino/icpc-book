/**
 * Author: chilli, Takanori MAEHARA
 * Description: Given N points, returns up to 8*N edges, which are guaranteed
 * to contain the Manhattan MST. The Manhattan MST of a set of points is the
 * MST where the weight of the edge between any pair of points is the Manhattan
 * distance between the points. Edges are in the form (distance, src, dst). Use
 * a standard MST algorithm on the result to find the final MST. Modify `edges`
 * and `sweep` to support doubles.
 * Status: Tested on kattis gridmst
 * Time: O(N log N)
 */
#include<UnionFind.h>

typedef Point<int> P;
pair<vector<array<int, 3>>, int> manhattanMST(vector<P> ps) {
    vector<int> id(ps.size());
    iota(id.begin(), id.end(), 0);
    vector<array<int, 3>> edges;
    for(int s = 0; s < 2; ++s) {
        for(int t = 0; t < 2; ++t) {
            sort(id.begin(), id.end(), [&](int i, int j) {
                 return (ps[i]-ps[j]).x < (ps[j]-ps[i]).y;});
            map<int, int> sweep;
            for (int i: id) {
                for (auto it = sweep.lower_bound(-ps[i].y);
                            it != sweep.end(); sweep.erase(it++)) {
                    int j = it->second;
                    auto d = ps[j] - ps[i];
                    if (d.y < d.x) break;
                    edges.push_back({abs(d.y) + abs(d.x), i, j});
                }
                sweep[-ps[i].y] = i;
            }
            for (auto &p: ps) p = P(p.y, p.x);
        }
        for (auto &p: ps) p = P(-p.x, p.y);
    }
    sort(edges.begin(), edges.end());
    UF uf(ps.size());
    int cost = 0;
    for (auto e: edges) if (uf.unite(e[1], e[2])) cost += e[0];
    return {edges, cost};
}
