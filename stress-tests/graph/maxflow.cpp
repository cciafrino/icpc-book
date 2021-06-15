#include "../utilities/template.h"

#include "../../content/graph/PushRelabel.h"
#include "../../content/graph/Dinitz.h"
#include "../../content/graph/EdmondsKarp.h"

// Bump allocator, to speed the test up and get rid of malloc performance noise
static char buf[1 << 23];
static size_t bufi = sizeof buf;
void* operator new(size_t s) {
	assert(s < bufi);
	return (void*)&buf[bufi -= s];
}
void operator delete(void*) {}

using Int = long long;
 
template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }
 
 
namespace MF {
	const int LIM_N = 5001001;
	const int LIM_M = 5001001;
	typedef int wint;
	const wint wEPS = 0;
	const wint wINF = 1001001001;
	int n, m, ptr[LIM_N], nxt[LIM_M * 2], zu[LIM_M * 2];
	wint capa[LIM_M * 2], tof;
	int lev[LIM_N], see[LIM_N], que[LIM_N], *qb, *qe;
	void init(int _n) {
		n = _n; m = 0; fill(ptr, ptr + n, -1);
	}
	void ae(int u, int v, wint w0, wint w1 = 0) {
		nxt[m] = ptr[u]; ptr[u] = m; zu[m] = v; capa[m] = w0; ++m;
		nxt[m] = ptr[v]; ptr[v] = m; zu[m] = u; capa[m] = w1; ++m;
	}
	wint augment(int src, int ink, wint flo) {
		if (src == ink) return flo;
		for (int &i = see[src]; ~i; i = nxt[i]) if (capa[i] > wEPS && lev[src] < lev[zu[i]]) {
			const wint f = augment(zu[i], ink, min(flo, capa[i]));
			if (f > wEPS) {
				capa[i] -= f; capa[i ^ 1] += f; return f;
			}
		}
		return 0;
	}
	bool solve(int src, int ink, wint flo = wINF) {
		for (tof = 0; tof + wEPS < flo; ) {
			qb = qe = que; fill(lev, lev + n, -1);
			for (lev[*qe++ = src] = 0, see[src] = ptr[src]; qb != qe; ) {
				const int u = *qb++;
				for (int i = ptr[u]; ~i; i = nxt[i]) if (capa[i] > wEPS) {
					const int v = zu[i];
					if (lev[v] == -1) {
						lev[*qe++ = v] = lev[u] + 1; see[v] = ptr[v];
						if (v == ink) goto au;
					}
				}
			}
			return false;
		au:	for (wint f; (f = augment(src, ink, flo - tof)) > wEPS; tof += f);
		}
		return true;
	}
}


int main() {
	rep(it,0,1000000) {
		bufi = sizeof buf;
		int n = 2 + rand() % 10;
		int s = rand() % n;
		int t = rand() % (n - 1);
		if (t >= s) t++;
		PushRelabel<int> pr(n);
		Dinitz<int> dinic(n);
		vector<unordered_map<int, int>> ek(n);

		int m = rand() % 40;
		rep(eit,0,m) {
			int a = rand() % n;
			int b = rand() % n;
			int c = rand() % 4;
			int d = rand() % 4 == 0 ? rand() % 3 + 1 : 0;
			pr.addEdge(a, b, c, d);
			dinic.addEdge(a, b, c, d);
			ek[a][b] += c;
			ek[b][a] += d;
		}
		auto origEk = ek;
		
		ll flow = pr.maxflow(s, t);

		// PushRelabel matches Dinic
		ll dinicFlow = dinic.maxflow(s, t);
		assert(flow == dinicFlow);

		// PushRelabel matches EdmondsKarp
		ll ekFlow = edmondsKarp(ek, s, t);
		assert(flow == ekFlow);

		// Conservation of flow for PushRelabel
		vector<ll> flows(n);
		rep(i,0,n) for(auto &e: pr.g[i]) if (e.f > 0) {
			assert(e.c >= 0);
			flows[i] += e.f;
			flows[e.dest] -= e.f;
		}
		assert(flow == flows[s]);
		assert(flow == -flows[t]);
		rep(i,0,n) if (i != s && i != t) assert(flows[i] == 0);

		// Conservation of flow for Dinic
		vector<ll> dinicFlows(n);
		rep(i,0,n) for(auto &e: dinic.adj[i]) {
			assert(e.c >= 0);
			dinicFlows[i] += e.f;
			dinicFlows[e.to] -= e.f;
		}
		assert(flows == dinicFlows);

		// Conservation of flow for EdmondsKarp
		vector<ll> ekFlows(n);
		rep(i,0,n) for(auto &e: origEk[i]) {
			int nc = ek[i][e.first];
			assert(nc >= 0);
			int flow = e.second - nc;
			if (flow > 0) {
				ekFlows[i] += flow;
				ekFlows[e.first] -= flow;
			}
		}
		assert(flows == ekFlows);

		// PushRelabel computes a cut
		ll acrossCut = 0;
		assert(pr.leftOfMinCut(s));
		assert(!pr.leftOfMinCut(t));
		rep(i,0,n) for(auto &e: pr.g[i]) {
			if (pr.leftOfMinCut(i) && !pr.leftOfMinCut(e.dest)) {
				assert(e.f >= 0);
				assert(e.c == 0);
				acrossCut += e.f;
			}
			if (!pr.leftOfMinCut(i) && pr.leftOfMinCut(e.dest)) {
				assert(e.f <= 0);
			}
		}

		// min cut = max flow
		assert(acrossCut == flow);
	}

	cout << "Tests passed!" << endl;
}
