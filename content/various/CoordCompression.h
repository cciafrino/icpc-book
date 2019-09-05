/**
 * Author: Felipe Abella
 * Description:
 * Status: tested
 */
vector<int> comp_coord(vector<int> &y, int N) {
    vector<int> result;
    for (int i = 0; i < N; ++i) result.emplace_back(y[i]);
    sort(result.begin(), result.end());
    result.resize(unique(result.begin(), result.end())- result.begin());
    for (int i = 0; i < N; ++i)
        y[i] = lower_bound(result.begin(), result.end(), y[i]) - result.begin();
    return result;
}
