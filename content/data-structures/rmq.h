/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: Felipe Abella
 * Status: Tested several times
 * Description: Range Minimum/Maximum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b]) in constant time. Returns a pair that holds the answer, first element is the value and the second is the index.
 * Usage:
 *  rmq_t<pair<int, int>> rmq(values); 
 *  // values is a vector of pairs {val(i), index(i)}
 *  rmq.query(inclusive, exclusive); 
 *  rmq_t<pair<int, int>, greater<pair<int, int>>> rmq(values) 
 *  //max query
 *  Time: $O(|V| \log |V| + Q)$
 */
template<typename T, typename Cmp=less<T>>
struct rmq_t : private Cmp {
    int N = 0;
    vector<vector<T>> table; 
    const T& min(const T& a, const T& b) const { return Cmp::operator()(a, b) ? a : b; }
    rmq_t() {}
    rmq_t(const vector<T>& values) : N(int(values.size())), table(__lg(N) + 1) {
        table[0] = values;
        for (int a = 1; a < int(table.size()); ++a) {
            table[a].resize(N - (1 << a) + 1);
            for (int b = 0; b + (1 << a) <= N; ++b) 
                table[a][b] = min(table[a-1][b], table[a-1][b + (1 << (a-1))]); 
        }
    }
    T query(int a, int b) const { 
        int lg = __lg(b - a);
        return min(table[lg][a], table[lg][b - (1 << lg) ]);
    }
};
