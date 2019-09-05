/**
 * Author: 
 * Description: 
 */

struct bridge_t {
    int n, reach, mark, cnt;
    vector<vector<int>> adj;
    bool has_bridge;
    vector<int> parent, inv_preorder;
    bridge_t(int _n) : n(_n), adj(n), inv_preorder(n, -1), has_bridge(false), parent(n), cnt(0) {}
    int dfs(int u) {
        reach = inv_preorder[u] = ++mark;
        bool found = false;
        for (int i = 0; i < (int)adj[u].size(); ++i) {
            int v = adj[u][i];
            if (inv_preorder[v] == -1) {
                parent[v] = u;
                dfs(v);
                reach = min(reach, inv_preorder[v]);
                if (inv_preorder[v] == reach) {
				    ++cnt;
                    printf("Bridge: %d - %d\n", u, v);
                    has_bridge = true;
                }
            }
            else if (!found && v == parent[u]) found = true;
            else reach = min(reach, inv_preorder[v]);
        }
    }
    void solve() {
        for (int i = 0; i < (int)adj.size(); ++i) {
            if (inv_preorder[i] == -1) {
                mark = 0;
                parent[i] = i;
                dfs(i);
            }
        }
    }
};


