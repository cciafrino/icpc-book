/**
 * Author: Koosaga
 * Description: Maximum Matching for general graphs (undirected and non bipartite) using Edmond's Blossom.
 * Time: $O(EV^2)$ 
 */

template<int N> struct generalMatching { /// start-hash
    int vis[N], par[N], orig[N], match[N], aux[N], t, N; // 1-based index
    vector<int> edges[N];
    queue<int> Q;
    void addEdge(int u, int v) {
    	edges[u].pb(v); edges[v].pb(u);
    } 
    void init(int n) {
    	N = n; t = 0;
    	for(int i = 0; i <= N; ++i) {
    		edges[i].clear();
    		match[i] = aux[i] = par[i] = 0;
    	}
    } /// end-hash
    void augment(int u, int v) { /// start-hash
    	int pv = v, nv;
    	do {
    		pv = par[v]; nv = match[pv];
    		match[v] = pv; match[pv] = v;
    		v = nv;
    	} while(u != pv);
    }/// end-hash
    int lca(int v, int w) {/// start-hash
    	++t;
    	while (1) {
    		if (v) {
    			if (aux[v] == t) return v; aux[v] = t;
    			v = orig[par[match[v]]];
    		}
    		swap(v, w);
    	}
    }/// end-hash
    void blossom(int v, int w, int a) {/// start-hash
    	while (orig[v] != a) {
    		par[v] = w; w = match[v];
    		if(vis[w] == 1) Q.push(w), vis[w] = 0;
    		orig[v] = orig[w] = a;
    		v = par[w];
    	}
    }/// end-hash
    bool bfs(int u) {/// start-hash
    	fill(vis+1, vis+1+N, -1); iota(orig + 1, orig + N + 1, 1);
    	Q = queue<int> (); Q.push(u); vis[u] = 0;
    	while (N(Q)) {
    		int v = Q.front(); Q.pop();
    		for(auto &x : edges[v]) {
    			if (vis[x] == -1) {
    				par[x] = v; vis[x] = 1;
    				if (!match[x]) return augment(u, x), true;
    				Q.push(match[x]); vis[match[x]] = 0;
    			} else if (vis[x] == 0 && orig[v] != orig[x]) {
    				int a = lca(orig[v], orig[x]);
    				blossom(x, v, a); blossom(v, x, a);
    			}
    		}
    	}
    	return false;
    }/// end-hash
    int Match() {/// start-hash
    	int ans = 0;
    	// find random matching (not necessary, constant improvement)
    	vector<int> V(N-1); iota(V.begin(), V.end(), 1);
    	shuffle(all(V), mt19937(0x94949));
    	for(auto &x : V) if(!match[x]) 
    		for(auto &y : edges[x]) if (!match[y]) {
    			match[x] = y, match[y] = x;
    			++ans; break;
    		}
    	for(int i = 1; i <= N; ++i) 
    	    if (!match[i] && bfs(i)) 
    	        ++ans;
    	return ans;
    }/// end-hash
};
