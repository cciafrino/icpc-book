/**
 * Author: Chris
 * Description: Find the minimum spanning tree. Better for dense graphs.
 * Time: $O(E \log V)$
 */
priority_queue<pair<int, int>> pq;
void process(int v) { 
    seen[v] = true;
    for (auto u : edges[v]) 
        if (!seen[v.first]) 
            pq.push({-v.second, -v.first});
}
int mst() {
    int mst_cost = 0; process(0);
    while (!pq.empty()) {
        auto v = pq.top(); pq.pop();
        int u = -v.second, w = -v.first;
        if (!seen[u]) mst_cost += w;
        process(u);
    }
    return mst_cost;
}

