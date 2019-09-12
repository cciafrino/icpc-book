/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: Felipe Abella
 * Status: Tested at Spoj RMQ
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time. Returns a pair that holds the answer, first element is the value and the second is the index, obviously doesn't work with sum or similar queries.
 * Usage:
 *  RMQ<int> rmq(values);
 *  rmq.query(inclusive, inclusive); 
 * Time: $O(|V| \log |V| + Q)$
 */

// change cmp for max query or similar
template<typename T, typename Cmp=less<pair<T, int>>>
struct RMQ {
  Cmp cmp;
  vector<vector<pair<T, int>>> table; 
  RMQ(const vector<T> &values) {
    int n = values.size();
    table.resize(__lg(n)+1);
    table[0].resize(n);
    for (int i = 0; i < n; ++i) table[0][i] = {values[i], i};
    for (int l = 1; l < (int)table.size(); ++l) {
        table[l].resize(n - (1<<l) + 1);
        for (int i = 0; i + (1<<l) <= n; ++i) {
            table[l][i] = min(table[l-1][i], table[l-1][i+(1<<(l-1))], cmp); // Change if max
            //table[l][i].first = (table[l-1][i].first + table[l-1][i+(1<<(l-1))].first); // example of sum 
        }
            
    }
  }
  pair<T, int> query(int a, int b) { // min query
    int l = __lg(b-a+1);
    return min(table[l][a], table[l][b-(1<<l)+1], cmp);
  }
  int sum_query(int a, int b) { 
        int l = b-a+1, ret = 0;
        for (int i = (int)table.size(); i >= 0; --i) 
            if ((1 << i) <= l) {
                ret += table[i][a].first; a += (1 << i);
                l = b - a + 1;
            }
        return ret;
  }
};
