/**
 * Author: Benjamin Qi, Chilli
 * Date: 2020-04-04
 * License: CC0
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Matching/Hungarian.h
 * Description: Given array of (possibly negative) costs to complete $N$ jobs
 * w/ $M$ workers $(N \le M)$, finds min cost to complete all jobs s.t. each
 * worker is assigned to at most one job. Takes cost[N][M], where cost[i][j] =
 * cost for i-th job to be completed by j-th worker and returns (min cost,
 * match), where match[i] = worker assigned to i-th job. Negate costs for max
 * cost.
 * Time: O(N^2M)
 * Status: Tested on kattis:cordonbleu, stress-tested
 */
pair<int, vector<int>> hungarian(const vector<vector<int>> &a) {
	if (a.empty()) return {0, {}};
	int n = a.size() + 1, m = a[0].size() + 1;
	vector<int> u(n), v(m), p(m), ans(n - 1);
	for(int i = 1; i < n; ++i) {
		p[0] = i;
		int j0 = 0; // add "dummy" worker 0
		vector<int> dist(m, INT_MAX), pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			int i0 = p[j0], j1, delta = INT_MAX;
			for(int j = 1; j < m; ++j) if (!done[j]) {
				auto cur = a[i0-1][j-1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			for(int j = 0; j < m; ++j) {
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0) { // update alternating path
			int j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	for(int j = 1; j < m; ++j) if (p[j]) ans[p[j]-1] = j-1;
	return {-v[0], ans}; // min cost
}