/**
 * Author: Tourist-Chris
 * Description: Find cycles in digraph*, at least one in every connected
 * component, cycles are given by edges id, all cycles are simple. The 
 * function returns the edges in each cycle found, each edges are 
 * represented by an id.
 * TODO Not fully tested for digraphs, not tested for undigraphs.
 */

struct SolveCycle {
    int cnt, sz, total_sz, n;
    vector<int> st, pre;
    vector<vector<int>> graph, cycles;
    vector<pair<int,int>> edges;
    SolveCycle(int _n) : n(_n), cnt(1<<30), sz(1<<30), total_sz(0),
    graph(n) {}
    void add(int a, int b) {
        graph[a].push_back(edges.size());
        edges.emplace_back(a, b);
    }
    void dfs(int v, int p) {
        pre[v] = st.size();
        for (int u : edges[v]) {
            if (u == p) continue;
            auto &e = edges[u];
            int to = e.first ^ e.second ^ v;
            if (pre[to] >= 0) {
                vector<int> cycle(1, u);
                for (int i = pre[to]; i < st.size(); ++i) 
                    cycle.push_back(st[i]);
                cycles.push_back(cycle);
                total_sz += cycle.size();
                if (cycles.size() >= cnt || total_size >= cnt)
                    return;
            }
            if (pre[to] == -1) {
                st.push_back(u);
                dfs(to, u);
                st.pop_back();
            }
        }
        pre[v] = -2;
    }
    vector<vector<int>> find_cycles(int n) {
        pre.resize(n, -1);
        total_sz = 0;
        for (int i = 0; i < n; ++i)
            if (pre[i] == -1) dfs(i, -1);
        return cycles;
    }
};

