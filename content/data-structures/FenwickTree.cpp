/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: TopCoder tutorial
 * Description: Classic FT with linear initialization. All queries are [a, b). get(pos) function returns the element at index pos in O(1) amortized. lowerbound(sum) returns the largest i in [0, n] st query(i) <= sum. Returns -1 if no such i exists (sum < 0).  Can be used as an ordered set on indices in [0, n) by using the tree as a 0/1 array: update(index, +1) is equivalent to insert(index); be careful not to re-insert. 
 * get(index) provides whether index is present or not. 
 * query(index) provides the count of elements < index. 
 * lowerbound(k) finds the k-th smallest element (0-indexed).
 * Time: Both operations are $O(\log N)$.
 */

template<typename T> struct FT {
    T tree_sum;
    const int n;
    vector<T> tree;
    FT(int _n) : n(_n), tree(n) {}
    FT(vector<T> &og) : n(og.size()+1), tree(n+1), tree_sum(0) {
        for (int i = 1; i <= n; ++i) { 
            tree_sum += og[i-1];
            tree[i] = og[i-1];
            for (int k = (i&-i) >> 1; k > 0; k >>= 1)
                tree[i] += tree[i-k];
        }
    }
    void update(int idx, const T delta) {
        tree_sum += delta;
        for (;idx <= n; idx += idx&-idx)
            tree[i] += delta;
    }
    T query(int idx){
        T ret = 0;
        for (; idx; idx -= idx&-idx) ret += tree[i];
        return ret;
    }
    T query_suffix(int idx) { return tree_sum - query(idx); }
    T query(int a, int b) { return query(b) - query(a); }
    T get(int pos) {
        int above = pos + 1;
        T sum = tree[above];
        above -= above & -above;
        while (pos != above) {
            sum -= tree[pos];
            above -= above&-above;
        }
        return sum;
    }
    int lower_bound(T sum) {
        if (sum < 0) return -1;
        int prefix = 0;
        for (int k = 31 - __builtin_clz(n); k >= 0; k--)
            if (prefix + (1 << k) <= n && tree[prefix + (1 << k)] <= sum) {
                prefix += 1 << k;
                sum -= tree[prefix];
            }
        return prefix;
    }
};