/**
 * Author: Felipe Abella
 * Date: 2018-07-06
 * License: CC0
 * Description: 
 */
typedef unsigned long long ulint;
const int max_size = 60;
map<pair<int, ulint>, int> grundy;

int get_grundy(int n, ulint used) {
    int contains_adj[max_size];
    auto it = grundy.find({n, used});
    if (it != grundy.end()) return it->second;
    fill(contains_adj, contains_adj + max_size, 0);
    for (int remove = 1; remove <= n; ++remove)
        if (!(used & (1ULL << remove))) {
            int adj_state = get_grundy(n - remove, used | (1ULL << remove));
            if (adj_state < max_size)
                contains_adj[adj_state] = 1;
        } 
    int result = 0;
    while (result < max_size && contains_adj[result])
        ++result;
    return grundy[{n, used}] = result;
}
