/**
 * Author: Chris
 * Source: Geeksforgeeks + Codeforces
 * Description: 1D Fenwick Tree with range increment
 */
#include "FenwickTree.h"
template<class T, int SZ> struct FT_t {
    FT<T,SZ> bit[2]; // piecewise linear functions
    // let cum[x] = sum_{i=1}^{x}a[i]
    void update(int right, T delta) { // add delta to a[1..right]
        // if x <= right, cum[x] += delta*x
        bit[1].update(1, delta), bit[1].update(right+1, -delta); 
        // if x > right, cum[x] += delta*right
        bit[0].update(right+1, right*delta); 
    }
    void update(int left, int right, T delta) { 
        update(left-1,-delta), update(right, delta); }
    T sum(int x) { return bit[1].sum(x)*x+bit[0].sum(x); } 
    T query(int x, int y) { return sum(y)-sum(x-1); }
}; 
