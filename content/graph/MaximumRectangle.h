/**
 * Author: BenQ
 * Description: Computes size of max rectangle in grid w/ obstacles
 * 
 */
// NOT WORKING
array<array<char, 1010>, 1010> grid;
array<int, 1010> cur;
int n, m;
lint result = 0;

void pre(int x) {
    vector<int> nex[m+1];
    for (int i = 0; i < n; ++i) nex[cur[i]-x].push_back(i);
    UF dsu(1010);
    for (int i = m; i >= 0; --i) 
        for (auto &a : nex[i]) {
            dsu.parent[a] = a;
            if (a > 0 && dsu.parent[a-1] != -1) dsu.unite(a, a-1);
            if (a < n-1 && dsu.parent[a+1] != -1) dsu.unite(a, a+1);
            result = max(result, i*(lint)dsu.rank[dsu.find(a)]);
        }
}

int solve() {
    for (int i = 0; i < n; ++i) cur[i] = m;
    for (int j = m-1; j >= 0; --j) {
        for (int i = 0; i < n; ++i)
            if (grid[i][j] == '*') cur[i] = j; //obstacle
        pre(j);
    }
    return result;
}
