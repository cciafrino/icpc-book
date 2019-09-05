/**
 * Author: Chris
 * License: CC0
 * Description: 
 * Status: tested
 * Time: $O(N \log N)$
 */
const int max_value = (int)1e5+10;
int knapsack2(vector<lint> &v, vector<lint> &w, int n, int total) {
    vector<lint> dp(max_value, 2e18); dp[0] = 0;
    for (int i = 0; i < n; ++i) 
        for (int j = max_value - v[i] - 1; j >= 0; --j)   
            dp[j + v[i]] = min(dp[j + v[i]], dp[j] + w[i]);
    for (int i = max_value-1; i >= 0; --i)
        if (dp[i] <= total) return i;
}
