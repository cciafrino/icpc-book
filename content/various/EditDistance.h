/**
 * Author: ?
 * Date: 2010-11-07
 * License: CC0
 * Description: Find the minimum numbers of edits required to convert string s into t.
 * Only insertion, removal and replace operations are allowed.
 * Source: https://github.com/ludopulles/tcr/blob/master/code/strings/edit_dist.cpp 
 */

vector<vector<int>> dp(MAX_SIZE, vector<int>(MAX_SIZE));
int levDist(const string &s, const string &t) {
    for (int i = 0; i <= s.size(); ++i) dp[i][0] = i;
    for (int i = 0; i <= t.size(); ++i) dp[0][i] = i;
    for (int i = 1; i <= s.size(); ++i) {
        for (int j = 1; j <= t.size(); ++j) {
            dp[i][j] = min(1 + min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]+(s[i-1] != t[i-1]));
        }
    }
    return dp[s.size()][t.size()];
}


