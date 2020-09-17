/**
 * Author: Chris 
 * Description: Faster implementation of Dijkstra's algorithm. par vector can be used to recover the path.
 */
#include<bits/extc++.h> // keep-include!!

vector<int> dist(N, INT_MAX/2), par(N, -1);
__gnu_pbds::priority_queue<pair<int, int>> q;
q.push({dist[S] = 0, S});
while (!q.empty()) {
    auto [u, v] = q.top(); q.pop();
    if (dist[v] < u) continue;
    for (auto& nxt : edges[v]) {
        int cost = dist[v] + nxt.second;
        if (cost < dist[nxt.first]) {
            dist[nxt.first] = cost;
            q.push({-dist[nxt.first], nxt.first});
            par[nxt.first] = v;
        }
    }
}
