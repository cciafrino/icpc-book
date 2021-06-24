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
array<i64, 50010> dp;
void prep(int N) {
    dp[0] = 1;
    for (int n = 1; n < N; ++n) {
        i64 sum = 0;
        for (int k = 0, l = 1, m = n - 1; ;) {
            sum += dp[m]; if ((m -= (k += 1)) < 0) break;
            sum += dp[m]; if ((m -= (l += 2)) < 0) break;
            sum -= dp[m]; if ((m -= (k += 1)) < 0) break;
            sum -= dp[m]; if ((m -= (l += 2)) < 0) break;
        }
        if ((sum %= M) < 0) sum += M;
        dp[n] = sum;
    }
}
