//Não eh 2-Sat se ambos pertencerem a mesma componente fortemente conexa (implemente tarjan_t!) - Essa solução eh bem melhor que usando dfs
struct twosat_t {
    int n;
    vector<vector<int>> adj;
    vector<int> result;
    twosat_t() {}
    twosat_t(int _n) : n(_n), adj(n<<1), result(n, -1) {}
    void add_or(int x, int y) {
        adj[x^1].emplace_back(y);
        adj[y^1].emplace_back(x);
    }
    bool solve() {
        tarjan_t tarjan((int)adj.size());
        tarjan.adj = adj;
        tarjan.solve();
        for (int i = 0; i < n; ++i) 
            if (tarjan.cnt_of[i<<1] == tarjan.cnt_of[(i<<1)+1]) return false;
        vector<int> cnt_result(tarjan.cnts.size(), -1);
        for (int i = 0; i < (int)cnt_result.size(); ++i) {
            if (cnt_result[i] == -1) cnt_result[i] = 1;
            for (int j = 0; j < tarjan.cnts[i].size(); ++j) {
                if (v < (n<<1)) {
                    cnt_result[tarjan.cnt_of[v^1]] = cnt_result[i] ^ 1;
                    if (cnt_result[i] == 1) result[v>>1] = v%2;
                }
            }
        }
        return true;
    }
};
