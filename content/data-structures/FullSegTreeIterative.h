/**
 * Author: Chris
 * Description: Full Iterative Segment Tree
 */

template<class T>
struct segtree_t {
    int size;
    vector<T> tree;
    vector<T> lazy;
    segtree_t(int N) : size(N), tree(2 * N), lazy(N) {}
    segtree_t(const vector<T> &other) :
            size(other.size()),
            tree(2 * other.size()),
            lazy(other.size()) {
        copy(other.begin(), other.end(), t.begin() + size);
        for (int i = size; i-- > 1;) 
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
    T query(int l, int r) { // query [l, r)
        if (l == r) return 0;
        T sum = T();
        l += size;
        r += size;
        int level = 1, leftMult = 0, rightMult = 0;
        while (l < r) {
            if (leftMult != 0) sum += lazy[l - 1] * leftMult;
            if (l & 1) {
                sum += tree[l];
                leftMult += level;
                l++;
            }
            if (rightMult != 0) sum += lazy[r] * rightMult;
            if (r & 1) {
                r--;
                sum += tree[r];
                rightMult += level;
            }
            l /= 2;
            r /= 2;
            level *= 2;
        }
        l--;
        while (r > 0) {
            if (leftMult > 0) sum += lazy[l] * leftMult;
            if (rightMult > 0) sum += lazy[r] * rightMult;
            l /= 2;
            r /= 2;
        }
        return sum;
    }
    void update(int l, int r, T value) {
        if (l == r) return;
        l += size;
        r += size;
        int level = 1;
        T leftAdd = 0, rightAdd = 0;
        while (l < r) {
            if (leftAdd != 0) tree[l - 1] = leftAdd;
            if (l & 1) {
                if (l < size) lazy[l] = value;
                tree[l] = level * value;
                leftAdd = level * value;
                l++;
            }
            if (rightAdd != 0) tree[r] = rightAdd;
            if (r & 1) {
                r--;
                if (r < size) lazy[r] = value;
                tree[r] = level * value;
                rightAdd = level * value;
            }
            l /= 2;
            r /= 2;
            level *= 2;
        }
        l--;
        while (r > 0) {
            tree[l] += leftAdd;
            tree[r] += rightAdd;
            l /= 2;
            r /= 2;
        }
    }
    T query(int p) {
        p += size;
        T res = tree[p];
        while (p > 1) {
            p = p / 2;
            res += lazy[p];
        }
        return res;
    }
    void update(int p, T value) {
        p += size;
        while (p > 0) {
            tree[p] += value;
            p = p / 2;
        }
    }
    T find_first(int v, int lx, int rx) {
        int l = -1, r = -1, cur;
        for (int a = lx + n, b = rx + n; a < b ; a /= 2, b /= 2) {
            if (a&1) {
                if (tree[a] <= v) 
                    if (l == -1) l = a;
                a += 1;
            }
            if (b&1) {
                b--;
                if (tree[b] <= v) r = b;
            }
        }
        if (l != -1) cur = l;
        else if (r != -1) cur = r;
        else return -1;
        assert(tree[cur] <= v);
        while(cur < n) {
            if (tree[2*cur] <= v) cur = 2*cur;
            else if (tree[2*cur+1] <= v) cur = 2*cur+1;
            else assert(false);
        }
        return cur - n;
    }
};


