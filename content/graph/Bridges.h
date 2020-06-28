/**
 * Author: (From CF tutorial)
 * Description: Find bridges in an undirected graph G. Do not forget
 * to set the first depth as 1. (depth[0] = 1)
 * 
 */
vector<vector<int>> edges;
vector<int> depth, dp;
int bridge = 0;
void dfs(int v, int p) {
    dp[v] = 0;
    for (int u : edges[v]) {
        if (depth[u] == 0) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
            dp[v] += dp[u];
        }
        else if (depth[u] < depth[v]) dp[v]++;
        else if (depth[u] > depth[v]) dp[v]--;
    }
    dp[v]--;
    if (depth[v] > 1 && dp[v] == 0) // Edge_vp is a bridge
        bridge++;
}
