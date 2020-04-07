/**
 * Author: (From CF tutorial)
 * Description: Find bridges in an undirected graph G. Do not forget
 * to set the first level as 1. (level[0] = 1)
 * 
 */
vector<vector<int>> edges;
vector<int> level, dp;
int bridge = 0;
void dfs(int v, int p) {
    dp[v] = 0;
    for (int u : edges[v]) {
        if (level[u] == 0) {
            level[u] = level[v] + 1;
            dfs(u, v);
            dp[v] += dp[u];
        }
        else if (level[u] < level[v]) dp[v]++;
        else if (level[u] > level[v]) dp[v]--;
    }
    dp[v]--;
    if (level[v] > 1 && dp[v] == 0) // Edge_vp is a bridge
        bridge++;
}
