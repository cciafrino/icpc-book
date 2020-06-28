/**
 * Author: Chris 
 * Description: n = vertices and s = starting point
 */

template<typename T> 
vector<T> Dijkstra(vector<vector<pair<int,T>>> &edges, int s) { 
    const int n = (int)edges.size();
	assert(0 <= s && s < n);
    vector<int> dist(n, numeric_limits<T>::max()/2), parent(n, -1);
    using Q = pair<T, int>;
    priority_queue<Q, vector<Q>, greater<Q>> q;
    q.push({dist[s] = 0, s});
    while(!q.empty()) {
        auto x = q.top(); q.pop();
        if (dist[x.second] < x.first) continue;
        for (auto u : edges[x.second])
            if (x.first + u.second < dist[u.first]) {
                q.push({dist[u.first] = x.first + u.second, u.first});
				parent[u.first] = x.second;
			}
    }
    return dist;
}
