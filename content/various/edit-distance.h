/**
 * Author: Chris
 * Date: 2020
 * License: CC0
 * Description: Find the minimum numbers of edits required to convert string s into t.
 * Only insertion, removal and replace operations are allowed.
 * Source: 
 */
int edit_dist(string &s, string &t) {
	const int n = int(s.size()), m = int(t.size());
	vector<vector<int>> dp(n+1, vector<int>(m+1, n+m+2));
	vector<vector<int>> prv(n+1, vector<int>(m+1, 0));
	dp[0][0] = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i < n) { // remove
				int cnd = dp[i][j] + 1;
				if (cnd < dp[i+1][j]) {
					dp[i+1][j] = cnd;
					prv[i+1][j] = 1;
				}
			}
			if (j < m) { // insert
				int cnd = dp[i][j] + 1;
				if (cnd < dp[i][j+1]) {
					dp[i][j+1] = cnd;
					prv[i][j+1] = 2;
				}
			}
			if (i < n && j < m) { // modify
				int cnd = dp[i][j] + (s[i] != t[j]);
				if (cnd < dp[i+1][j+1]) {
					dp[i+1][j+1] = cnd;
					prv[i+1][j+1] = 3;
				}
			}
		}
	}
	return dp[n][m];
}


