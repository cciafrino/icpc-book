/**
 * Author: LeticiaFCS
 * Description: finds the directions of the edges of given functional graph, 
 *		returns pair of $parent$ and $indegree$ of each vertex.
 *		Useful together with functional-digraph.h.
 * Status: NOT tested
 */
pair<vector<int>, vector<int>> make_functional_digraph(const vector<vector<int>> &g, vector<int> deg){
	int n = int(g.size());
	vector<int> par(n), indeg(n);
	vector<bool> vis(n);
	queue<int> q;
 	for(int u=0; u<n; u++)
		if(deg[u] == 1)
			q.push(u);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		vis[u] = true;
		for(int v: g[u]){
			if(vis[v]) continue;
			par[u] = v;
			indeg[v]++;
			deg[v]--;
			if(deg[v] == 1)
				q.push(v);
		}
	}
	for(int u=0; u<n; u++){
		if(vis[u]) continue;
		int cur = u, nxt = -1;
		while(nxt != u){
			vis[cur] = true;
			nxt = -1;
			for(int x: g[u])
				if(!vis[x]){
					nxt = x;
					break;
				}	
			if(nxt == -1)
				nxt = u;
			indeg[nxt]++;
			par[cur] = nxt;
			cur = nxt;
		}
	}
	return {par, indeg};	
}
