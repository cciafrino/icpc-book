/**
 * Author: Chris
 * Source: 
 * Description: Computes the maximum sum of a non consecutive subsequence.
 * Time: $O(N)$
 * 
 */
const int MAXN = 100, MAXM = 100;
array<int, MAXN> A, dp;
int solve(int N) {
    dp[0] = A[0] > 0 ? A[0] : 0;
    if (N > 1) dp[1] = max(dp[0], A[1]);
    for (int i = 2; i < N; i++) dp[i] = max(dp[i - 2] + A[i], dp[i - 1]);
    return dp[N - 1];
}
