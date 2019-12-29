/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: TopCoder
 * Description: 
 * Time: Both operations are $O(\log N)$.
 */

template<typename T> struct FT {
    T tree_sum;
    const int n;
    vector<T> tree;
    FT(int n) : tree(n) {}
    FT(vector<T> &og) : n(og.size()+1), tree(n+1), tree_sum(0) {
        for (int i = 1; i <= n; ++i) { // O(n) initialization
            tree_sum += og[i-1];
            tree[i] = og[i-1];
            for (int k = (i&-i) >> 1; k > 0; k >>= 1)
                tree[i] += tree[i-k];
        }
    }
    void update(int idx, const T delta) {
        tree_sum += delta;
        for (int i = idx+1; i <= tree.size(); i += i&-i)
            tree[i] += delta;
    }
    T query(int idx){ // [0, idx)
        T ret = 0;
        for (int i = idx; i > 0; i -= i&-i) 
            ret += tree[i];
        return ret;
    }
    T query_suffix(int idx) { // [idx, n)
        return tree_sum - query(idx);
    }
    T query(int a, int b) { // [a, b)
        return query(b) - query(a);
    }
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
};