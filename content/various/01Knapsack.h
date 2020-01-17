/**
 * Author: Chris
 * License: CC0
 * Description: Bottom-up is faster in practice
 * Status: tested
 * Time: $O(N \log N)$
 */
 
// 1-indexed bottom-up, waaaay faster in practice
int knapsack(int limit, vector<int> &v, vector<int> &w) {
    vector<int> dp(limit+1, -1); int n = w.size();
    dp[0] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = limit; j >= w[i]; --j)
            if (dp[j - w[i]] >= 0)
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    int result = 0;
    for (int i = 0; i <= limit; ++i) 
        result = max(result, dp[i]);
    return result;
}
// top-down
int n, c; // total of items and cost
array<int, MAXN> w, v; // weight, value
array<array<int, MAXN>, MAXN> dp; // filled -1

int get(int idx, int cap) {
    if (cap < 0) return -INT_MAX;
    if (idx == n) return 0;
    if (dp[idx][cap] != -1) return dp[idx][cap];
    return dp[idx][cap] = max(get(idx+1, cap), v[idx] + get(idx+1, cap - w[idx]));
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
