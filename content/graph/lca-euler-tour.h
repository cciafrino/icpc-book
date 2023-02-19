/**
 * Author: 
 * Date: 2021-02-19
 * License: 
 * Source: 
 * Status: stress-tested
 * Description: Data structure for computing lowest common ancestors and build Euler Tour in a tree.
 * Edges should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: $O(N \log N + Q + Q \log)$
 */

struct small_lca_t {
    int T = 0;
    vector<int> time, path, walk, depth;
    rmq_t<int> rmq;
    small_lca_t(vector<vector<int>> &edges) : time(int(edges.size())), 
    depth(time), rmq((dfs(edges,0,-1), walk)) {}
    void dfs(vector<vector<int>> &edges, int v, int p) {
        time[v] = T++;
        for(int u : edges[v]) {
            if (u == p) continue;
            depth[u] = depth[v] + 1; 
            path.push_back(v), walk.push_back(time[v]);
            dfs(edges, u, v);
        }
    }
    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
};

struct lca_t {
    int N;
    vector<vector<int>> adj;
    vector<int> parent, depth, sz;
    vector<int> euler_tour, timer;
    vector<int> tour_in, tour_out, postorder;
    vector<int> idx, rev_idx;
    vector<int> heavy_root;
    rmq_t<pair<int,int>> rmq;
    int next_idx = 0, rev_next_idx = 0;
    bool built = false;
    lca_t() : N(0) {}
    lca_t(vector<vector<int>>& _adj, int root = -1, bool build_rmq = true) :
        N(int(_adj.size())), adj(_adj), parent(N, -1), depth(N), sz(N), timer(N),
        tour_in(N), tour_out(N), postorder(N), idx(N), heavy_root(N), 
        built(false) {
 
        if (0 <= root && root < N) pre_dfs(root, -1);
 
        euler_tour.reserve(2 * N);
        
        for (int i = 0; i < N; ++i) 
            if (parent[i] == -1) {
                if (i != root) pre_dfs(i, -1);
                dfs(i, false);
                euler_tour.push_back(-1);
            }
 
        rev_idx = idx;
        reverse(rev_idx.begin(), rev_idx.end());
        assert(int(euler_tour.size()) == 2 * N);
        vector<pair<int, int>> euler_tour_depths;
        euler_tour_depths.reserve(euler_tour.size());
 
        int id = 0;
        for (int cur : euler_tour) {
            euler_tour_depths.push_back({cur == -1 ? cur : depth[cur], id++});
        }
 
        if (build_rmq) rmq = rmq_t<pair<int, int>>(euler_tour_depths);
        built = true;
    }
    
    void pre_dfs(int cur, int par) {
        parent[cur] = par;
        depth[cur] = (par == -1 ? 0 : 1 + depth[par]);
        adj[cur].erase(remove(adj[cur].begin(), adj[cur].end(), par), adj[cur].end());
        sz[cur] = 1;
        for (int nxt : adj[cur]) {
            pre_dfs(nxt, cur);
            sz[cur] += sz[nxt];
        }
        if (!adj[cur].empty()) {
            auto w = max_element(adj[cur].begin(), adj[cur].end(), [&](int a, int b) { return sz[a] < sz[b]; });
            swap(*adj[cur].begin(), *w);
        }
    }
 
    void dfs(int cur, bool heavy) {
        heavy_root[cur] = heavy ? heavy_root[parent[cur]] : cur;
        timer[cur] = int(euler_tour.size());
        euler_tour.push_back(cur);
        idx[next_idx] = cur;
        tour_in[cur] = next_idx++;
        bool heavy_child = true;
        for (int next : adj[cur]) {
            dfs(next, heavy_child);
            euler_tour.push_back(cur);
            heavy_child = false;
        }
        tour_out[cur] = next_idx;
        postorder[cur] = rev_next_idx++;
    }
  
    pair<int, array<int, 2>> get_diameter() const {
        assert(built);
        pair<int, int> u_max = {-1, -1};
        pair<int, int> ux_max = {-1, -1};
        pair<int, array<int, 2>> uxv_max = {-1, {-1, -1}};
        for (int cur : euler_tour) {
            if (cur == -1) break;
            u_max = max(u_max, {depth[cur], cur});
            ux_max = max(ux_max, {u_max.first - 2 * depth[cur], u_max.second});
            uxv_max = max(uxv_max, {ux_max.first + depth[cur], {ux_max.second, cur}});
        }
        return uxv_max;
    }
 
    int query(int a, int b) const {
        if (a == b) return a;
        a = timer[a], b = timer[b];
        if (a > b) swap(a, b);
        return euler_tour[rmq.query(a, b).second];
    }
 
    bool is_ancestor(int a, int b) const {
        return tour_in[a] <= tour_in[b] && tour_in[b] < tour_out[a];
    }
 
    bool on_path(int x, int a, int b) const {
        return (is_ancestor(x, a) || is_ancestor(x, b)) && is_ancestor(query(a, b), x);
    }
 
    int dist(int a, int b) const {
        return depth[a] + depth[b] - 2 * depth[query(a, b)];
    }
 
    int child_ancestor(int a, int b) const {
        assert(a != b); assert(is_ancestor(a, b));
        // Note: this depends on rmq_t breaking ties by latest index.
        int child = euler_tour[rmq.query(timer[a], timer[b]).second + 1];
        assert(parent[child] == a);
        assert(is_ancestor(child, b));
        return child;
    }
 
    int get_kth_ancestor(int a, int k) const {
        while (a >= 0) {
            int root = heavy_root[a];
            if (depth[root] <= depth[a] - k) return idx[tour_in[a] - k];
            k -= depth[a] - depth[root] + 1;
            a = parent[root];
        }
        return a;
    }
 
    int get_kth_node_on_path(int a, int b, int k) const {
        int lca = query(a, b);
        int x = depth[a] - depth[lca], y = depth[b] - depth[lca];
        assert(0 <= k && k <= x + y);
        if (k < x) return get_kth_ancestor(a, k);
        else return get_kth_ancestor(b, x + y - k);
    }

    int get_common_node(int a, int b, int c) const {
        // Return the deepest node among lca(a, b), lca(b, c), and lca(c, a).
        int x = query(a, b), y = query(b, c), z = query(c, a);
        x = depth[y] > depth[x] ? y : x;
        x = depth[z] > depth[x] ? z : x;
        return x;
    }
};
