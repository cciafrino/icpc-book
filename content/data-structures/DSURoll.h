/**
 * Author: Chris
 * Description: DSU with Rollbacks
 */

struct unionfind_t {
    vector<int> parent, rank;
    vector<bool> is_dirty;
    vector<int> dirty;
    unionfind_t(int n): parent(n), rank(n, 0), is_dirty(n, false) {
        iota(parent.begin(), parent.end(), 0);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (rank[a] > rank[b]) swap(a, b);
        parent[a] = b;
        mark_dirty(a);
        if (rank[a] == rank[b]) {
            ++rank[b];
            mark_dirty(b);
        }
    }
    int find(int a) {
        if (parent[a] == a) return a;
        mark_dirty(a);
        return parent[a] = find(parent[a]);
    }
    void mark_dirty(int a) {
        if (!is_dirty[a]) {
            is_dirty[a] = true;
            dirty.push_back(a);
        }
    }
    void rollback() {
        for (int v : dirty) {
            parent[v] = v;
            rank[v] = 0;
            is_dirty[v] = false;
        }
        dirty.clear();
    }
};
