#include "../utilities/template.h"
using lint = long long;
#include "../../content/graph/PushRelabel.h"
#include "../../content/graph/Dinitz.h"
#include "../../content/graph/EdmondsKarp.h"
#include "../../content/graph/HLPP.h"

template <int MAXN, class T = int> struct HLPPChilli { ///start-hash
    const T INF = numeric_limits<T>::max(); 
    struct edge_t { int to, rev; T flow; };
    int s = MAXN - 1, t = MAXN - 2;
    vector<edge_t> adj[MAXN];
    vector<int> lst[MAXN], gap[MAXN];
    T excess[MAXN];
    int highest, height[MAXN], cnt[MAXN], work;
    void addEdge(int from, int to, int flow, bool isDirected = true) {
        adj[from].push_back({to, (int)adj[to].size(), flow});
        adj[to].push_back({from, (int)adj[from].size() - 1, isDirected ? 0 : flow});
    } ///end-hash
    void updHeight(int v, int nh) { ///start-hash
        work++;
        if (height[v] != MAXN) cnt[height[v]]--;
        height[v] = nh;
        if (nh == MAXN) return;
        cnt[nh]++, highest = nh;
        gap[nh].push_back(v);
        if (excess[v] > 0) lst[nh].push_back(v);
    } ///end-hash
    void globalRelabel() { ///start-hash
        work = 0;
        fill(height, height + MAXN, MAXN);
        fill(cnt, cnt + MAXN, 0);
        for (int i = 0; i < highest; i++)
            lst[i].clear(), gap[i].clear();
        height[t] = 0;
        queue<int> q({t});
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : adj[v])
                if (height[e.to] == MAXN && adj[e.to][e.rev].flow > 0)
                    q.push(e.to), updHeight(e.to, height[v] + 1);
            highest = height[v];
        } 
    } ///end-hash
    void push(int v, edge_t &e) { ///start-hash
        if (excess[e.to] == 0)
            lst[height[e.to]].push_back(e.to);
        T df = min(excess[v], e.flow);
        e.flow -= df, adj[e.to][e.rev].flow += df;
        excess[v] -= df, excess[e.to] += df;
    } ///end-hash
    void discharge(int v) { ///start-hash
        int nh = MAXN;
        for (auto &e : adj[v]) {
            if (e.flow > 0) {
                if (height[v] == height[e.to] + 1) {
                    push(v, e);
                    if (excess[v] <= 0) return;
                } 
                else nh = min(nh, height[e.to] + 1);
            }
        }
        if (cnt[height[v]] > 1) updHeight(v, nh);
        else {
            for (int i = height[v]; i <= highest; i++) {
                for (auto j : gap[i]) updHeight(j, MAXN);
                gap[i].clear();
            }
        }
    } ///end-hash
    T maxflow(int heur_n = MAXN) { ///start-hash
        fill(excess, excess + MAXN, 0);
        excess[s] = INF, excess[t] = -INF;
        globalRelabel();
        for (auto &e : adj[s]) push(s, e);
        for (; highest >= 0; highest--) {
            while (!lst[highest].empty()) {
                int v = lst[highest].back();
                lst[highest].pop_back();
                discharge(v);
                if (work > 4 * heur_n) globalRelabel();
            }
        }
        return excess[t] + INF;
    } ///end-hash
};

// Bump allocator, to speed the test up and get rid of malloc performance noise
static char buf[1 << 23];
static size_t bufi = sizeof buf;
void* operator new(size_t s) {
	assert(s < bufi);
	return (void*)&buf[bufi -= s];
}
void operator delete(void*) {}

int main() {
	long double HLPP1t = 0, PushRelabelt = 0, HLPP2t = 0, HLPP3t;
	rep(it,0,10000) {
		bufi = sizeof buf;
		int n = 2 + rand() % 10;
		int s = rand() % n;
		int t = rand() % (n - 1);
		if (t >= s) t++;
		PushRelabel<ll> pr(n);
		// Dinitz<ll> dinic(n);
		HLPP<ll> flow2(n);
		// vector<unordered_map<int, int>> ek(n);
		HLPPChilli<11000, ll> flowhlpp;
		int m = rand() % 40;
		rep(eit,0,m) {
			int a = rand() % n;
			int b = rand() % n;
			int c = rand() % 4;
			int d = rand() % 4 == 0 ? rand() % 3 + 1 : 0;
			pr.addEdge(a, b, c);
			// dinic.addEdge(a, b, c, d);
			flowhlpp.addEdge(a, b, c);
			flow2.addEdge(a, b, c);
			// ek[a][b] += c;
			// ek[b][a] += d;
		}
		
		// auto origEk = ek;
		auto start_pushRelabel = chrono::high_resolution_clock::now();
		ll flow = pr.maxflow(s, t);
		auto end_pushRelabel = chrono::high_resolution_clock::now();
		auto start_HLPP1 = chrono::high_resolution_clock::now();
		ll result2 = flow2.maxflow(s, t);
		auto end_HLPP1 = chrono::high_resolution_clock::now();
		flowhlpp.s = s, flowhlpp.t = t;
		auto start_HLPP2 = chrono::high_resolution_clock::now();
		ll result = flowhlpp.maxflow();
		auto end_HLPP2 = chrono::high_resolution_clock::now();
		// if (1.0*end_pushRelabel/CLOCKS_PER_SEC > 1.0*end_HLPP2/CLOCKS_PER_SEC)
		// 	PushRelabelt++;
		// else HLPP2t++;
		// if (1.0*end_HLPP2/CLOCKS_PER_SEC > 1.0*end_HLPP1/CLOCKS_PER_SEC)
		// 	HLPP3t++;
		// else HLPP1t++;
		// cout << flow << ' ' << result << endl;
		// PushRelabel matches Dinic
		// ll dinicFlow = dinic.maxflow(s, t);
		// assert(flow == dinicFlow);
		HLPP1t += chrono::duration_cast<chrono::nanoseconds>(end_HLPP1 - start_HLPP1).count();
		HLPP2t += chrono::duration_cast<chrono::nanoseconds>(end_HLPP2 - start_HLPP2).count();
		PushRelabelt += chrono::duration_cast<chrono::nanoseconds>(end_pushRelabel - start_pushRelabel).count();
		assert(flow == result2);
		assert(result == result2);
		// PushRelabel matches EdmondsKarp
		// ll ekFlow = edmondsKarp(ek, s, t);
		// assert(result == ekFlow);

		// Conservation of flow for PushRelabel
		// vector<ll> flows(n);
		// rep(i,0,n) trav(e, pr.g[i]) if (e.f > 0) {
		// 	assert(e.c >= 0);
		// 	flows[i] += e.f;
		// 	flows[e.dest] -= e.f;
		// }
		// assert(flow == flows[s]);
		// assert(flow == -flows[t]);
		// rep(i,0,n) if (i != s && i != t) assert(flows[i] == 0);

		// // Conservation of flow for Dinic
		// vector<ll> dinicFlows(n);
		// rep(i,0,n) trav(e, dinic.adj[i]) {
		// 	assert(e.flow() <= e.oc);
		// 	dinicFlows[i] += e.flow();
		// 	dinicFlows[e.to] -= e.flow();
		// }
		// assert(flows == dinicFlows);

		// // Conservation of flow for EdmondsKarp
		// vector<ll> ekFlows(n);
		// rep(i,0,n) trav(e, origEk[i]) {
		// 	int nc = ek[i][e.first];
		// 	assert(nc >= 0);
		// 	int flow = e.second - nc;
		// 	if (flow > 0) {
		// 		ekFlows[i] += flow;
		// 		ekFlows[e.first] -= flow;
		// 	}
		// }
		// assert(flows == ekFlows);

		// // PushRelabel computes a cut
		// ll acrossCut = 0;
		// assert(pr.leftOfMinCut(s));
		// assert(!pr.leftOfMinCut(t));
		// rep(i,0,n) trav(e, pr.g[i]) {
		// 	if (pr.leftOfMinCut(i) && !pr.leftOfMinCut(e.dest)) {
		// 		assert(e.f >= 0);
		// 		assert(e.c == 0);
		// 		acrossCut += e.f;
		// 	}
		// 	if (!pr.leftOfMinCut(i) && pr.leftOfMinCut(e.dest)) {
		// 		assert(e.f <= 0);
		// 	}
		// }

		// // min cut = max flow
		// assert(acrossCut == flow);
	}
	// cout << "Chilli lost " << HLPP2t << " times, while PushRelabel lost " << PushRelabelt << " times "<<endl;
	// cout << "Chilli lost " << HLPP3t << " times, while china lost " << HLPP1t << " times "<<endl;
	PushRelabelt *= 1e-9;
	HLPP1t *= 1e-9;
	HLPP2t *= 1e-9;
	cout << "PushRelabel: " << PushRelabelt << endl;
	cout << "HLPP Chilli: " << HLPP2t << endl;
	cout << "HLPP China: " << HLPP1t << endl;
	cout << "Tests passed!" << endl;
}
