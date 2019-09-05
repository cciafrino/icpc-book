/**
 * Author: Chris 
 * Date: 
 * License: CC0
 * Source: G4G Tutorial
 * Description: 
 * Status: fuzz-tested a bit
 */

template<typename T, int size>
struct MergeSortTree {
    vector<T> tree[4*size];
    vector<T> a;
    MergeSortTree(vector<T> &values) { a = values; }
    void build(int idx, int lx, int rx) {
        if (lx == rx) tree[idx].push_back(a[lx]);
        else {
            int mid = l + (r-l)/2;
            build(2*idx, lx, mid);
            build(2*idx+1, mid+1, rx);
            merge(tree[2*idx].begin(), tree[2*idx].end(), tree[2*idx+1].begin(), tree[2*idx+1].end(), back_inserter(tree[idx]));
        }
    }
    T query(int idx, int lx, int rx, int ql, int qr, int a, int b) {
        if (ql <= lx && rx <= qr)
            return upper_bound(tree[idx].begin(), tree[idx].end(), b) - lower_bound(tree[idx].begin(), tree[idx].end(), a);
        if (qr < lx || ql > rx) return 0;
        int mid = lx + (rx - lx)/2;
        return query(2*idx, lx, mid, ql, qr, a, b) + query(2*idx+1, mid+1, rx, ql, qr, a, b);
    }
};
