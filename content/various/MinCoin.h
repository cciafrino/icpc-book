/**
 * Author: Chris
 * License: CC0
 * Description: minimum number of coins to make K
 * Status: tested
 * Time: $O(kV)$
 */

int coin(vector<int> &c, int k) {
    vector<int> dp(k+1, INF); dp[0] = 0;
    for (int i = 0; i < c.size(); ++i) 
        for (int j = c[i]; j <= k; ++j)
            dp[j] = min(dp[j], 1 + dp[j-c[i]]);
    return dp[k];
}

