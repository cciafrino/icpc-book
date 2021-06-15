/**
 * Author: ?, Chris
 * Source: University of Tokyo Notebook
 * Description:  Find the cost of the smallest tree containing all elements of terminal ts for a non-negative undirected graph
 * Time: $O(3^{t}n + 2^{t}n^{2} + n^{3})$
 * 
 */
//TODO: Check what is a terminal...
int Steiner(vector<vector<int>> &g, vector<int> &ts) {
    int n = g.size(), m = ts.size();
    if (m < 2) return 0;
    vector<vector<int>> dp(1<<m, vector<int>(n));
    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i)        
            for(int j = 0; j < n; ++j)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
            dp[1<<i][j] = g[ts[i]][j];
    for (int i = 1; i < (1<<m); ++i) if (((i-1)&i) != 0) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = INF;
            for (int k = (i-1)&i; k > 0; k = (k-1)&i)
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i^k][j]);
        }
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                dp[i][j] = min(dp[i][j], dp[i][k] + g[k][j]);
    }
    return dp[(1<<m)-1][ts[0]];
}
