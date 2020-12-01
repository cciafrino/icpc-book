/**
 * Author: Felipe Abella, Chris
 * Description: Builds suffix array for a string. 
 * The {\tt lcp} function calculates longest
 * common prefixes for neighbouring strings in suffix array.
 * The returned vector is of size $n+1$. 
 * Time: $O(N \log N)$ where $N$ is the length of the string
 * for creation of the SA. $O(N)$ for longest common prefixes.
 */
#include<../data-structures/RMQ.h>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct suffix_array_t { 
    int N, H; 
    vector<int> sa, invsa;
    vector<int> lcp;
    rmq_t<pair<int, int>> RMQ;
    bool cmp(int a, int b) { return invsa[a + H] < invsa[b + H]; }
    void ternary_sort(int a, int b) {
        if (a == b) return;
        int pivot = sa[a + rng() % (b - a)];
        int left = a, right = b;
        for (int i = a; i < b; ++i) if (cmp(sa[i], pivot)) swap(sa[i], sa[left++]);
        for (int i = b-1; i >= left; --i) if (cmp(pivot, sa[i])) swap(sa[i], sa[--right]);
        ternary_sort(a, left);
        for (int i = left; i < right; ++i) invsa[sa[i]] = right-1;
        if (right-left == 1) sa[left] = -1;
        ternary_sort(right, b);
    } 
    suffix_array_t() {} 
    template<typename I>
    suffix_array_t(I begin, I end): N(int(end - begin)), sa(N) {
        vector<int> v(begin, end); v.push_back(INT_MIN);
        invsa = v; iota(sa.begin(), sa.end(), 0);
        H = 0; ternary_sort(0, N);
        for (H = 1; H <= N; H *= 2)
            for (int j = 0, i = j; i != N; i = j)
                if (sa[i] < 0) {
                    while (j < N && sa[j] < 0) j += -sa[j];
                    sa[i] = -(j - i);
                } 
                else { j = invsa[sa[i]] + 1; ternary_sort(i, j); } 
        for (int i = 0; i < N; ++i) sa[invsa[i]] = i;

        lcp.resize(N); int res = 0;
        for (int i = 0; i < N; ++i) {
            if (invsa[i] > 0) while (v[i + res] == v[sa[invsa[i] - 1] + res]) ++res;
            lcp[invsa[i]] = res; res = max(res - 1, 0);
        }
        vector<pair<int, int>> lcp_index(N);
        for (int i = 0; i < N; ++i) lcp_index[i] = {lcp[i], 1 + i};
        RMQ = rmq_t<pair<int, int>>(move(lcp_index));
    } 
    pair<int, int> rmq_query(int a, int b) const { return RMQ.query(a, b); } 
    pair<int, int> get_split(int a, int b) const { return RMQ.query(a, b-2); }
    int get_lcp(int a, int b) const { 
        if (a == b) return N - a;
        a = invsa[a], b = invsa[b];
        if (a > b) swap(a, b);
        return rmq_query(a + 1, b).first;
    } 
};
