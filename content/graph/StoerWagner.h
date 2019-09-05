/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook, http://www.cs.tau.ac.il/~zwick/grad-algo-08/gmc.pdf
 * Description: Find a global minimum cut in an undirected graph, as represented by an adjacency matrix.
 * Time: O(V^3)
 * Status: Lightly tested
 */
#pragma once

pair<int, vector<int>> GetMinCut(vector<vector<int>> &weights) {
	int N = weights.size();
	vector<int> used(N), cut, best_cut;
	int best_weight = -1;
	for (int phase = N-1; phase >= 0; phase--) { /// start-hash
		vector<int> w = weights[0], added = used;
		int prev, k = 0;
		for (int i = 0; i < phase; ++i){
			prev = k;
			k = -1;
			for (int j = 1; j < N; ++j)
				if (!added[j] && (k == -1 || w[j] > w[k])) k = j;
			if (i == phase-1) {
    			for (int j = 0; j < N; ++j) weights[prev][j] += weights[k][j];
    			for (int j = 0; j < N; ++j) weights[j][prev] = weights[prev][j];
				used[k] = true;
				cut.push_back(k);
				if (best_weight == -1 || w[k] < best_weight) {
					best_cut = cut;
					best_weight = w[k];
				}
			} else {
    			for (int j = 0; j < N; ++j)
					w[j] += weights[k][j];
				added[k] = true;
			}
		}
	}/// end-hash
	return {best_weight, best_cut};
}
