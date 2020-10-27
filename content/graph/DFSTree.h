/**
 * Author: Chris and LeticiaFCS
 * Description: Find cut vertices and bridges.
 * Usage: Call solve right after build the graph
 */
struct tree_t {
	struct ed{ int pos, from, to; };
	int timer, n, m;
	vector<bool> art, bridges;
	vector<int> pre, low;
    	vector<vector<int>> g;
	vector<ed> edges;
	tree_t(int n): n(n), art(n), pre(n), low(n), g(n), timer(1), m(0){ }
	void addEdge(int u, int v) { 
		edges.push_back({m, u, v}); g[u].push_back(m++);
		edges.push_back({m, v, u}); g[v].push_back(m++);
	}
	array<int, 2> getEdge(int id){
		return { edges[id].from, edges[id].to };
	}
	int dfs(int u, int p){
		low[u] = pre[u] = timer++;
		int ch = 0;
		for(auto &pos:g[u]){
			int v = edges[pos].to;
			if(v == p) continue;
			if(pre[v]) low[u] = min(low[u], pre[v]);
			else{
				dfs(v, u); ch++;
				if(low[v] >= pre[u] && p != -1)
					art[u] = true;
				if(low[v] > pre[u]){
					bridges[pos] = bridges[pos^1] = true;
				}
				low[u] = min(low[u], low[v]);
			}
		}
		return ch;
	}
	void solve(){
		bridges.resize(m);
		for(int u=0; u<n; u++)
			if(!pre[u]) art[u] = dfs(u, -1) > 1;
	}		
};
 
