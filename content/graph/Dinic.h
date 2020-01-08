/**
 * Author: chilli (adapted)
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * To obtain the actual flow, look at positive values only.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING
 * 		   Working on hackerearth Min-Cut and Kattis Minimum Cut
 */
template<typename T = lint>
struct Dinic {
	struct Edge {
		int to, rev; T c, f;
	};
	vector<int> lvl, ptr, q;
	vector<int> partition; //call findMinCut before use it
	vector<pair<pair<int,int>,int>> cut; //u,v,c
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n),partition(n),cut(0) {}
	void addEdge(int a, int b, T c, int rcap = 0) {
		adj[a].push_back({b, adj[b].size(), c, 0});
		adj[b].push_back({a, adj[a].size() - 1, rcap, 0});
	}
	T dfs(int v, int t, T f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < adj[v].size(); i++) {
			Edge& e = adj[v][i];
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
		for(int L = 0; L < 31; ++L) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vector<int>(q.size());
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for(Edge &e : adj[v])
					if (!lvl[e.to] && (e.c - e.f) >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (T p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	//only if you want the edges of the cut
	void dfsMC(int u){
		partition[u] = 1;
		for (Edge &e : adj[u])
			if (!partition[e.to])
				if (e.c - e.f == 0)
					cut.push_back({{u,e.to},e.c});
				else if (e.c - e.f > 0) dfsMC(e.to);
	}
	//only if you want the edges of the cut
	vector<pair<pair<int,int>,int>> findMinCut(int u,int t){
		maxflow(u,t); //DONT call again if you already called it
		dfsMC(u);
		return cut;
	}
};
