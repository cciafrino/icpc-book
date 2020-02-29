/**
 * Status: tested on codeForces 101807J and 101908L
 * Description: 
 * Time: 
 */
#include "SegTree.h"
typedef vector<vector<pair<int,int>>> adj;

template<typename T, bool USE_EDGES>
struct HLD {
	int t, n;
	vector<int> in, par, parflow, sz, depth;
	vector<T> val;
 	tree_t<T> seg; //or another query struct
	HLD(){}
	HLD(adj &g, int r = 0) : t(0), n(g.size()), par(n,-1), 
	parflow(n,-1), depth(n), in(n), sz(n), val(n) { 
		par[r] = parflow[r] = r;
		dfs_sz(g, r), dfs_flow(g, r); 
		seg.s = val; //init query struct
	}
	T query(int a, int b) {//inclusive query
		return seg.query(a, b+1);
	}
	void update(int a, T value) {
		seg.update(a, value);
	}
	void update(int a, int b, T value) {//inclusive update
		
	}
	void dfs_sz(adj &g, int u) { //par, size & depth
		sz[u]++;
		for(auto &e : g[u]) {
			int v = e.st;
			if(par[v] == -1) {
				par[v] = u; depth[v] = depth[u] + 1;
				dfs_sz(g, v);
				sz[u] += sz[v]; 
				if (par[u] == g[u][0].st || sz[v] > sz[g[u][0].st])
					swap(g[u][0], e);
			}
		}
	}
	void dfs_flow(adj &g, int u) {//parflow, in & val
		in[u] = t++;
		for (auto &e : g[u]) {
			int v = e.st;
			if (parflow[v] == -1) {
				if(e == g[u][0]) parflow[v] = parflow[u];
				else parflow[v] = v;
				dfs_flow(g, v);
				val[in[v]] = USE_EDGES ? e.nd : 0;
			}
		}
	}
	void update_path(int u, int v, T value){ //update path
		if (u == v){ update(in[u],in[u],value); return; }
		for(int e, p; parflow[u] != parflow[v]; u = p){
			if(depth[parflow[u]] < depth[parflow[v]]) swap(u,v);
			e = 1, p = parflow[u];
			if(u == p) e = 0, p = par[u];
			update(in[parflow[u]] + e, in[u], value);
		}
		if (in[u] > in[v]) swap(u, v);
		update(in[u] + USE_EDGES, in[v], value);
	}
	T query_path(int u, int v) {
		if (u == v) return query(in[u], in[u]);
		T ans = T();	
		for (int e, p; parflow[u] != parflow[v]; u = p){
			if(depth[parflow[u]] < depth[parflow[v]]) swap(u,v);
			e = 1, p = parflow[u];
			if(u == p) e = 0, p = par[u];
			ans += query(in[parflow[u]] + e, in[u]);
		}
		if (in[u] > in[v]) swap(u, v);
		return ans += query(in[u] + USE_EDGES, in[v]);
	}	
	void update_node(int u, int v, T value) {
		if (depth[u] < depth[v]) u = v;
		update(in[u],value);
	}
	int querySubtree(int v) { 
		return tree.query(in[v] + USE_EDGES, pos[v] + sz[v]);
	}
	void modifySubtree(int v, T value) {
		tree.update(in[v] + VALS_EDGES, in[v] + sz[v], value);
	}
};
