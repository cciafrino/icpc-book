/**
 * Author: Chris
 * License: 
 * Description: Knapsack problem but now take the same item multiple items is allowed.
 * Status: tested
 * Time: $O(N \log N)$
 */

int knapsack(vector<int> &v, vector<int> &w, int total) {
    vector<int> dp(total+1, -1);
    int result = 0; dp[0] = 0;
    for (int i = 0; i <= total; ++i) for (int j = 0; j < n; ++j)
        if (w[j] <= i && dp[i - w[j]] >= 0) 
            dp[i] = max(dp[i], dp[i - w[j]] + v[j]);
    int result = 0;
    for (int i = 0; i <= total; ++i) result = max(result, dp[i]);
    return result;
}
