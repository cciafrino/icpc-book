/**
 * Author: Chris 
 * Description: Find Kth shortest path from s to t.
 * Time: O((V + E) lg(V) * k)
 * Source: https://github.com/dragonslayerx
 */

int getCost(vector<vector<pair<int,int>>> &G, int s, int t, int k) {
    int n = G.size();
    vector<int> dist(n, INF), count(n, 0);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
	Q.push({0, s});
	while (!Q.empty() && (count[t] < k)) {
		pair<int,int> v = Q.top();
		int u = v.second, w = v.first;
		Q.pop();
		if ((dist[u] == INF) || (w > dist[u])) { // remove equal paths
			count[u] += 1;
			dist[u] = w;
		}
		if (count[u] <= k) 
		    for (int x : G[u]) {
				int v = x.first, w = x.second;
				Q.push({dist[u] + w, v});
		    }
	}
    return dist[t];
}