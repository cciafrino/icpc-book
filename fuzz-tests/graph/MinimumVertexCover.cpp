#include "../utilities/template.h"

#include "../../content/graph/HopcroftKarp.h"
#include "../../content/graph/DFSMatching.h"
#include "../../content/graph/MinimumVertexCover.h"

vi coverHK(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = dfsMatching(g, match);
	vector<bool> lfound(n, true), seen(m);
	trav(it, match) if (it != -1) lfound[it] = false;
	vi q, cover;
	rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		trav(e, g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}

int main() {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	long double kuhn = 0, kactl = 0;
	rep(it,0,300000) {
		int N = rand() % 20, M = rand() % 20;
		int prop = rand();
		vector<vi> gr(N);
		vi left(N), right(M);
		BipartiteMatcher mc(N, M);
		rep(i,0,N) rep(j,0,M) if (rand() < prop) {
			gr[i].push_back(j);
			mc.addEdge(i,j);
		}
		auto verify = [&](vi& cover) {
			trav(x, cover) {
				if (x < N) left[x] = 1;
				else right[x - N] = 1;
			}
			rep(i,0,N) if (!left[i]) trav(j,gr[i]) {
				assert(right[j]);
				/* if (!right[j]) {
					cout << N << ' ' << M << endl;
					rep(i,0,N) trav(j, gr[i]) cout << i << " - " << j << endl;
					cout << "yields " << sz(cover) << endl;
					trav(x, cover) cout << x << endl;
					abort();
				} */
			}
		};

		auto start_kuhn = chrono::high_resolution_clock::now();
		vi cover1 = cover(mc, N, M);
		auto end_kuhn = chrono::high_resolution_clock::now();
		
		auto start_kactl = chrono::high_resolution_clock::now();
		vi cover2 = coverHK(gr, N, M);
		auto end_kactl = chrono::high_resolution_clock::now();
		
		kuhn +=  chrono::duration_cast<chrono::nanoseconds>(end_kuhn - start_kuhn).count(); 
		kactl += chrono::duration_cast<chrono::nanoseconds>(end_kactl - start_kactl).count(); 
		
		assert(sz(cover1) == sz(cover2));
		verify(cover1);
		verify(cover2);
		// cout << '.' << endl;
	}
	kuhn *= 1e-9;
	kactl *= 1e-9;
	cout << "Fast Kuhn's performance: " << kuhn << endl;
	cout << "Kactl's implementation performance: " << kactl << endl;
	cout<<"Tests passed!" << endl;
}
