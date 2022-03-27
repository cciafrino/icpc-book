/**
 * Author: Monsoon
 * License: 
 * Description: Find first value greater than $m$ that cannot be formed by the sums of numbers from $v$.
 * Status: tested
 * Time: 
 */

bitset<int(1e7)> dp, dp1;
int knapsack(vector<int> &items, int n, int m) {
    dp[0] = dp1[0] = true;
    for (int i = 0; i < n; ++i) {
        dp1 <<= items[i];
        dp |= dp1;
        dp1 = dp;   
    }
    dp.flip();
    return dp._Find_next(m);
}
