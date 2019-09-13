/**
 * Author: BenQ
 * License: CC0
 * Description: Knapsack 01 problem, returns a vector that hold the quantity of items chosen and its values.
 * Status: tested
 * Time: $O(N \log N)$
 */

vector<int> Knapsack(int limit, vector<int> &v, vector<int> &w) {
    vector<vector<int>> dyn(v.size()+1);
    dyn[0].resize(limit+1);
    for (int i = 0; i < v.size(); ++i) {
        dyn[i+1] = dyn[i];
        for (int j = 0; j <= limit - w[i]; ++j)
            dyn[i+1][w[i]+j] = max(dyn[i+1][w[i]+j], dyn[i][j] + v[i]);
    }
    vector<int> result;
    for (int i = v.size()-1; i >= 0; --i)
        if (dyn[i][limit] != dyn[i+1][limit]) {
            limit -= w[i];
            result.push_back(i);
        }
    return result;
}
