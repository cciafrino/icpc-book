/**
 * Author: LeticiaFCS
 * License: CC0
 * Description: Two maximum equal sum disjoint subsets,
 * s[i] = 0 if v[i] wasn't selected, s[i] = 1 if v[i] is
 * in the first subset and s[i] = 2 if v[i] is in the
 * second subset
 * Status: tested on URI1700 and leetcode Tallest Billboard
 * Time: $O(n * S)$
 */
auto twoMaxEqualSumDS(const vector<int> &v){
    int sum=accumulate(v.begin(), v.end(), 0), n=int(v.size());
    vector<int> old(2*sum + 1, INT_MIN/2), dp(2*sum + 1), s(n);
    vector<vector<int>> rec(n, vector<int>(2*sum + 1));
    int i; old[sum] = 0;
    for(i = 0; i < n; ++i, swap(old, dp))
        for(int a, b, d = v[i]; d <= 2*sum - v[i]; d++){
            dp[d] = max(old[d], a = old[d - v[i]] + v[i]);
            dp[d] = max(dp[d], b = old[d + v[i]]);
            rec[i][d] = dp[d] == a ? 1 : dp[d] == b ? 2 : 0;
        }
    for(int j = i-1, d = sum; j >= 0; --j)
        d+=(s[j] = rec[j][d]) ? s[j] == 2 ? v[j] : - v[j] : 0;
    return make_pair(old[sum], s);
}
