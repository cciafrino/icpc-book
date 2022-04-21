#include "../utilities/template.h"

// #include "mcmf3.h"
// #include "mcmf4.h"
// #include "mcmfold.h"
// #include "mcmfnew.h"
//#include <bits/extc++.h>
// #define setpi dummy(){} bool setpi
// #undef assert
// #define assert(x) return x
#include "../../content/graph/min-cost-max-flow.h"
// #undef assert
// #undef setpi
#include <cassert>
#include "MinCostMaxFlow2.h"

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

struct edge_t { int a, b, w, s() { return (a < b ? a : -a); }};
vector<int> negCyc(int n, vector<edge_t>& edges) {
    vector<int64_t> d(n); vector<int> p(n);
    int v = -1;
    for (int i = 0; i < n; ++i) {
        v = -1; 
        for (edge_t &u : edges)
            if (d[u.b] > d[u.a] + u.w) {
                d[u.b] = d[u.a] + u.w;
                p[u.b] = u.a, v = u.b;
            }
        if (v == -1) return {};
    }
    for (int i = 0; i < n; ++i) v = p[v]; // enter cycle
    vector<int> cycle = {v}; 
    while (p[cycle.back()] != v) cycle.push_back(p[cycle.back()]);
    return {cycle.rbegin(), cycle.rend()};
}

void testPerf() {
	srand(2);
	int N = 500, E = 10000, CAPS = 100, COSTS = 100000;
	min_cost<ll, ll> mcmf(N+10);
	int s = 0, t = 1;
	rep(i,0,E) {
		int a = rand() % N;
		int b = rand() % N;
		int cap = rand() % CAPS;
		int cost = rand() % COSTS;
		if (a == b) continue;
		mcmf.add_edge(a, b, cap, cost);
		// ::cap[a][b] = cap;
		// ::cost[a][b] = cost;
	}
	auto pa = mcmf.run(s, t);
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
		min_cost<ll, ll> mcmf(N+M+20);
		rep(i,0,N) mcmf.add_edge(S, i, 1, 0);
		rep(i,0,M) mcmf.add_edge(N+i, T, 1, 0);
		rep(i,0,N) rep(j,0,M) mcmf.add_edge(i, N+j, 1, co[i][j] - 2);
		auto pa = mcmf.run(S, T);
		assert(pa.first == min(N, M));
		assert(pa.second == v - 2 * pa.first);
		::i = last;
	}
	cout << "Tests passed!" << endl;
}

void testNeg() {
	int ed[100][100];
	rep(it,0,1000000) {
		size_t lasti = ::i;
		int N = rand() % 7 + 2;
		int M = rand() % 17;
		int S = 0, T = 1;
		min_cost<ll, ll> mcmf(N+10);
		MCMF2 mcmf2(N+10);
		rep(i,0,N) rep(j,0,N) ed[i][j] = 0;
		vector<edge_t> edges; edges.reserve(M);
		rep(eid,0,M) {
			int i = rand() % N, j = rand() % N;
			if (i != j && !ed[i][j]) {
				ed[i][j] = 1;
				int fl = rand() % 50;
				int co = rand() % 11 - 3;
				mcmf.add_edge(i, j, fl, co);
				mcmf2.addEdge(i, j, fl, co);
				edges.push_back({i, j, co});
			}
		}

		if (!negCyc(N, edges).empty()) continue;
		auto pa = mcmf.run(S, T);
		auto pa2 = mcmf2.maxflow(S, T);
		assert(pa == pa2);
		::i = lasti;
	}
	cout<<"Tests passed!"<<endl;
}

int main() {
	testMatching();
	testNeg();
}
