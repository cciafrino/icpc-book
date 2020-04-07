/**
 * Author: Chris
 * Description: Find the minimum spanning tree. Better for sparse graphs.
 * Time: $O(E \log E)$
 */
template<typename T> 
T kruskal(int n, vector<pair<T, pair<int,int>>> &edges) {
    sort(edges.begin(), edges.end());
    T cost = 0;
    UF dsu(n);
    for (auto &e : edges) 
        if (dsu.find(e.second.first) != dsu.find(e.second.second)) {
            dsu.unite(e.second.first, e.second.second);
            cost += e.first;
        }
    return cost;
}
