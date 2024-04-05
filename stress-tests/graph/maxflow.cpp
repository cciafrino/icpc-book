#include "../utilities/template.h"

#include "../../content/graph/push-relabel.h"
#include "../../content/graph/dinitz.h"

template<class T> T edmondsKarp(vector<unordered_map<int, T>>&
		graph, int source, int sink) {
	assert(source != sink);
	T flow = 0;
	vi par(sz(graph)), q = par;

	for (;;) {
		fill(all(par), -1);
		par[source] = 0;
		int ptr = 1;
		q[0] = source;

		rep(i,0,ptr) {
			int x = q[i];
			for (auto e : graph[x]) {
				if (par[e.first] == -1 && e.second > 0) {
					par[e.first] = x;
					q[ptr++] = e.first;
					if (e.first == sink) goto out;
				}
			}
		}
		return flow;
out:
		T inc = numeric_limits<T>::max();
		for (int y = sink; y != source; y = par[y])
			inc = min(inc, graph[par[y]][y]);

		flow += inc;
		for (int y = sink; y != source; y = par[y]) {
			int p = par[y];
			if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
			graph[y][p] += inc;
		}
	}
}

// Bump allocator, to speed the test up and get rid of malloc performance noise
static char buf[1 << 23];
static size_t bufi = sizeof buf;
void* operator new(size_t s) {
	assert(s < bufi);
	return (void*)&buf[bufi -= s];
}
void operator delete(void*) {}

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
			// dinicFlows[i] += e.f;
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
