/**
 * Author: Chris
 * Date: 2020
 * License: CC0
 * Description: Find the minimum numbers of edits required to convert string s into t.
 * Only insertion, removal and replace operations are allowed.
 * Source: https://github.com/ludopulles/tcr/blob/master/code/strings/edit_dist.cpp 
 */

vector<vector<int>> dp(MAX_SIZE_S+1, vector<int>(MAX_SIZE_T+1, INF));
int edit_dist(const string &s, const string &t) {
	dp[0][0] = 0;
    for (int i = 0; i <= s.size(); ++i) {
        for (int j = 0; j <= t.size(); ++j) {
            if (i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
			if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
			if (i > 0 && j > 0)
				dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (s[i-1] != t[j-1]));
        }
    }
    return dp[s.size()][t.size()];
}


