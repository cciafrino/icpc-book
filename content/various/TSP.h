/**
 * Author: BenQ
 * License: CC0
 * Description:  Solve the Travelling Salesman Problem.
 * Status:
 * Time: $O(N^2*2^N)$
 */
const int MX = 15;
array<array<int, MX>, 1<<N> dp;
array<array<int, MX>, MX> dist;
int N;

int TSP(int n) {
    dp[0][1] = 0;
    for (int j = 0; j < (1 << n); ++j)
        for (int i = 0; i < n; ++i)
            if (j & (1<<i))
                for (int k = 0; k < n; ++k)
                    if (!(j & (1<<k)))
                        dp[k][j^(1<<k)] = min(dp[k][j^(1<<k)], dp[i][j]+dist[i][k]);
    int ret = (1 << 31); // = INF
    for (int i = 1; i < n; ++i)
        ret = min(ret, dp[i][(1<<n)-1] + dist[i][0]);
    return ret;
}
