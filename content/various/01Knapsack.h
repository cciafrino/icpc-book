/**
 * Author: Chris
 * License: CC0
 * Description: Bottom-up is faster in practice
 * Status: tested
 * Time: $O(N \log N)$
 */
 
// 1-indexed bottom-up, faster in practice
int Knapsack(int limit, vector<int> &v, vector<int> &w) {
    vector<int> dyn(10*v.size(), -1); int n = w.size();
    dyn[0] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = limit; j >= w[i]; --j)
            if (dyn[j - w[i]] >= 0)
                dyn[j] = max(dyn[j], dyn[j - w[i]] + v[i]);
    int result = 0;
    for (int i = 0; i <= limit; ++i) 
        result = max(result, dyn[i]);
    return result;
}
// top-down
int n, c; // total of items and cost
array<int, MAXN> w, v; // weight, value
array<array<int, MAXN>, MAXN> dyn; // filled -1

int get(int idx, int cap) {
    if (cap < 0) return -INT_MAX;
    if (idx == n) return 0;
    if (dyn[idx][cap] != -1) return dyn[idx][cap];
    return dyn[idx][cap] = max(get(idx+1, cap), v[idx] + get(idx+1, cap - w[idx]));
}

void recover(int idx, int cap) { 
    if (idx == n) return;
    int grab = v[idx] + get(idx+1, cap - w[idx]);
    int change = get(idx+1, cap);
    if (grab >= change) {
        items.push_back(idx);
        recover(idx+1, cap - w[idx]);
    }
    else recover(idx+1, cap);
}
