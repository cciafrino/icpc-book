/**
 * Author: BenQ
 * License: CC0
 * Description: 
 * Status: tested
 * Time: $O(N \log N)$
 */

int unbounded_knapsack(vector<int> &v, vector<int> &w, int total) {
    vector<int> dp(total+1, 0);
    int result = 0;
    for (int i = 0; i <= total; ++i) for (int j = 0; j < n; ++j)
        if (w[j] <= i) dp[i] = max(dp[i], dp[i - w[j]] + v[j]);
    return dp[total];
}
