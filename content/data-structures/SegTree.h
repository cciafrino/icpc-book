/**
 * Author: halyavin
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Time and space efficient Segment Tree. Point update and range query.
 * Time: O(\log N)
 * Status: fuzz-tested
 */
#pragma once

template<class T>
struct segtree_t {
    int size;
    vector<T> t;
    segtree_t(int N) : size(N), t(2 * N) {}
    segtree_t(const vector<T> &other) :
            size(other.size()),
            t(2 * other.size()) {
        copy(other.begin(), other.end(), t.begin() + size);
        for (int i = size; i-- > 1;) 
            t[i] = combine(t[2 * i], t[2 * i + 1]);
    }
    T get(int p) {
        return t[p + size];
    }
    void modify(int p, T value) {
        p += size;
        t[p] = value;
        while (p > 1) {
            p = p / 2;
            t[p] = combine(t[2 * p], t[2 * p + 1]);
        }
    }
    T query(int l, int r) {
        l += size;
        r += size;
        T left = init();
        T right = init();
        while (l < r) {
            if (l & 1) {
                left = combine(left, t[l]);
                l++;
            }
            if (r & 1) {
                r--;
                right = combine(t[r], right);
            }
            l = l / 2;
            r = r / 2;
        }
        return combine(left, right);
    }
private:
    T combine(T left, T right) {
        return left + right;
    }
    T init() {
        return T();
    }
};
