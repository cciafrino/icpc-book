/**
 * Author: BenQ
 * License: CC0
 * Description: Knapsack 01 problem, returns a vector that holds each chosen item.
 * Status: tested
 * Time: $O(nW)$
 */

vector<int> Knapsack(int limit, vector<int> &v, vector<int> &w) {
    vector<vector<int>> dp(v.size()+1);
    dp[0].resize(limit+1);
    for (int i = 0; i < v.size(); ++i) {
        dp[i+1] = dp[i];
        for (int j = 0; j <= limit - w[i]; ++j)
            dp[i+1][w[i]+j] = max(dp[i+1][w[i]+j], dp[i][j] + v[i]);
    }
    vector<int> result;
    for (int i = v.size()-1; i >= 0; --i)
        if (dp[i][limit] != dp[i+1][limit]) {
            limit -= w[i];
            result.push_back(i);
        }
    return result;
}
