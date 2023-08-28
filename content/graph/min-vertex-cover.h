/**
 * Author: Johan Sannemo, Simon Lindholm, Chris
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set.
 * Status: stress-tested
 */
#include "bipartite-matching.h"
vector<int> cover(bm_t& B, int N, int M) {
	int ma = B.solve();
	vector<bool> lfound(N, true), seen(N+M);
	for (int i = N; i < N+M; ++i) if (B.match[i] != -1) 
		lfound[B.match[i]] = false;
	vector<int> q, cover;
	for (int i = 0; i < N; ++i) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int v = q.back(); q.pop_back();
		lfound[v] = true;
		for(int e : B.adj[v]) if (!seen[e] && B.match[e] != -1) {
			seen[e] = true;
			q.push_back(B.match[e]);
		}
	}
	for (int i = 0; i < N; ++i) if (!lfound[i]) cover.push_back(i);
	for (int i = N; i < N+M; ++i) if (seen[i]) cover.push_back(i);
	assert(cover.size() == ma);
	return cover;
}
