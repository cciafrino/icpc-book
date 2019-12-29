/**
 * Author: Chris
 * Description: SQRT-Decomposition for sum range and point update.
 */
 
template<typename T>
struct tree_t {
    int p;
    const int n, sz;
    vector<T> og, bucket;
    tree_t(vector<T>& other) : n(other.size()), og(other), 
        sz((int)sqrt(n)), p(-1), bucket(sz) { 
        for (int i = 0; i < n; ++i) {
            p += (i % sz == 0);
            bucket[p] += og[i];
        }
    }
    void update(int pos, T delta) {
        bucket[pos/sz] += delta - og[pos];
        og[pos] = delta;
    }
    T query(int lx, int rx) {
        T sum = 0;
        while (lx < rx && lx%sz != 0 && lx != 0) sum += og[lx++];
        for(; lx + sz <= rx; lx += sz) sum += blocks[lx/sz];
        while (lx <= rx) sum += og[lx++];
        return sum;
    }
};