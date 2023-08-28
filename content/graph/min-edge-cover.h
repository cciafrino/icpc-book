/**
 * Author: Chris
 * Date: 2020-03-21
 * License: CC0
 * Description: Finds a minimum edge cover in a bipartite graph.
 *  The size is the same as the number of vertices minus the size of a maximum matching.
 * The mark vector represents who the vertices of set $B$ has an edge to.
 * Usage: vector<int> mark(n+m, -1);
 auto cover = minEdgeCover(g, mark, n, m);
 * Status: Tested
 */
#include "bipartite-matching.h"
vector<pair<int,int>> minEdgeCover(bm_t& g, vector<int>& mark, int N, int M) {
	int ma = g.solve();
	vector<pair<int,int>> cover;
	for (int i = 0; i < N; ++i) {
		if (g.match[i] >= 0) cover.push_back({i, g.match[i]-N});
		else if (int(g.adj[i].size())) 
			cover.push_back({i, g.adj[i][0] - N});
	}
	for (int i = N; i < N + M; ++i) 
		if (g.match[i] == -1 && mark[i] >= 0) 
			cover.push_back({mark[i], i - N});
	return cover;
}
