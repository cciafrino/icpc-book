/**
 * Author: Rodrigo Zhou
 * Description: 
 */
 
vector<int> cut, mark, low, par;
vector<vector<int>> edges;
int Time = 0;

void dfs(int v, int p) {
    int cnt = 0;
    par[v] = p;
    low[v] = mark[v] = Time++;
    for (int u : edges[v]) {
        if (mark[u] == -1) {
            par[u] = v; 
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] >= mark[v]) cnt++;
            //if (low[u] > mark[v]) u-v bridge            
        }
        else if (u != par[v]) low[v] = min(low[v], mark[u]);
    }
    if (cnt > 1 || (mark[v] != 0 && cnt > 0)) cut[v] = 1;
}
void solve(int n) {
    cut.resize(n, 0);
    mark.resize(n, -1);
    low.resize(n, 0);
    par.resize(n, 0);
    for (int i = 0; i < n; ++i) 
        if (mark[i] == -1) {
            Time = 0;
            dfs(i, i);
        }
}
