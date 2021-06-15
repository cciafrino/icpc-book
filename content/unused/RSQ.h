/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: Felipe Abella
 * Status: Tested at Spoj RMQ
 * Description: Range Sum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time. 
 * Usage:
 *  rsq_t<int> rsq(values);
 *  rsq.query(inclusive, inclusive); 
 * Time: $O(|V| \log |V| + Q)$
 */

template<typename T>
struct rsq_t {
    vector<vector<T>> table;
    rsq_t() {}
    rsq_t(const vector<T> &values) {
        int n = values.size();
        table.resize(__lg(n)+1); table[0].resize(n);
        for (int i = 0; i < n; ++i) table[0][i] = values[i];
        for (int l = 1; l < (int)table.size(); ++l) {
            table[l].resize(n - (1<<l) + 1);
            for (int i = 0; i + (1<<l) <= n; ++i)
                table[l][i] = table[l-1][i] + table[l-1][i+(1<<(l-1))];
        }
    }
    T query(int a, int b) {
        int l = b - a + 1; T ret{};
        for (int i = (int)table.size(); i >= 0; --i) 
            if ((1 << i) <= l) {
                ret += table[i][a]; a += (1<<i);
                l = b - a + 1;
            }
        return ret;
    }
};
