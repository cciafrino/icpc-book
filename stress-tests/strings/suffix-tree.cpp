#include<bits/stdc++.h>
using namespace std;

template<typename T, typename Cmp=less<T>>
struct rmq_t : private Cmp {
    int N = 0;
    vector<vector<T>> table; 
    const T& min(const T& a, const T& b) const { return Cmp::operator()(a, b) ? a : b; }
    rmq_t() {}
    rmq_t(const vector<T>& values) : N(int(values.size())), table(__lg(N) + 1) {
        table[0].resize(N);
        for (int i = 0; i < N; ++i) table[0][i] = values[i];
        for (int a = 1; a < int(table.size()); ++a) {
            table[a].resize(N - (1 << a) + 1);
            for (int b = 0; b + (1 << a) <= N; ++b) 
                table[a][b] = min(table[a-1][b], table[a-1][b + (1 << (a-1))]); 
        }
    }
    T query(int a, int b) const { 
        int lg = __lg(b - a + 1);
        return min(table[lg][a], table[lg][b - (1 << lg) + 1]);
    }
};

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

    struct node_t {
        int link, len, id;
    };

    vector<node_t> tree;
    void build_suffix_tree() {
        vector<int> stk;
        tree.push_back({-1, 0, -1});
        stk.push_back(size(tree) - 1);
        for (int i = 1; i < N; ++i) {
            for (auto len : {N - invsa[i] - 1, lcp[i]}) {
                int l = invsa[i];
                while (tree[stk.back()].len > len) {
                    int cur = stk.back();
                    stk.pop_back();
                    l = tree[cur].id;
                    if (len > tree[stk.back()].len) {
                        tree.push_back({-1, len, l});
                        stk.push_back(size(tree) - 1);
                    }
                    tree[cur].link = stk.back();
                }
                if (len > tree[stk.back()].len) {
                    tree.push_back({-1, len, l});
                    stk.push_back(size(tree) - 1);
                }
            }
        }
    }
};

void dfs(suffix_array_t& us, string& s, int h, int l, int r) {
    int nh;
    cout << h << "   " << l << " " << r << endl;
    if (r - l == 1) {
        nh = us.N - us.sa[l - 1];
    } else {
        int md;
        tie(nh, md) = us.get_split(l, r);
        dfs(us,s, nh, l, md);
        dfs(us,s, nh, md, r);
    } // there are (nh - h) distinct substrings s,t, occur exactly (r - l) times
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit | cin.eofbit | cin.badbit);
    string S = "cattcat";
    suffix_array_t us(begin(S), end(S));
    dfs(us, S, 0, 1, size(S));
}
