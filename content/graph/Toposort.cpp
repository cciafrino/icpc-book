const int N  = 1e2 + 5;
vector<int> vis, adj, toposort; //Reverse order in toposort vector
void ts(int u){
    vis[u] = true;
    for (int i = 0, v; i < (int) adj[u].size(); ++i){
        v = adj[u][i];
        if (!vis[v]) ts[v];
    }
    toposort.push_back(u);
}
