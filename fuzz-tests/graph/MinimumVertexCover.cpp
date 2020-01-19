#include "../utilities/template.h"

#include "../../content/graph/MinimumVertexCover.h"
#include "../../content/graph/HopcroftKarp.h"
#include "../../content/graph/DFSMatching.h"

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
	clock_t start1, end1, start2, end2;
	int a = 0, b = 0;
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
		start1 = clock();
		// mc.improve();
		vi cover1 = cover(gr, N, M, mc);
		end1 = clock();
		start2 = clock();
		vi cover2 = coverHK(gr, N, M);
		end2 = clock();
		// cout << double(end1 - start1)/CLOCKS_PER_SEC << "    " << 
		// double(end2 - start2)/CLOCKS_PER_SEC << endl;
		if (double(end1 - start1)/CLOCKS_PER_SEC > double(end2 - start2)/CLOCKS_PER_SEC) ++a;
		else ++b;
		assert(sz(cover1) == sz(cover2));
		verify(cover1);
		verify(cover2);
		// cout << '.' << endl;
	}
	
	cout<<"Tests passed! " << a << ' ' << b << endl;
}
