/**
 * Author: André Sousa
 * Description:  Called lumberjack technique, solve functional graphs 
 * problems for digraphs, it's also pretty good for dp on trees.
 *  Consists in go cutting the leaves until there is no leaves,
 *  only cycles. For that we keep a processing queue of the leaves,
 *  note that during this processing time we go through all the childrens
 * of v before reaching a vertex v, therefore we can compute some
 * infos about the children, like subtree of a given vertex
 * Status: Tested on CodeForces 22E - Scheme
 */
  

struct LumberJack{
	int n, numcycle;

	vector<int> subtree, order, par, cycle, parincycles, idxcycle, sz, st, depth, indeg, cycles[MAXN];
	
	vector<bool> seen, incycle, leaf;
	
	LumberJack(int N):n(N){
		init(n);
	}
	
	LumberJack(vector<int> deg):n(deg.size()){
		init(n);
		par = deg;
	}

	void init(int n){
		subtree.assign(n,0);
		order.assign(n,0);
		par.assign(n,0);
		cycle.assign(n,0);
		parincycles.assign(n,0);
		idxcycle.assign(n,0);
		sz.assign(n,0);
		st.assign(n,0);
		depth.assign(n,0);
		indeg.assign(n,0);
		seen.assign(n,0);
		incycle.assign(n,0);
		leaf.assign(n,0);
	}

	void find_cycle(int u){
		int idx= ++numcycle, cur=0, p = u;
		st[idx] = u;
		sz[idx]=0;
		cycles[idx].clear();
		while(!seen[u]){
			seen[u]=incycle[u]=1;
			parincycles[u]=u;
			cycle[u]=idx;
			idxcycle[u]=cur;
			cycles[idx].push_back(u);
			++sz[idx];
			depth[u]=0;
			++subtree[u];
			u=par[u];
			++cur;
		}
	}


	void bfs(){
		queue<int> q;
		for(int i=0;i<n;i++)
			if(!indeg[i]){
				leaf[i]=1;
				q.push(i);
				seen[i]=1;
			}
		while(!q.empty()){
			int v = q.front(); q.pop();
			order.push_back(v);
			++subtree[v];
			int curpar=par[v];
			indeg[curpar]--;
			subtree[curpar] += subtree[v];
			if(!indeg[curpar]){
				q.push(curpar);
				seen[curpar]=1;
			}
		}
		numcycle=0;
		for(int i=0;i<n;++i)
			if(!seen[i]) find_cycle(i);
		for(int i=order.size()-1; i>=0;i--){
			int v = order[i], curpar=par[v];
			parincycles[v] = parincycles[curpar];
			cycle[v] = cycle[curpar];
			incycle[v] = 0;
			idxcycle[v]=-1;
			depth[v] = 1+depth[curpar];
		}
	}
};

