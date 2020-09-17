/**
 * Author: Chris
 * Description: Find the minimum spanning tree. Better for sparse graphs.
 * Time: $O(E \log E)$
 */
#include<UnionFind.h>
template<typename T> 
T kruskal(int n, vector<pair<T, pair<int,int>>> &edges) {
    sort(edges.begin(), edges.end());
    T cost = 0;
    UF dsu(n);
    for (auto& e : edges) 
        if (!dsu.same_set(e.second.first, e.second.second)) {
            dsu.unite(e.second.first, e.second.second);
            cost += e.first;
        }
    return cost;
}
