/**
 * Author: Felipe Abella, Chris
 * Description: Builds suffix array for a string. 
 * The {\tt lcp} function calculates longest
 * common prefixes for neighbouring strings in suffix array.
 * The returned vector is of size $n+1$, and $ret[0] = 0$.
 * Time: $O(N \log N)$ where $N$ is the length of the string
 * for creation of the SA. $O(N)$ for longest common prefixes.
 */
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct suffix_array_t { /// start-hash
    vector<vector<pair<int, int>>> rmq;
    int n, h; vector<int> sa, invsa, lcp;
    bool cmp(int a, int b) { return invsa[a+h] < invsa[b+h]; }
    void ternary_sort(int a, int b) {
        if (a == b) return;
        int pivot = sa[a+rng()%(b-a)];
        int left = a, right = b;
        for (int i = a; i < b; ++i) if (cmp(sa[i], pivot)) swap(sa[i], sa[left++]);
        for (int i = b-1; i >= left; --i) if (cmp(pivot, sa[i])) swap(sa[i], sa[--right]);
        ternary_sort(a, left);
        for (int i = left; i < right; ++i) invsa[sa[i]] = right-1;
        if (right-left == 1) sa[left] = -1;
        ternary_sort(right, b);
    } /// end-hash
    suffix_array_t() {} /// start-hash
    suffix_array_t(vector<int> v): n(v.size()), sa(n) {
        v.push_back(INT_MIN);
        invsa = v; iota(sa.begin(), sa.end(), 0);
        h = 0; ternary_sort(0, n);
        for (h = 1; h <= n; h *= 2)
            for (int j = 0, i = j; i != n; i = j)
                if (sa[i] < 0) {
                    while (j < n && sa[j] < 0) j += -sa[j];
                    sa[i] = -(j-i);
                } /// end-hash
                else { j = invsa[sa[i]]+1; ternary_sort(i, j); } /// start-hash
        for (int i = 0; i < n; ++i) sa[invsa[i]] = i;
        lcp.resize(n); int res = 0;
        for (int i = 0; i < n; ++i) {
            if (invsa[i] > 0) while (v[i+res] == v[sa[invsa[i]-1]+res]) ++res;
            lcp[invsa[i]] = res; res = max(res-1, 0);
        } /// end-hash
        int logn = 0; while ((1<<(logn+1)) <= n) ++logn; /// start-hash
        rmq.resize(logn+1, vector<pair<int, int>>(n));
        for (int i = 0; i < n; ++i) rmq[0][i] = {lcp[i], i};
        for (int l = 1; l <= logn; ++l)
            for (int i = 0; i+(1<<l) <= n; ++i)
                rmq[l][i] = min(rmq[l-1][i], rmq[l-1][i+(1<<(l-1))]);
    } /// end-hash
    pair<int, int> rmq_query(int a, int b) { /// start-hash
        int size = b-a+1, l = __lg(size);
        return min(rmq[l][a], rmq[l][b-(1<<l)+1]);
    } /// end-hash
    int get_lcp(int a, int b) { /// start-hash
        if (a == b) return n-a;
        int ia = invsa[a], ib = invsa[b];
        return rmq_query(min(ia, ib)+1, max(ia, ib)).first;
    } /// end-hash
};

