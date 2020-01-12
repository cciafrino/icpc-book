/**
 * Author: André Sousa
 * Description:  Called lumberjack technique, solve functional graphs 
 * problems for digraphs, it's also pretty good for dp on trees.
 *  Consists in go cutting the leaves until there is no leaves,
 *  only cycles. For that we keep a processing queue of the leaves,
 *  note that during this processing time we go through all the childrens
 * of v before reaching a vertex v, therefore we can compute some
 * infos about the children, like subtree of a given vertex
 */
  

vector<int> deg, subtree, order, par, parincycles, idxcycle, sz, st, depth, cycles[MAXN];
vector<bool> seen, incycle,
int numcycle;

void bfs() {
    queue<int> q;
    for (int i = 0; i < n; ++i)
	    if (!indeg[i]) {
		    q.push(i);
		    seen[i] = 1;
	    }
    while(!q.empty()) {
	    int v = q.front(); q.pop();
	    order.push_back(v);
	    ++subtree[v];
	    int curpar = par[v];
	    indeg[curpar]--;
	    subtree[curpar] += subtree[v];
	    if (!indeg[curpar]) {
		    q.push(curpar);
		    seen[curpar] = 1;
	    }
    }
    numcycles = 0;
    for (int i = 0; i < n; ++i) 
	    if (!seen[i]) find_cycle(i);
    for (int i = order.size()-1; i >= 0; --i) {
	    int v = order[i], curpar = par[v];
	    parincycle[v] = parincycle[curpar];
	    cycle[v] = cycle[curpar];
	    incycle[v] = 0;
	    idxcycle[v] = -1;
	    depth[v] = 1 + depth[curpar];
    }
}
void find_cycle(int u) {
    int idx = ++numcycle, cur = 0, par = u;
    st[idx] = u;
    size[idx] = 0;
    cycles[idx].clear();
    while(!seen[u]) {
	    seen[u] = incycle[u] = 1;
	    parincycle[u] = u;
	    cycle[u] = idx;
	    idxcycle[u] = cur;
	    cycles[idx].push_back(u);
	    ++size[idx];
	    depth[u] = 0;
	    ++subtree[u];
	    u = par[u];
	    ++cur;
    }
}
