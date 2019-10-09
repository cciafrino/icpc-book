/**
 * Author: Chris
 * Source: 
 * Description: Find if exist an hamiltonian path
 * Time: $O(2^n  n^{2})$
 * 
 */

bool hamiltonian(vector<vector<int>> &edges, int n) {
	array<array<bool, MAXN>, MAXN> dp;
	for (int i = 0; i < n; ++i) dp[i][1<<i] = 1;
	for (int i = 0; i < (1 << n); ++i) {
		for (int j = 0; j < n; ++j) 
			if (i & (1 << j)) {
				for (int k = 0; k < n; ++k)
					if (i & (1 << k) && edges[k][j] && k != j && dp[k][i^(1<<j)]) {
						dp[i][j] = 1;
						break;
					}
			}
	}
	for (int i = 0; i < n; ++i)
		if (dp[i][(1 << n)-1]) return 1;
	return 0;
}