/**
 * Status: tested on codeForces 101807J and 101908L
 * Description: 
 * Time: 
 */
#include "SegTree.h"
typedef vector<vector<pair<int,int>>> adj; //vertex, value

template<typename T, bool USE_EDGES>
struct HLD {
	int t, n;
	T ini_val;
	vector<int> in, par, pf, sz, dep;
	vector<T> val;
 	tree_t<T> seg; //or another query struct
	HLD(){}
	HLD(adj &g, int r = 0) : t(0), n(g.size()), par(n,-1), 
	pf(n,-1), dep(n), in(n), sz(n),  ini_val(T()), val(n,ini_val){ 
		par[r] = pf[r] = r;
		dfs_sz(g, r), dfs_flow(g, r); 
		seg = {val}; //init query struct
	}
	void f(T &a, T b){ a += b; } 
	T query(int a, int b) {//inclusive query
		return seg.query(a, b+1);
	}
	void update(int a, T value) {
		seg.update(a, value);
	}
	void update(int a, int b, T value) {//inclusive update
		
	}
	void dfs_sz(adj &g, int u) { //par, size & dep
		sz[u]++;
		for(auto &e : g[u]) {
			int v = e.st;
			if(par[v] == -1) {
				par[v] = u; dep[v] = dep[u] + 1;
				dfs_sz(g, v);
				sz[u] += sz[v]; 
				if (par[u] == g[u][0].st || sz[v] > sz[g[u][0].st])
					swap(g[u][0], e);
			}
		}
	}
	void dfs_flow(adj &g, int u) {//pf, in & val
		in[u] = t++;
		for (auto &e : g[u]) {
			int v = e.st;
			if (pf[v] == -1) {
				if(e == g[u][0]) pf[v] = pf[u];
				else pf[v] = v;
				dfs_flow(g, v);
				val[in[v]] = USE_EDGES ? e.nd : ini_val;
			}
		}
	}
	void path(int u, int v, function<void(int,int)> func){
		if (u == v){ return func(in[u],in[u]);}
		for(int e, p; pf[u] != pf[v]; u = p){
			if(dep[pf[u]] < dep[pf[v]]) swap(u,v);
			e = 1, p = pf[u];
			if(u == p) e = 0, p = par[u];
			func(in[pf[u]] + e, in[u]);
		}
		if (in[u] > in[v]) swap(u, v);
		func(in[u] + USE_EDGES, in[v]);
	}
	void update_path(int u, int v, T value){
		path(u,v, [value,this](int a,int b){ update(a,b,value); });
	}
	T query_path(int u, int v) {
		T ans = ini_val;
		path(u,v,[&ans,this](int a,int b){ f(ans, query(a,b)); });
		return ans;
	}
	void update_edge(int u, int v, T value) {
		if (dep[u] < dep[v]) u = v;
		update(in[u],value);
	}
	T query_subtree(int v) { 
		return query(in[v] + USE_EDGES, in[v] + sz[v]);
	}
	void update_subtree(int v, T value) {
		update(in[v] + USE_EDGES, in[v] + sz[v], value);
	}
};
