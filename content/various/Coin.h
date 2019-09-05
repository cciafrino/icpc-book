/**
 * Author: Chris
 * License: CC0
 * Description: Number of ways to make value K with X coins
 * Status: tested
 * Time: $O(N)$
 */

int coin(vector<int> &c, int k) {
    vector<int> dp(k+1, 0); dp[0] = 1;
    for (int i = 0; i < c.size(); ++i) 
        for (int j = c[i]; j <= k; ++j)
            dp[j] += dp[j-c[i]];
    return dp[k];
}

