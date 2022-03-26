/**
 * Author: ?
 * Date: 
 * License: CC0
 * Source: own work
 * Description: Solves $Ax = b$ over $\mathbb F_2$. If there are multiple solutions, one is returned arbitrarily.
 *  Returns true, or false if no solutions. Last column of $a$ is $b$. $c$ is the rank.
 * Time: O(n^2 m)
 * Status: Stress tested on 2018-2019 Brazil Subregional - M
 */
typedef bitset<2010> bs;
bool gauss(vector<bs> a, bs& ans, int n) {
    int m = int(a.size()), c = 0;
    bs pos; pos.set();
    for (int j = n-1, i; j >= 0; --j) {
        for (i = c; i < m; ++i)
            if (a[i][j]) break;
        if (i == m) continue;
        swap(a[c], a[i]);
        i = c++; pos[j] = 0;
        for (int k = 0; k < m; ++k)
            if (a[k][j] && k != i)
                a[k] ^= a[i];
    }
    ans = pos;
    for(int i = 0; i < m; ++i) {
        int ac = 0;
        for (int j = 0; j < n ; ++j) {
            if (!a[i][j]) continue;
            if (!pos[j]) pos[j] = 1, ans[j] = ac^a[i][n];
            ac ^= ans[j];
        }
        if (ac != a[i][n]) return false;
    }
    return true;
}
