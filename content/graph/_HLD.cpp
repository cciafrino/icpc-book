
typedef lint F;
typedef vector<vector<pair<int,F>>> adj;
F zero=0;
struct HLD{
	
	adj g;
	vector<int> in, par, parflow, sz, depth;
	vector<F> val;

	//declare query struct
				 

	int t, n;
	bool USE_EDGES;
	
	HLD(){}

	HLD(adj &g, bool u, int r = 0){init(g,u,r);}
	
	void init(adj &G, bool u, int r = 0){
		t=0, g=G, n=g.size(), USE_EDGES = u;
		par = parflow = vector<int>(n,-1);
		depth = in = sz = vector<int>(n,0);
		val.resize(n); val[0] = zero;
		par[r] = parflow[r] = r;
		dfs_sz(r);
		dfs_flow(r);
		strinit();
	}

	void strinit(){
		
	}
	F strquery(int a, int b){//inclusive query
		
	}
	void strupdate(int a, F value){
		
	}
	void strupdate(int a, int b, F value){//inclusive update
		
	}

	void dfs_sz(int u){ //par, size & depth
		sz[u]++;
		for(auto &e: g[u]){
			int v = e.st;
			if(par[v] == -1){
				par[v] = u; depth[v] = depth[u] + 1;
				dfs_sz(v);
				sz[u] += sz[v]; 
				if(par[u] == g[u][0].st || sz[v] > sz[g[u][0].st])
					swap(g[u][0],e);
			}
		}
	}

	void dfs_flow(int u){//parflow, in & val
		in[u] = t++;
		for(auto &e:g[u]){
			int v = e.st;
			if(parflow[v] == -1){
				if(e == g[u][0]) parflow[v] = parflow[u];
				else parflow[v] = v;
				dfs_flow(v);
				val[in[v]] = USE_EDGES?e.nd:zero;
			}
		}
	}
	
	F query(int u, int v){
		if(u == v) return strquery(in[u],in[u]);
		F ans = zero;	
		for(int e, p; parflow[u] != parflow[v]; u=p){
			if(depth[parflow[u]] < depth[parflow[v]]) swap(u,v);
			e = 1, p = parflow[u];
			if(u == p) e = 0, p = par[u];
			ans += strquery(in[parflow[u]]+e,in[u]);
		}
		if(in[u] > in[v]) swap(u,v);
		return ans += strquery(in[u]+USE_EDGES,in[v]);
	}
	void update(int u, int v, F value){
		if(u == v){strupdate(in[u],in[u],value);return;}
		for(int e, p; parflow[u] != parflow[v]; u=p){
			if(depth[parflow[u]] < depth[parflow[v]]) swap(u,v);
			e = 1, p = parflow[u];
			if(u == p) e = 0, p = par[u];
			strupdate(in[parflow[u]]+e,in[u],value);
		}
		if(in[u] > in[v]) swap(u,v);
		strupdate(in[u]+USE_EDGES,in[v],value);
	}
};

