/**
 * Author: André Sousa
 * Description:  Called lumberjack technique, solve functional graphs 
 * problems for digraphs, it's also pretty good for dp on trees.
 *  Consists in go cutting the leaves until there is no leaves,
 *  only cycles. For that we keep a processing queue of the leaves,
 *  note that during this processing time we go through all the childrens
 * of v before reaching a vertex v, therefore we can compute some
 * infos about the children, like subtree of a given vertex
 * Usage: Lumberjack<10010> g; g.init(par, indeg); (Be careful with the size of cyles when declared locally!)
 * Status: Tested on CodeForces 22E - Scheme
 */
template<int T> struct Lumberjack {
	int n, numcycle;
	vector<int> subtree, order, par, cycle;
	vector<int> parincycles, idxcycle, sz, st;
	vector<int> depth, indeg, cycles[T];
	vector<bool> seen, incycle, leaf;
	void init(vector<int>& _par, vector<int>& _indeg) {
		n = int(_par.size());
		par = _par;
		indeg = _indeg;
		order.resize(0);
		subtree.assign(n, 0);
		seen.assign(n, false);
		sz = st = subtree;
		parincycles = cycle = sz;
		idxcycle = depth = sz; 
		incycle = leaf = seen;
		bfs();
	}
	void find_cycle(int u){
		int idx= ++numcycle, cur = 0, p = u;
		st[idx] = u;
		sz[idx] = 0;
		cycles[idx].clear();
		while (!seen[u]) {
			seen[u] = incycle[u] = 1;
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
			if (!indeg[i]){
				seen[i] = leaf[i] = true;
				q.push(i);
			}
		while(!q.empty()){
			int v = q.front(); q.pop();
			order.push_back(v);
			++subtree[v];
			int curpar = par[v];
			indeg[curpar]--;
			subtree[curpar] += subtree[v];
			if(!indeg[curpar]){
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
