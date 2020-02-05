/**
 * Author: Chris
 * License: 
 * Description: Knapsack with definition changed. Support large values because the weight isn't a dimension in our dp anymore.
 * Status: tested
 * Time: $O(vW)$ where $v$ is the sum of values.
 */
constexpr int limit = (int)1e5+10;
int knapsack(int capacity, vector<lint> &v, vector<lint> &w) {
    vector<lint> dp(limit, 1LL << 60); dp[0] = 0;
    for (int i = 0; i < v.size(); ++i) 
        for (int j = limit-v[i]-1; j >= 0; --j)   
            dp[j + v[i]] = min(dp[j + v[i]], dp[j] + w[i]);
    for (int i = limit-1; i >= 0; --i)
        if (dp[i] <= capacity) return i;
}
