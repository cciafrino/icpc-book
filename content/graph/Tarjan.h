/**
 * Author: Chris
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Usage: cnt_of[i] holds the
 * component index of a node (a component only has edges to
 * components with lower index). ncnt will contain the
 * number of components.
 */
struct tarjan_t { 
    int n, ncnt = 0, time = 0;
    vector<vector<int>> edges;
    vector<int> preorder_of, cnt_of, order;
    stack<int> stack_t;
    tarjan_t(int n): n(n), edges(n), preorder_of(n, 0), cnt_of(n, -1) {}
    int dfs(int u) { /// start-hash
        int reach = preorder_of[u] = ++time, v;
        stack_t.push(u);
        for (int v : edges[u]) 
            if (cnt_of[v] == -1) 
                reach = min(reach, preorder_of[v]?:dfs(v));
        if (reach == preorder_of[u]) { 
            do {
                v = stack_t.top();
                stack_t.pop();
                order.push_back(v);
                cnt_of[v] = ncnt;
            } while (v != u);
            ++ncnt;
        }
        return preorder_of[u] = reach;
    }/// end-hash
    void solve() {
        time = ncnt = 0;
        for (int i = 0; i < (int)edges.size(); ++i)
            if (cnt_of[i] == -1) dfs(i);
    }
};
