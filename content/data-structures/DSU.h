/**
 * Author: Chris
 * Date: 2018
 * License: CC0
 * Source: Me
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */

struct UF {
    int n;
    vector<int> parent, rank;
    UF(int _n): n(_n), parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find(parent[v]);
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (rank[a] > rank[b]) swap(a, b);
        parent[a] = b;
        if (rank[a] == rank[b]) ++rank[b];
        return true;
    }
};
