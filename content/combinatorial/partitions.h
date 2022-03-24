/**
 * Author: Chris
 * Date: 2021
 * License: 
 * Source: Hos
 * Status: 
 * Description: Fills array with partition function $p(n)$  $\forall 0 \leq i leq n$
 * Usage:
 * Time: 
 */
const int M = 998244353;
vector<int64_t> prep(int N) {
    vector<int64_t> dp(N); dp[0] = 1;
    for (int n = 1; n < N; ++n) {
        int64_t sum = 0;
        for (int k = 0, l = 1, m = n - 1; ;) {
            sum += dp[m]; if ((m -= (k += 1)) < 0) break;
            sum += dp[m]; if ((m -= (l += 2)) < 0) break;
            sum -= dp[m]; if ((m -= (k += 1)) < 0) break;
            sum -= dp[m]; if ((m -= (l += 2)) < 0) break;
        }
        if ((sum %= M) < 0) sum += M;
        dp[n] = sum;
    }
    return dp;
}
