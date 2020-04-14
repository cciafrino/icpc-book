/**
 * Author: André Sousa
 * Description:  Called lumberjack technique, solve functional graphs 
 * problems for graphs, it's also pretty good for dp on trees.
 *  Consists in go cutting the leaves until there is no leaves,
 *  only cycles. For that we keep a processing queue of the leaves,
 *  note that during this processing time we go through all the childrens
 * of v before reaching a vertex v, therefore we can compute some
 * infos about the children, like subtree of a given vertex
 *
 * Status: NOT tested
 */
template<int T> struct Lumberjack {
	int n, numcycle;
	vector<int> subtree, order, par, cycle;
	vector<int> parincycles, idxcycle, sz, st;
	vector<int> depth, deg, cycles[T];
	vector<bool> seen, incycle, leaf;
	vector<vector<int>> graph;
	void init(vector<vector<int>>& _graph, vector<int>& _deg){ 
		init(_graph.size());
		graph = _graph; deg = _deg; 
	}
	void init(int N) {
		n = N;
		order.resize(0);
		subtree.assign(n, 0);
		seen.assign(n, false);
		sz = st = subtree;
		parincycles = par = cycle = sz;
		idxcycle = depth = deg = sz; 
		incycle = leaf = seen;
		vector<int> adj; graph.assign(n, adj);
	}
	int find_par(int u) {
	    for (int v : graph[u]) if (!seen[v]) 
	    	return v;
	    return -1;
	}
	void find_cycle(int u){
		int idx= ++numcycle, cur = 0, p = u;
		st[idx] = u;
		sz[idx] = 0;
		cycles[idx].clear();
		while (!seen[u]) {
			seen[u] = incycle[u] = true;
			par[u] = find_par(u);
			if(par[u] == -1) par[u] = p;
			parincycles[u] = u;
			cycle[u] = idx;
			idxcycle[u] = cur;
			cycles[idx].push_back(u);
			++sz[idx];
			depth[u] = 0;
			++subtree[u];
			u = par[u];
			++cur;
		}
	}
	void bfs() {
		queue<int> q;
		for (int i = 0; i < n; ++i)
			if (deg[i] == 1){
				seen[i] = leaf[i] = true;
				q.push(i);
			}
		while(!q.empty()){
			int v = q.front(); q.pop();
			order.push_back(v);
			++subtree[v];
			int curpar = find_par(v);
			deg[curpar]--;
			subtree[curpar] += subtree[v];
			if(deg[curpar] == 1){
				q.push(curpar);
				seen[curpar] = true;
			}
		}
		numcycle = 0;
		for (int i = 0; i < n; ++i)
			if (!seen[i]) find_cycle(i);
		for(int i = order.size()-1; i >= 0; --i){
			int v = order[i], curpar = par[v];
			parincycles[v] = parincycles[curpar];
			cycle[v] = cycle[curpar];
			incycle[v] = false;
			idxcycle[v] = -1;
			depth[v] = 1 + depth[curpar];
		}
	}
};

