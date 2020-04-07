/**
 * Author: Chris
 * License: CC0
 * Description: Given weights and values of n items, put these items in a 
 * knapsack of capacity W to get the maximum total value possible. More efficient
 * space-wise since we work in only one row.
 * Status: tested
 * Time: $O(NW)$
 */
 
int knapsack(int limit, vector<int> &v, vector<int> &w) {
    vector<int> dp(limit+1, -1); int n = w.size();
    dp[0] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = limit; j >= w[i]; --j)
            if (dp[j - w[i]] >= 0)
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    int result = 0;
    for (int i = 0; i <= limit; ++i) 
        result = max(result, dp[i]);
    return result;
}