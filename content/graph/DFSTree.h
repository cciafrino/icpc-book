/**
 * Author: Chris and LeticiaFCS
 * Description: Find cut vertices and bridges.
 * Usage: Call solve right after build the graph
  * Status: Tested on UVA 315
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
		//assert(u < (int) g.size());
		//assert(v < (int) g.size()); 
		edges.push_back({m, u, v}); g[u].push_back(m++);
		edges.push_back({m, v, u}); g[v].push_back(m++);
	}
	array<int, 2> getEdge(int id){
		return { edges[id].from, edges[id].to };
	}
	int dfs(int u, int p/*, int r = 0*/){
		//cout<<"max old deep: "<<old_prof<<" cur deep: "<<r<<"\n";
		//assert(r < 52000);
		low[u] = pre[u] = timer++;
		int v, ch = 0;
		for(auto &pos:g[u]){
			//assert(pos >= 0);
			//assert(pos < (int) edges.size());
			int v = edges[pos].to;
			if(p == v) continue;
			if(pre[v]) low[u] = min(low[u], pre[v]);
			else{
				dfs(v, u/*, r+1*/); ch++;
				/*assert(u < (int) low.size());
				assert(v < (int) low.size());
				assert(u < (int) pre.size());
				assert(v < (int) pre.size()); 
				assert(pos < (int) bridges.size()); 
				assert((pos^1) < (int) bridges.size());
				assert(u >= 0);
				assert(v >= 0);
				assert(u >= 0);
				assert(v >= 0); 
				assert(pos >= 0); 
				assert((pos^1) >= 0);*/				
				if(low[v] >= pre[u] && p != -1)
					art[u] = true;
				if(low[v] > pre[u])
					bridges[pos] = bridges[pos^1] = true;
				low[u] = min(low[u], low[v]);
			}
		}		
		return ch;
	}
	void solve(){
		assert(m == (int) edges.size());
		bridges.resize(m);
		for(int u=0; u<n; u++)
			if(!pre[u]){ art[u] = dfs(u, -1) > 1; }
	}		
};
 
