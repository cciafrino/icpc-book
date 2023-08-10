/**
 * Author: Yui Hosaka
 * Date: Unknown
 * Source: AtCoder
 * Description: Min-cost max-flow. Assumes there is no negative cycle.
 * Status: Working on kattis Minimum Cost Maximum Flow and Spoj Greedy
 * Time: O(F(V + E) log V), being F the amount of flow.
 */
template<class flow_t, class cost_t> struct min_cost {
	static constexpr flow_t FLOW_EPS = 1e-10L;
	static constexpr flow_t FLOW_INF = std::numeric_limits<flow_t>::max();
	static constexpr cost_t COST_EPS = 1e-10L;
	static constexpr cost_t COST_INF = std::numeric_limits<cost_t>::max();
	int n, m;
	vector<int> ptr, nxt, zu;
	vector<flow_t> capa;
	vector<cost_t> cost;
	explicit min_cost(int n_) : n(n_), m(0), ptr(n_, -1) {}
	void add_edge(int u, int v, flow_t w, cost_t c) { // d482f5
		nxt.push_back(ptr[u]); zu.push_back(v); capa.push_back(w); cost.push_back( c); ptr[u] = m++;
		nxt.push_back(ptr[v]); zu.push_back(u); capa.push_back(0); cost.push_back(-c); ptr[v] = m++;
	}
	vector<cost_t> pot, dist;
	vector<bool> vis;
	vector<int> pari;
	// cost slopes[j] per flow when flows[j] <= flow <= flows[j + 1]
	vector<flow_t> flows; vector<cost_t> slopes;
	//   The distance to a vertex might not be determined if it is >= dist[t].
	//   You can pass t = -1 to find a shortest path to each vertex.
	void shortest(int s, int t) { // e9bb0d
		using Entry = pair<cost_t, int>;
		priority_queue<Entry, vector<Entry>, std::greater<Entry>> que;
		for (int u = 0; u < n; ++u) { dist[u] = COST_INF; vis[u] = false; }
		for (que.emplace(dist[s] = 0, s); !que.empty(); ) {
			const cost_t c = que.top().first;
			const int u = que.top().second;
			que.pop();
			if (vis[u]) continue;
			vis[u] = true;
			if (u == t) return;
			for (int i = ptr[u]; ~i; i = nxt[i]) if (capa[i] > FLOW_EPS) {
				const int v = zu[i];
				const cost_t cc = c + cost[i] + pot[u] - pot[v];
				if (dist[v] > cc) { que.emplace(dist[v] = cc, v); pari[v] = i; }
			}
		}
	}
	pair<flow_t, cost_t> run(int s, int t, flow_t limFlow = FLOW_INF) {
		assert(0 <= limFlow);
		pot.assign(n, 0);
		while (true) {
			bool upd = false;
			for (int i = 0; i < m; ++i) if (capa[i] > FLOW_EPS) {
				const int u = zu[i ^ 1], v = zu[i];
				const cost_t cc = pot[u] + cost[i];
				if (pot[v] > cc + COST_EPS) { pot[v] = cc; upd = true; }
			}
			if (!upd) break;
		}
		dist.resize(n); vis.resize(n); pari.resize(n);
		flows.clear(); flows.push_back(0);
		slopes.clear();
		flow_t flow = 0; cost_t cost = 0;
		while (flow < limFlow) {
			shortest(s, t);
			if (!vis[t]) break;
			for (int u = 0; u < n; ++u) pot[u] += min(dist[u], dist[t]);
			flow_t f = limFlow - flow;
			for (int v = t; v != s; ) {
				const int i = pari[v]; if (f > capa[i]) { f = capa[i]; } v = zu[i ^ 1];
			}
			for (int v = t; v != s; ) {
				const int i = pari[v]; capa[i] -= f; capa[i ^ 1] += f; v = zu[i ^ 1];
			}
			flow += f;
			cost += f * (pot[t] - pot[s]);
			flows.push_back(flow); slopes.push_back(pot[t] - pot[s]);
		}
		return {flow, cost};
	}
};
