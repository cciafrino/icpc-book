/**
 * Author: chilli, LeticiaFCS
 * Date: 2020-03-18
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * To obtain each partition $A$ and $B$ of the cut look at $lvl$, for $v \subset A$, $lvl[v] > 0$,
 * for $u \subset B$, $lvl[u] = 0$.
 * Status: Tested, stress-tested
 */
template<typename T = int> struct Dinitz {
	struct edge_t { int to, rev; T c, f; };
	vector<vector<edge_t>> adj;
	vector<int> lvl, ptr, q;
	Dinitz(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	inline void addEdge(int a, int b, T c, T rcap = 0) {
		adj[a].push_back({b, (int)adj[b].size(), c, 0});
		adj[b].push_back({a, (int)adj[a].size() - 1, rcap, 0});
	}
	T dfs(int v, int t, T f) {
		if (v == t || !f) return f;
		for (int &i = ptr[v]; i < int(adj[v].size()); ++i) {
			edge_t &e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (T p = dfs(e.to, t, min(f, e.c - e.f))) {
					e.f += p, adj[e.to][e.rev].f -= p;
					return p;
				}
		}
		return 0;
	}
	T maxflow(int s, int t) { 
		T flow = 0; q[0] = s;
		for (int L = 0; L < 31; ++L) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vector<int>(q.size());
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (edge_t &e : adj[v])
					if (!lvl[e.to] && (e.c - e.f) >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (T p = dfs(s, t, numeric_limits<T>::max()/4)) flow += p;
		} while (lvl[t]);
		return flow;
	} 
	bool leftOfMinCut(int v) { return lvl[v] != 0; }
	pair<T, vector<pair<int,int>>> minCut(int s, int t) {
		T cost = maxflow(s,t); 
		vector<pair<int,int>> cut;		
		for (int i = 0; i < int(adj.size()); i++) for(edge_t &e : adj[i])
			if (lvl[i] && !lvl[e.to]) cut.push_back({i, e.to});
		return {cost, cut};
	} 
};
