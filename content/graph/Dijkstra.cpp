/**
 * Author: LeticiaFCS
 * Description: Calculates the shortest path between start node and every other node in the graph
 */
void dijkstra(vector<vector<pii>> &graph, vector<int> &dist, int start){
	vector<bool> vis(n, 0);
	for(int i = 0; i < n; i++) dist[i] = INF;
	priority_queue <pii, vector<pii>, greater<pii>> q;
	q.push({dist[start] = 0,start});
	while(!q.empty()) {
		int u=q.top().nd;
		q.pop();
		vis[u]=1;
		for(pii p: graph[u]){
			int e=p.st, v=p.nd;
			if (vis[v]) continue;
			int new_dist=dist[u]+e;
			if(new_dist<dist[v]){
				q.push({dist[v] = new_dist,v});
			}
		}
	}
}
