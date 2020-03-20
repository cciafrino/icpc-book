#include "../utilities/template.h"
using lint = long long;
#include "../../content/graph/PushRelabel.h"
#include "../../content/graph/Dinitz.h"
#include "../../content/graph/EdmondsKarp.h"
#include "../../content/graph/HLPP.h"

// Bump allocator, to speed the test up and get rid of malloc performance noise
static char buf[1 << 23];
static size_t bufi = sizeof buf;
void* operator new(size_t s) {
	assert(s < bufi);
	return (void*)&buf[bufi -= s];
}
void operator delete(void*) {}

int main() {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	long double HLPP1t = 0, PushRelabelt = 0, HLPP2t = 0, Dinitzt = 0;
	long double EKt = 0;
	rep(it,0,100000) {
		bufi = sizeof buf;
		int n = 2 + rng() % 10;
		int s = rng() % n;
		int t = rng() % (n - 1);
		if (t >= s) t++;
		PushRelabel<ll> pr(n);
		Dinitz<ll> dinic(n);
		HLPP<ll> flow2(n);
		vector<unordered_map<int, int>> ek(n);
		int m = rng() % 40;
		rep(eit,0,m) {
			int a = rng() % n;
			int b = rng() % n;
			int c = rng() % 4;
			int d = rng() % 4 == 0 ? rng() % 3 + 1 : 0;
			pr.addEdge(a, b, c);
			dinic.addEdge(a, b, c);
			flow2.addEdge(a, b, c);
			ek[a][b] += c;
			// ek[b][a] += c;
		}
		
		auto origEk = ek;

		auto start_pushRelabel = chrono::high_resolution_clock::now();
		ll flow = pr.maxflow(s, t);
		auto end_pushRelabel = chrono::high_resolution_clock::now();

		auto start_HLPP1 = chrono::high_resolution_clock::now();
		ll result2 = flow2.maxflow(s, t);
		auto end_HLPP1 = chrono::high_resolution_clock::now();	

		auto start_dinic = chrono::high_resolution_clock::now();
		ll dinicFlow = dinic.maxflow(s, t);
		auto end_dinic = chrono::high_resolution_clock::now();

		auto start_ek = chrono::high_resolution_clock::now();
		ll ekFlow = edmondsKarp(ek, s, t);
		auto end_ek = chrono::high_resolution_clock::now();

		Dinitzt +=chrono::duration_cast<chrono::nanoseconds>(end_dinic - start_dinic).count(); 
		HLPP1t += chrono::duration_cast<chrono::nanoseconds>(end_HLPP1 - start_HLPP1).count();
		PushRelabelt += chrono::duration_cast<chrono::nanoseconds>(end_pushRelabel - start_pushRelabel).count();
		EKt += chrono::duration_cast<chrono::nanoseconds>(end_ek - start_ek).count();

		assert(result2 == ekFlow);
		assert(flow == dinicFlow);
		assert(flow == result2);
		assert(result2 == dinicFlow);

		// Conservation of flow for PushRelabel
		vector<ll> flows(n);
		rep(i,0,n) trav(e, pr.g[i]) if (e.f > 0) {
			assert(e.c >= 0);
			flows[i] += e.f;
			flows[e.dest] -= e.f;
		}
		assert(flow == flows[s]);
		assert(flow == -flows[t]);
		rep(i,0,n) if (i != s && i != t) assert(flows[i] == 0);

		// Conservation of flow for Dinic
		vector<ll> dinicFlows(n);
		rep(i,0,n) trav(e, dinic.adj[i]) if (e.f > 0) {
			assert(e.c >= 0);
			dinicFlows[i] += e.f;
			dinicFlows[e.to] -= e.f;
		}
		assert(flows == dinicFlows);

		// Conservation of flow for EdmondsKarp
		vector<ll> ekFlows(n);
		rep(i,0,n) trav(e, origEk[i]) {
			int nc = ek[i][e.first];
			assert(nc >= 0);
			int flow = e.second - nc;
			if (flow > 0) {
				ekFlows[i] += flow;
				ekFlows[e.first] -= flow;
			}
		}
		assert(flows == ekFlows);

		// // PushRelabel computes a cut
		ll acrossCut = 0;
		assert(pr.leftOfMinCut(s));
		assert(!pr.leftOfMinCut(t));
		rep(i,0,n) trav(e, pr.g[i]) {
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
	PushRelabelt *= 1e-9;
	HLPP1t *= 1e-9;
	Dinitzt *= 1e-9;
	EKt *= 1e-9;
	cout << "PushRelabel: " << PushRelabelt << endl;
	cout << "Dinitz: " << Dinitzt << endl;
	cout << "HLPP: " << HLPP1t << endl;
	cout << "EK: " << EKt << endl;
	cout << "Tests passed!" << endl;
}
