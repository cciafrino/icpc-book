/**
 * Author: Chris
 * Description: Solve lowest common ancestor queries using binary jumps.
 * Can also find the distance between two nodes. 
 * Time: $O(N\lgN + Q\lgN)$ 
 * Status: Tested
 */

template<typename T>
struct lca_t {
    int logn{0}, preorderpos{0};
    vector<int> invpreorder, height;
    vector<vector<int>> jump_binary, edges;
    lca_t(int n, vector<vector<int>>& adj) : 
    edges(adj), height(n), invpreorder(n) { 
        while((1<<(logn+1)) <= n) ++logn;
        jump_binary.assign(n+1, vector<int>(logn+1, 0));
        dfs(0, -1, 0);
    } 
    void dfs(int v, int p, int h) { 
        invpreorder[v] = preorderpos++;
        height[v] = h;
        jump_binary[v][0] = p < 0 ? v : p;
        for (int l = 1; l <= logn; ++l)
            jump_binary[v][l] = jump_binary[jump_binary[v][l-1]][l-1];
        for (int u : edges[v]) {
            if (u == p) continue; 
            dfs(u, v, h + 1);
        }
    }
    int climb(int v, int dist) { 
        for (int l = 0; l <= logn; ++l)
            if (dist & (1 << l)) v = jump_binary[v][l];
        return v;
    }
    int query(int a, int b) { 
        if (height[a] < height[b]) swap(a, b);
        a = climb(a, height[a] - height[b]);
        if (a == b) return a;
        for (int l = logn; l >= 0; --l) 
            if (jump_binary[a][l] != jump_binary[b][l]) 
                a = jump_binary[a][l], b = jump_binary[b][l];
        return jump_binary[a][0];
    } 
    T dist(int a, int b) {
        return height[a] + height[b] - 2 * height[query(a,b)];
    }
    bool is_parent(int p, int v) { 
        if (height[p] > height[v]) return false;
        return p == climb(v, height[v] - height[p]);
    }
    bool on_path(int x, int a, int b) {
        int v = query(a, b);
        return is_parent(v, x) && (is_parent(x, a) || is_parent(x, b));
    }
    int get_kth_on_path(int a, int b, int k) {
        int v = query(a, b);
        int x = height[a] - height[v], y = height[b] - height[v];
        if (k < x) return climb(a, k);
        else return climb(b, x + y - k);
    }
};