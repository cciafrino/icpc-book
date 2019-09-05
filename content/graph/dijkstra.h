/**
 * Author: Chris 
 * Description: n = vertices and v = starting point
 */
template<class K> using pq = priority_queue<K, vector<K>, greater<K>>;
template<typename T> vector<T> Dijkstra(vector<vector<pair<int,T>>> &edges, int n, int v) { 
	assert(0 <= v && v < n);
    vector<int> dist(n, INT_MAX/2), parent(n, -1);
    pq<pair<int,int>> q;
    q = pq<pair<int,int>>(); 
    q.push({dist[v] = 0, v});
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
