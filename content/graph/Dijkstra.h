/**
 * Author: Chris 
 * Description: Faster implementation of Dijkstra's algorithm. Makes very easy to handle SSSP on state graphs.
 * Date: 2020
 * License: CC0
 * Source: Yosupo
 * Time: $O(N\log N)$
 * Status: Tested on URI 1931
 */
#include<bits/extc++.h> // keep-include!!

template <class D> struct MinDist {
    vector<D> dist; vector<int> from;
};
template <class D, class E> // Weight type and Edge info
MinDist<D> Dijkstra(const vector<vector<E>>& g, int s, D inf = numeric_limits<D>::max()) {
    int N = int(g.size());
    vector<D> dist = vector<D>(N, inf);
    vector<int> par = vector<int>(N);
    struct state_t {
        D key;
        int to;
        bool operator<(state_t r) const { return key > r.key; }
    };
    __gnu_pbds::priority_queue<state_t> q;
    q.push(state_t{0, s});
    dist[s] = D(0);
    while (!q.empty()) {
        state_t p = q.top(); q.pop();
        if (dist[p.to] < p.key) continue;
        for (E nxt : g[p.to]) {
            if (p.key + nxt.second < dist[nxt.first]) {
                dist[nxt.first] = p.key + nxt.second;
                par[nxt.first] = p.to;
                q.push(state_t{dist[nxt.first], nxt.first});
            }
        }
    }
    return MinDist<D>{dist, par};
}
