#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// #include "mcmf3.h"
// #include "mcmf4.h"
// #include "mcmfold.h"
// #include "mcmfnew.h"
#define setpi dummy(){} bool setpi
#undef assert
#define assert(x) return x
//#include "../content/graph/MinCostMaxFlow.h"
#undef assert
#undef setpi
#include <cassert>
#include "MinCostMaxFlow2.h"

template <typename flow_t = int, typename cost_t = long long>
struct MCMF_SSPA {
	int N;
	vector<vector<int>> adj;
	struct edge_t {
		int dest;
		flow_t cap;
		cost_t cost;
	};
	vector<edge_t> edges;
 
	vector<char> seen;
	vector<cost_t> pi;
	vector<int> prv;
 
	void addEdge(int from, int to, flow_t cap, cost_t cost) {
		assert(cap >= 0);
		int e = int(edges.size());
		edges.emplace_back(edge_t{to, cap, cost});
		edges.emplace_back(edge_t{from, 0, -cost});
		adj[from].push_back(e);
		adj[to].push_back(e+1);
	}
 
	const cost_t INF_COST = numeric_limits<cost_t>::max() / 4;
	const flow_t INF_FLOW = numeric_limits<flow_t>::max() / 4;
	vector<cost_t> dist;
	__gnu_pbds::priority_queue<pair<cost_t, int>> q;
	vector<typename decltype(q)::point_iterator> its;
	void path(int s) {
		//cerr << "path " << s << '\n';
		dist.assign(N, INF_COST);
		dist[s] = 0;
 
		its.assign(N, q.end());
		its[s] = q.push({0, s});
 
		while (!q.empty()) {
			int i = q.top().second; q.pop();
			cost_t d = dist[i];
			//cerr << i << ' ' << d << '\n';
			for (int e : adj[i]) {
				if (edges[e].cap) {
					int j = edges[e].dest;
					cost_t nd = d + edges[e].cost;
					if (nd < dist[j]) {
						dist[j] = nd;
						prv[j] = e;
						if (its[j] == q.end()) {
							its[j] = q.push({-(dist[j] - pi[j]), j});
						} else {
							q.modify(its[j], {-(dist[j] - pi[j]), j});
						}
					}
				}
			}
		}
 
		swap(pi, dist);
	}
 
	pair<flow_t, cost_t> maxflow(int s, int t) {
		assert(s != t);
		flow_t totFlow = 0; cost_t totCost = 0;
		while (path(s), pi[t] < INF_COST) {
			flow_t curFlow = numeric_limits<flow_t>::max();
			for (int cur = t; cur != s; ) {
				int e = prv[cur];
				int nxt = edges[e^1].dest;
				curFlow = min(curFlow, edges[e].cap);
				cur = nxt;
			}
			totFlow += curFlow;
			totCost += pi[t] * curFlow;
			for (int cur = t; cur != s; ) {
				int e = prv[cur];
				int nxt = edges[e^1].dest;
				edges[e].cap -= curFlow;
				edges[e^1].cap += curFlow;
				cur = nxt;
			}
		}
		return {totFlow, totCost};
	}
 
	explicit MCMF_SSPA(int N_) : N(N_), adj(N), pi(N, 0), prv(N) {}
};

struct MCMF2 {
	vector<vector<FlowEdge>> g;
	MCMF2(int n) : g(n) {}
	void addEdge(int s, int t, Flow c, Flow cost = 0) {
		flow_add_edge(g, s, t, c, cost);
	}
	pair<ll, ll> maxflow(int s, int t) {
		return min_cost_max_flow(g, s, t);
	}
	void setpi(int s) {}
};

// typedef MCMF2 MCMF;

#if 1
static size_t i;
#else
static char buf[450 << 20];
static size_t i = sizeof buf;
void* operator new(size_t s) {
	assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) noexcept {}
#endif

typedef vector<ll> vd;
bool zero(ll x) { return x == 0; }
ll MinCostMatching(const vector<vd>& cost, vi& L, vi& R) {
	int n = sz(cost), mated = 0;
	vd dist(n), u(n), v(n);
	vi dad(n), seen(n);

	/// construct dual feasible solution
	rep(i,0,n) {
		u[i] = cost[i][0];
		rep(j,1,n) u[i] = min(u[i], cost[i][j]);
	}
	rep(j,0,n) {
		v[j] = cost[0][j] - u[0];
		rep(i,1,n) v[j] = min(v[j], cost[i][j] - u[i]);
	}

	/// find primal solution satisfying complementary slackness
	L = vi(n, -1);
	R = vi(n, -1);
	rep(i,0,n) rep(j,0,n) {
		if (R[j] != -1) continue;
		if (zero(cost[i][j] - u[i] - v[j])) {
			L[i] = j;
			R[j] = i;
			mated++;
			break;
		}
	}

	for (; mated < n; mated++) { // until solution is feasible
		int s = 0;
		while (L[s] != -1) s++;
		fill(all(dad), -1);
		fill(all(seen), 0);
		rep(k,0,n)
			dist[k] = cost[s][k] - u[s] - v[k];

		int j = 0;
		for (;;) { /// find closest
			j = -1;
			rep(k,0,n){
				if (seen[k]) continue;
				if (j == -1 || dist[k] < dist[j]) j = k;
			}
			seen[j] = 1;
			int i = R[j];
			if (i == -1) break;
			rep(k,0,n) { /// relax neighbors
				if (seen[k]) continue;
				auto new_dist = dist[j] + cost[i][k] - u[i] - v[k];
				if (dist[k] > new_dist) {
					dist[k] = new_dist;
					dad[k] = j;
				}
			}
		}

		/// update dual variables
		rep(k,0,n) {
			if (k == j || !seen[k]) continue;
			auto w = dist[k] - dist[j];
			v[k] += w, u[R[k]] -= w;
		}
		u[s] += dist[j];

		/// augment along path
		while (dad[j] >= 0) {
			int d = dad[j];
			R[j] = R[d];
			L[R[j]] = j;
			j = d;
		}
		R[j] = s;
		L[s] = j;
	}

	auto value = vd(1)[0];
	rep(i,0,n) value += cost[i][L[i]];
	return value;
}

void testPerf() {
	
	srand(2);
	int N = 500, E = 10000, CAPS = 100, COSTS = 100000;
	MCMF_SSPA<> mcmf(N);
	int s = 0, t = 1;
	rep(i,0,E) {
		int a = rand() % N;
		int b = rand() % N;
		int cap = rand() % CAPS;
		int cost = rand() % COSTS;
		if (a == b) continue;
		mcmf.addEdge(a, b, cap, cost);
		// ::cap[a][b] = cap;
		// ::cost[a][b] = cost;
	}
	auto pa = mcmf.maxflow(s, t);
	cout << pa.first << ' ' << pa.second << endl;
}

void testMatching() {
	
	rep(it,0,100000) {
		size_t last = ::i;
		int N = rand() % 10, M = rand() % 10;
		int NM = max(N, M);
		vector<vd> co(NM, vd(NM));
		rep(i,0,N) rep(j,0,M) co[i][j] = (rand() % 10) + 2;
		vi L, R;
		ll v = MinCostMatching(co, L, R);
		int S = N+M, T = N+M+1;
		MCMF_SSPA<> mcmf(N+M+2);
		rep(i,0,N) mcmf.addEdge(S, i, 1, 0);
		rep(i,0,M) mcmf.addEdge(N+i, T, 1, 0);
		rep(i,0,N) rep(j,0,M) mcmf.addEdge(i, N+j, 1, co[i][j] - 2);
		//mcmf.setpi(S);
		auto pa = mcmf.maxflow(S, T);
		assert(pa.first == min(N, M));
		assert(pa.second == v - 2 * pa.first);
		::i = last;
	}
}

void testNeg() {
	int ed[100][100];
	
	rep(it,0,1000000) {
		size_t lasti = ::i;
		int N = rand() % 7 + 2;
		int M = rand() % 17;
		int S = 0, T = 1;
		
		MCMF_SSPA<> mcmf(N);
		MCMF2 mcmf2(N);
		rep(i,0,N) rep(j,0,N) ed[i][j] = 0;
		rep(eid,0,M) {
			int i = rand() % N, j = rand() % N;

			if (i != j && !ed[i][j]) {
				ed[i][j] = 1;
				int fl = rand() % 50;
				int co = rand() % 11 - 3;
				
				mcmf.addEdge(i, j, fl, co);
				mcmf2.addEdge(i, j, fl, co);
			}
		}/*
		if (!mcmf.setpi(S)) {
			cerr << '!';
			continue;
		}*/

		cerr << '.';
		
		auto pa = mcmf.maxflow(S, T);
		
		auto pa2 = mcmf2.maxflow(S, T);
		
		assert(pa.first == pa2.first && pa.second == pa2.second);

		::i = lasti;
	}
}

int main() {
	testMatching();
	testNeg();
}
