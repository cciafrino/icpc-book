/**
 * Author: halyavin
 * Description: Time and space efficient Lazy SegTree.
 * Usage: Change private functions to
 */

template<class T, class Tlazy = T>
struct LazySegTree {
    int size;
    vector<T> t;
    vector<Tlazy> lazy;
    int h;
    LazySegTree(int N) : size(N), t(2 * N), lazy(N, lazyInit()),
        h(32 - __builtin_clz(N)) { }
    LazySegTree(const vector<T> &other) :
      size(other.size()),
      t(2 * other.size()),
      lazy(other.size(), lazyInit()),
      h(32 - __builtin_clz(other.size())) {
        std::copy(other.begin(), other.end(), t.begin() + size);
        for (int i = size; i-- > 1;) 
            t[i] = combine(t[2 * i], t[2 * i + 1]);
    }
    void apply(int p, int level, Tlazy up_lazy) {
        if (p < size) {
            lazy[p] = combinelazy(lazy[p], up_lazy);
            t[p] = combineWithlazy(t[2 * p], t[2 * p + 1], level, lazy[p]);
        } else t[p] = combineValue(t[p], up_lazy);
    }
    void build(int p) {
        int level = 0;
        while (p > 1) {
            level++;
            p /= 2;
            t[p] = combineWithlazy(t[2 * p], t[2 * p + 1], level, lazy[p]);
        }
    }
    void push(int p) {
        for (int s = h; s > 0; s--) {
            int pos = p >> s;
            if (lazy[pos] != lazyInit()) {
                apply(2 * pos, s - 1, lazy[pos]);
                apply(2 * pos + 1, s - 1, lazy[pos]);
                lazy[pos] = lazyInit();
            }
        }
    }
    void update(int p, Tlazy value) {
        p += size;
        t[p] = combineValue(t[p], value);
        build(p);
    }
    T query(int l, int r) {
        if (l == r) return init();
        l += size;
        r += size;
        push(l);
        push(r - 1);
        T left = init(), right = init();
        while (l < r) {
            if (l & 1) {
                left = combine(left, t[l]);
                l++;
            }
            if (r & 1) {
                r--;
                right = combine(t[r], right);
            }
            l /= 2;
            r /= 2;
        }
        return combine(left, right);
    }
    void update(int l, int r, Tlazy value) {
        push(l); push(r-1); // not sure if its needed
        if (l == r) return;
        l += size;
        r += size;
        int l0 = l;
        int r0 = r - 1;
        int level = 0;
        while (l < r) {
            if (l & 1) {
                apply(l, level, value);
                l++;
            }
            if (r & 1) {
                r--;
                apply(r, level, value);
            }
            l /= 2;
            r /= 2;
            level++;
        }
        build(l0);
        build(r0);
    }
    T query(int p) {
        p += size;
        push(p);
        return t[p];
    }
 
 private: 
    T combineWithlazy(T left, T right, int level, Tlazy lazy) {
        if (lazy == -1) { // sum = return (right - left + 1) * lazy
            return combine(left, right);
        } else {
            return lazy;
        }
    }
    T combine(T left, T right) {
        return max(left, right); // (left + right) or min(left,right)
    }
    Tlazy combinelazy(Tlazy lazy, Tlazy up_lazy) {
        if (up_lazy == -1) return lazy;
        return up_lazy;
        
    }
    T combineValue(T value, Tlazy up_lazy) {
        return up_lazy;
    }
    T init() {
        return 0;
    }
    Tlazy lazyInit() {
        return -1;
    }
};
