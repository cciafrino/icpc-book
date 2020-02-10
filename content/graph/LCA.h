/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: 
 * Status: tested
 * Description: 
 * Usage:
 * Time: 
 */
template<typename T, class Cmp=less<T>>
struct rmq_t {
    Cmp cmp; vector<vector<T>> table;
    rmq_t() {}
    rmq_t(const vector<T> &values, Cmp _cmp = Cmp()): cmp(_cmp) {
        table.push_back(values);
        for (int l = 1; l <= (int)__lg(values.size()); ++l) {
            table.push_back(vector<T>(values.size() - (1<<l) + 1));
            for (int i = 0; i+(1<<l) <= (int)values.size(); ++i) 
                table[l][i] = min(table[l-1][i], table[l-1][i+(1<<(l-1))], cmp);
        }
    }
    T query(int a, int b) {
        int l = __lg(b-a+1);
        return min(table[l][a], table[l][b-(1<<l)+1], cmp);
    }
};

template<typename T>
struct cmp_as_key {
    vector<T> *values = nullptr;
    cmp_as_key() {}
    cmp_as_key(vector<T> *_values): values(_values) {}
    bool operator()(int a, int b) const {
        return (*values)[a] < (*values)[b];
    }
};

vector<vector<int>> edges;
vector<int> walk, last_seen, depth;
rmq_t<int, cmp_as_key<int>> rmq;

void dfs(int v, int p, int d) {
    depth[v] = d;
    last_seen[v] = walk.size();
    walk.push_back(v);
    for (int u : edges[v]) {
        if (u == p) continue;
        dfs(u, v, d + 1);
        last_seen[v] = walk.size();
        walk.push_back(v);
    }
}
 
void precalc() {
    dfs(0, -1, 0);
    rmq = {walk, {&depth}};
}
 
int lca(int a, int b) {
    int pa = last_seen[a], pb = last_seen[b];
    if (pa <= pb) return rmq.query(pa, pb);
    else return rmq.query(pb, pa);
}
