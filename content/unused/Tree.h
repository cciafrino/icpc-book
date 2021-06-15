/**
 * Author: Chris
 * Description: Structure that handles tree's, can find its diameter
 * points, diameter length, center vertices, etc. Consider using two BFS's if
 * constraints are too tight.
 */

struct tree_t {
    int n;
    vector<vector<int>> edges;
    vector<int> parent, dist;
    pair<int, int> center, diameter;
    tree_t(vector<vector<int>> g) : n(g.size()), parent(n), dist(n) {
        edges = g;
        diameter = {1, 1};
    }
    void dfs(int v, int p) {
        for (int u : edges[v]) {
            if (u == p) continue;
            parent[u] = v;
            dist[u] = dist[v] + 1;
            dfs(u, v);
        }
    }
    pair<int,int> find_diameter() { // diameter start->finish point
        parent[0] = -1; dist[0] = 0;
        dfs(0, 0);
        for (int i = 0; i < n; ++i)
            if (dist[i] > dist[diameter.first]) diameter.first = i;
        parent[diameter.first] = -1;
        dist[diameter.first] = 0;
        dfs(diameter.first, diameter.first);
        for (int i = 0; i < n; ++i)
            if (dist[i] > dist[diameter.second]) diameter.second = i;
        return diameter;
    }
    int get_diameter() { // length of diameter
        diameter = find_diameter();
        return dist[diameter.second];
    }
    pair<int,int> find_center() { 
        diameter = find_diameter();
        int k = diameter.second, length = dist[diameter.second];
        for (int i = 0; i < length/2; ++i) k = parent[k];
        if (length%2) return center = {k, parent[k]}; // two centers
        else return center = {k, -1}; // k is the only center of the tree
    }
};
